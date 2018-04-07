#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapper.c"
#include <semaphore.h>
#include <sys/mman.h>

extern char buffer[200][26];
extern int countLine;
int *head;
int *tail;
int bufferSize;
int numOfReducer;
int *numOfUser;
char result[120][27] = {'\0'};

int numOfConsumer = 0;
int *endOfRead;


pthread_mutex_t *lock;

pthread_cond_t *full;

pthread_cond_t *empty;

pthread_condattr_t condattr;

pthread_mutexattr_t mutexattr;

int consumer();

void *mapper() {
	while(1) {

		pthread_mutex_lock(lock);
		if(*endOfRead == 1) {
			pthread_mutex_unlock(lock);
			break;
		}
		if(*tail == countLine) {
			*endOfRead = 1;
			pthread_cond_broadcast(empty);
			pthread_cond_broadcast(full);
			pthread_mutex_unlock(lock);
			break;
		}
		while((*tail) - (*head) == bufferSize - 1) {
			pthread_cond_wait(full,lock);
		}
		(*tail)++;

		//printf("mapper : %d \n",tail);
		pthread_cond_signal(empty);
		pthread_mutex_unlock(lock);
	}
	return 0;
}

void *reducer() {
	//printf("hi reducer \n");
	while(1) {
		pthread_mutex_lock(lock);
		while((*tail) - (*head) == 0 && (*endOfRead) != 1) {
			pthread_cond_wait(empty,lock);
		}
		if((*endOfRead) == 1 && (*tail) - (*head) == 0) {
			pthread_mutex_unlock(lock);
			break;
		}
		consumer();
		(*head)++;
		//printf("reducer : %d \n",head);
		pthread_cond_signal(full);
		pthread_mutex_unlock(lock);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	numOfConsumer = atoi(argv[2]);
	bufferSize = atoi(argv[1]);
	char *filename = (char *)argv[3];
	producer(filename);

	/* initialize the mutex and condation variable */


	lock = (pthread_mutex_t *)mmap(NULL,sizeof(pthread_mutex_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,-1,0);
	full = (pthread_cond_t *)mmap(NULL,sizeof(pthread_mutex_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,-1,0);
	empty = (pthread_cond_t *)mmap(NULL,sizeof(pthread_mutex_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,-1,0);
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_setpshared(&mutexattr,PTHREAD_PROCESS_SHARED);
	pthread_condattr_init(&condattr);
	pthread_condattr_setpshared(&condattr,PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(lock,&mutexattr);
	pthread_cond_init(full,&condattr);
	pthread_cond_init(empty,&condattr);

	
	/* first establish buffer i, then fork consumer i */

	int x = 1;
	int tempFlag = 0; // flag to show whether mapper is implmented.
	int fatherpid;
	head = (int *)mmap(NULL,sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	tail = (int *)mmap(NULL,sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	endOfRead = (int *)mmap(NULL,sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	numOfUser = (int *)mmap(NULL,sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	*endOfRead = 0;
	*head = 0;
	*tail = 0;
	*numOfUser = 0;

	while(x > 0 && numOfConsumer > 0) { //establish multiple processes;

		x = fork();
		if(x > 0) { //parent process
			//fatherpid = getpid();
			//printf("father pid is %d \n",getpid());
			numOfConsumer--;
			if(tempFlag == 0) {
				//printf("countline is %d \n",countLine);
				mapper();
				tempFlag = 1;
			}
			
			
		}

		else  { // child process
			//printf("consumer is %d \n",numOfConsumer);
			reducer();
		}

	}
	//printf("hello");
		//printf("pid is %d \n",getpid());
	
		//printf("pid is %d \n",getpid());
	if(result[0][0] != '\0') {
		for(int i = 0; i < *numOfUser; i++) {
				for(int j = 0; j < 26;j++) {
					printf("%c",result[i][j]);
				}
			printf("\n");
		}
	}
	return 0;
}


int consumer() {
			char paren[1] = {'\0'};
			int flag = 0;
			char score[10] = {'\0'};
			for(int k = 0; buffer[*head][k + 22] != ')'; k++) {
				score[k] = buffer[*head][k + 22];
			}

			if(*numOfUser == 0) {
				for(int i = 0; i < 26; i++) {
					result[0][i] = buffer[0][i];
				}
				(*numOfUser)++;
			}

			else {

				for(int i = 0; i < *numOfUser; i++) {
					if(strncmp(buffer[*head],result[i],22) == 0) {
							char resScore[15] = {'\0'};
							int tempscore = 0;
							for(int k = 0; result[i][k + 22] != ')'; k++) {
								resScore[k] = result[i][k + 22];
							}
							//printf("score is %d\n",atoi(score));
							//printf("resScore is %s\n",resScore);
							tempscore = atoi(score) + atoi(resScore);
							//printf("the tempscore is %d \n",tempscore);
							sprintf(resScore,"%d",tempscore);
							//printf("RESCORE is %s\n",resScore);
							//for(int k = 0; result[i][k + 22] != ')'; k++) {
							//	result[i][k + 22] = resScore[k];
							//}
							for(int j = 0 ; result[i][j + 22] != ')'; j++) {
									result[i][j + 22] = '\0';
							}

							for(int k = 0; resScore[k] != '\0'; k++) {
								result[i][k + 22] = resScore[k];
							}
							//strncat(result[i],paren,1);

							flag = 1;
							for(int i = 0; i < 15; i++) {
								resScore[i] = '\0';
							}
							break;
					}
				}

				if(flag == 0) {
					for(int i = 0; i < 26 ; i ++) {
						result[*numOfUser][i] = buffer[*head][i];
					}
					(*numOfUser)++;
				}

				flag = 0;


			}
			return 0;

			
}