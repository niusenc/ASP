#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapper.c"
#include <semaphore.h>


extern char buffer[200][26];
extern int countLine;
int head = 0;
int tail = 0;
int bufferSize;
int numOfReducer;
int numOfUser = 0;
char result[120][27] = {'\0'};
//char cpbuffer[100][26];
//pthread_cond_t full;
//pthread_cond_t empty;
/* implement the queue */
//STAILQ_HEAD(tail_list, tail_entry) head = STAILQ_HEAD_INITIALIZER(head);
//struct tail_list *headp;

//struct tail_entry {
//	STAILQ_ENTRY(tail_entry) next;
//	char str[200];
//};
	//extern struct tail_entry n1;
	//extern struct tail_entry n2;
	//extern struct tail_entry *np;
//pthread_mutex_t lock;
//int numberOfItems = 0;
//char cpbuffer[countLine][26];

sem_t binSem;
sem_t full;
sem_t empty;
int endOfRead = 0;

int consumer();

void *mapper(void *t) {
	/*char *line = malloc(500);
	ssize_t len;
	sleep(3);
	int read = getline(&line, &len, stdin);
	printf("%s", line);*/
	//char *filename[] = (char *)t;
	/*while(1) {
		pthread_mutex_lock(&lock);
		if(numberOfItems == countLine) {
			break;
		}
		//printf("hi mapper \n");
		pthread_mutex_unlock(&lock);
	}*/
	//for(int i = 0; i < countLine; i++) {
	//	for(int j = 0; j < 26; j++) {
	//		printf("%c",buffer[i][j]);
	//		}
	//		printf("\n");
	//	}	
	//printf("hi mapper \n");
	while(1) {
		sem_wait(&binSem);
		if(endOfRead == 1) {
			sem_post(&binSem);
			break;
		}
		if(tail == countLine) {
			endOfRead = 1;
			for(int i = 0; i < numOfReducer; i++) {
				sem_post(&empty);
				sem_wait(&full);
			}
			sem_post(&binSem);
			break;
		}
		while(tail - head == bufferSize - 1) {
			sem_post(&binSem);
			sem_wait(&full);
			sem_wait(&binSem);
		}
		tail++;
		//printf("mapper : %d \n",tail);
		sem_post(&empty);
		sem_post(&binSem);
	}
	return 0;
}

void *reducer(void *t) {
	//printf("hi reducer \n");
	while(1) {
		sem_wait(&binSem);
		while(tail - head == 0 && endOfRead != 1) {
			sem_post(&binSem);
			sem_wait(&empty);
			sem_wait(&binSem);
		}
		if(endOfRead == 1 && tail - head == 0) {
			sem_post(&binSem);
			break;
		}
		consumer();
		head++;
		//printf("reducer : %d \n",head);
		sem_post(&full);
		sem_post(&binSem);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	//int temp = countLine;
	sem_init(&binSem,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,0);
	char *filename = (char *)argv[3];
	producer(filename);
	/*for(int i = 0; i < countLine; i++) {
		for(int j = 0; j < 26; j++) {
			printf("%c",buffer[i][j]);
			}
			printf("\n");
		}*/
	//printf("%s \n", buffer[12]);
	 bufferSize = atoi(argv[1]);
	 numOfReducer = atoi(argv[2]);
	pthread_t callThd[numOfReducer + 1];
	pthread_create(&callThd[0], NULL, mapper, (void *)argv[3]); /*create mapper thread */
	/* create reducer threads */
	for(long i = 1; i < numOfReducer + 1; i++) {
		pthread_create(&callThd[i], NULL, reducer, (void *)i);
	}
	/* wait on the other threads */
	for(long i = 0; i < numOfReducer + 1; i++) {
		pthread_join(callThd[i], NULL);
	}

		for(int i = 0; i < numOfUser; i++) {
			for(int j = 0; j < 26;j++) {
				printf("%c",result[i][j]);
			}
		printf("\n");
	}


	pthread_exit(NULL);
	
	return 0;

}


int consumer() {
			char paren[1] = {'\0'};
			int flag = 0;
			char score[10] = {'\0'};
			for(int k = 0; buffer[head][k + 22] != ')'; k++) {
				score[k] = buffer[head][k + 22];
			}

			if(numOfUser == 0) {
				for(int i = 0; i < 26; i++) {
					result[0][i] = buffer[0][i];
				}
				numOfUser++;
			}

			else {

				for(int i = 0; i < numOfUser; i++) {
					if(strncmp(buffer[head],result[i],22) == 0) {
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
						result[numOfUser][i] = buffer[head][i];
					}
					numOfUser++;
				}

				flag = 0;


			}
			return 0;

			
}