#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

//TAILQ_HEAD(tail_list, tail_entry) head = TAILQ_HEAD_INITIALIZER(head);
//struct tail_entry {
//	TAILQ_ENTRY(tail_entry) next;
//	char str[200];
//};

//struct tail_entry n1;
//n1 = malloc(sizeof(struct tail_entry));
//struct tail_entry *np;

char buffer[200][26] = {'\0'};
int countLine = 0;
void producer(char* filename) {
	
	FILE *fp;
	char ch;
	//char* filename[15];
	char temp[24];
	int count = 0;
	//printf("enter the filename to be opened \n");
	//scanf("%s", filename);
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("cannot open file \n");
		exit(0);
	}
	ch = fgetc(fp);
	while (ch != EOF) {
		temp[count] = ch;
		count++;
		if (count == 24) {
			int i = 0;
			while (temp[i] != ' ') {
				i++;
			}
			char output[26] = {'\n'};
			char tempoutput[25] = {'\n'};
			for (int k = 0; k < 6; k++) {
				output[k] = temp[k];
			}
			for (int k = 6; k < i - 2; k++) {
				output[k] = temp[k + 2];
			}
			for(int k = i - 2; k < 21; k++) {
				output[k] = ' ';
			}
			switch (temp[6]) {
			case 'P': output[22] = '5';
				output[23] = '0';
				output[24] = ')';
				output[21] = ',';
				break;
			case 'L': output[22] = '2';
				output[23] = '0';
				output[24] = ')';
				output[21] = ',';
				break;
			case 'D': output[21] = ',';
				output[22] = '-';
				output[23] = '1';
				output[24] = '0';
				output[25] = ')';
				break;
			case 'S': output[22] = '4';
				output[23] = '0';
				output[24] = ')';
				output[21] = ',';
				break;
			case 'C': output[22] = '3';
				output[23] = '0';
				output[24] = ')';
				output[21] = ',';
				break;
			}
			if(temp[6] == 'D') {
				for (int j = 0; j < 26; j++) {
					//printf("%c", output[j]);
					//n1.str[j] = output[j];
					buffer[countLine][j] = output[j];

				}
				countLine++;
				//strcpy(n1.str, output);
			}
			else {
				for(int n = 0; n < 26; n++) {
					//tempoutput[n] = output[n];
					//printf("%c", tempoutput[n]);
					//n1.str[n] = output[n];
					buffer[countLine][n] = output[n];
				}
				countLine++;
				//strcpy(n1.str, output);
			}

			//printf("\n");
			count = 0;
			ch = fgetc(fp);
			
		}
		ch = fgetc(fp);
		if(ch == EOF) {
			return;
		}
	}


	fclose(fp);
}
