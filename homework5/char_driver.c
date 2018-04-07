#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/gfp.h>
#include <linux/slab.h>


#define MYDEV_NAME "mydriver"
#define CDRV_IOC_MAGIC 'Z'
#define ASP_CLEAR_BUF _IOW(CDRV_IOC_MAGIC,1,int)

//int major = 0;
int minor = 0;
int major_number = 0;
static int NUM_DEVICES = 3;// number of devices
int ramdiskSize = 100; 


struct class *my_class;

struct asp_mycdev {
	struct cdev dev;
	char *ramdisk;
	struct semaphore sem;
	int devNo;
	int ramdiskSize; //device size

};

static struct asp_mycdev *driverDevices = NULL;

static int mycdrv_release(struct inode *inode, struct file *filp) {
	struct asp_mycdev *dev; 
	dev = filp -> private_data;
	return 0;
}

int mycdrv_open(struct inode *inode, struct file *filp) {
	struct asp_mycdev *dev;
	dev = container_of(inode -> i_cdev, struct asp_mycdev, dev);
	filp -> private_data = dev;
	return 0;

}

ssize_t mycdrv_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
	struct asp_mycdev *dev = filp -> private_data;
	int nbytes;
	if(down_interruptible(&dev -> sem))
		return -ERESTARTSYS;
	if((count + *f_pos) > ramdiskSize) {
		pr_info("trying to read past end of device,"
			"aborting because this is just a stub!\n");
		return 0;
	}

	nbytes = count - copy_to_user(buf, dev -> ramdisk + *f_pos, count);
	*f_pos += nbytes;
	pr_info("\n READING function, nbytes=%d, pos=%d\n", nbytes, (int)*f_pos);
	up(&dev -> sem);
	return nbytes;
}

ssize_t mycdrv_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {
	struct asp_mycdev *dev = filp -> private_data;
	int nbytes;
	if(down_interruptible(&dev -> sem))
		return -ERESTARTSYS;
	if((count + *f_pos) > ramdiskSize) {
		pr_info("trying to read past end of device,"
			"aborting because this is just a stub!\n");
		return 0;
	}

	nbytes = count - copy_from_user(dev -> ramdisk + *f_pos, buf, count);
	*f_pos += nbytes;
	pr_info("\n WRITING function, nbytes=%d, pos=%d\n", nbytes, (int)*f_pos);
	up(&dev -> sem);
	return nbytes;
}

loff_t mycdrv_lseek(struct file *filp, loff_t offset, int orig) {
	struct asp_mycdev *dev = filp -> private_data;
	loff_t testpos;
	//char *temp;
	char *space;
	int i = 0;
	down_interruptible(&dev -> sem);
	switch(orig) {
		case SEEK_SET:
			testpos = offset;
			break;
		case SEEK_CUR:
			testpos = filp ->f_pos + offset;
			break;
		case SEEK_END:
			testpos = dev -> ramdiskSize + offset;
			break;
		default:
			return -EINVAL;
	}

	testpos = testpos >= 0 ? testpos : 0;
	if(testpos > dev -> ramdiskSize) {
		printk(KERN_INFO "current offset is %lld,offset is %lld,ramsize = %d",filp->f_pos,offset,dev -> ramdiskSize);
		space = kzalloc(testpos, GFP_KERNEL);
		for( i = 0; i < dev -> ramdiskSize; i++) {
			space[i] = dev -> ramdisk[i];
		}

		kfree(dev -> ramdisk);
		dev -> ramdisk = space;
	}

	filp -> f_pos = testpos;
	printk(KERN_INFO "current offset is %lld",filp->f_pos);
	up(&dev -> sem);
	return testpos;

}

long mycdrv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	struct asp_mycdev *dev = filp -> private_data;
	long retval = -1;
	int err = 0;
	down_interruptible(&dev -> sem);
	if(_IOC_DIR(cmd)&_IOC_READ)
	{
		err=!access_ok(VERIFY_WRITE,(void __user*)arg,_IOC_SIZE(cmd));
	}
	else if(_IOC_DIR(cmd)&_IOC_WRITE)
	{
		err=!access_ok(VERIFY_READ,(void __user*)arg,_IOC_SIZE(cmd));
	}
	switch(cmd) {
		case ASP_CLEAR_BUF:
			kfree(dev->ramdisk);
			dev->ramdisk=kzalloc(dev->ramdiskSize,GFP_KERNEL);
			filp->f_pos=0;
			printk(KERN_INFO "BUF has been cleared");
			retval = 1;
			break;
		default: retval = -ENOTTY;

	}
	up(&dev -> sem);
	if(retval == 1) {
		printk(KERN_DEBUG "Buffer is cleared");
	}

	return retval;
}


static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = mycdrv_read,
	.write = mycdrv_write,
	.open = mycdrv_open,
	.release = mycdrv_release,
	.llseek = mycdrv_lseek,
	.unlocked_ioctl = mycdrv_ioctl
};

static void driver_setup_cdev(struct asp_mycdev *dev, int index,int major_number) {
	int err, devno = MKDEV(major_number, minor + index);
	cdev_init(&dev -> dev,&fops);
	dev -> dev.owner = THIS_MODULE;
	dev -> dev.ops = &fops;
	err = cdev_add(&dev -> dev, devno,1);
}


/*initialize the driver*/
static int my_init(void) {
	dev_t dev = 0;
	char name[] = "mycdrv0";
	int result;
	int i = 0;
	result = alloc_chrdev_region(&dev,minor,NUM_DEVICES,MYDEV_NAME);
	major_number = MAJOR(dev);
	driverDevices = kmalloc(NUM_DEVICES * sizeof(struct asp_mycdev),GFP_KERNEL);
	for(i = 0; i < NUM_DEVICES; i++) {
		sema_init(&driverDevices[i].sem,1);
		driverDevices[i].ramdiskSize = 100;
		driverDevices[i].ramdisk = kzalloc((size_t)ramdiskSize,GFP_KERNEL);
		// driverDevices[i].dev.owner = THIS_MODULE;
		// driverDevices[i].dev.ops = &fops;
		// cdev_add(&driverDevices[i].dev,dev = MKDEV(major_number,i),1);
		driver_setup_cdev(&driverDevices[i],i,major_number);
	}
	my_class = class_create(THIS_MODULE,"MY CLASS");
	for( i = 0; i < NUM_DEVICES; i++) {
		char str[2];
		sprintf(str, "%d",i);
		name[6] = str[0];
		printk(KERN_INFO "device name is %s",name);
		device_create(my_class,NULL,result=MKDEV(major_number,i),NULL,name);
	}
	return 0;
}

/*initialize the cdev*/


void cleanUp(void) {
	dev_t devno = MKDEV(major_number,minor);
	int i = 0;
	for(i = 0; i < NUM_DEVICES; i++) {
		device_destroy(my_class,MKDEV(major_number,i));
	}

	class_destroy(my_class);
	for(i = 0; i < NUM_DEVICES;i++) {
		kfree(driverDevices[i].ramdisk);
		cdev_del(&driverDevices[i].dev);
		unregister_chrdev_region(devno = MKDEV(major_number,i),1);
	}
	
}

module_init(my_init);
module_exit(cleanUp);
MODULE_LICENSE("GPL");
module_param(NUM_DEVICES,int,S_IRUGO);