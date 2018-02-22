#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE *fp;
	char ch;
	char filename[15];
	char temp[24];
	int count = 0;
	//printf("enter the filename to be opened \n");
	//scanf("%s", filename);
	fp = fopen(argv[1], "r");
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
			char output[25] = {' '};
			char tempoutput[24] = {' '};
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
					printf("%c", output[j]);
				}
			}
			else {
				for(int n = 0; n < 25; n++) {
					tempoutput[n] = output[n];
					printf("%c", tempoutput[n]);
				}
			}
			printf("\n");
			count = 0;
			ch = fgetc(fp);
		}
		ch = fgetc(fp);
	}
	fclose(fp);
	return 0;
}
