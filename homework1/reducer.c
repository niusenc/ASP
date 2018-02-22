#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	int main() {
		char paren[1] = {')'};
		char history[15] = "history        ";
		char entertain[15] = "entertainment  ";
		char cosmetics[15] = "cosmetics      ";
		char sports[15] = "sports         ";
		char photography[15] = "photography    ";
		char art[15] = "art            ";
		int hist_score = 0;
		int enter_score = 0;
		int cos_score = 0;
		int spor_score = 0;
		int pho_score = 0;
		int art_score = 0;
		char ch[200] = {' '};
		char ID[4];
		char topic[15];
		char score[8] = {'\0'};
		char* str_ID;
		char* str_score;
		char* str_topic;
		int groupID;
		int hist_flag = 0;
		int enter_flag = 0;
		int cos_flag = 0;
		int spor_flag = 0;
		int pho_flag = 0;
		int art_flag = 0;			
			gets(ch);
			for(int i = 0; i < 4; i++) {
				ID[i] =  ch[i+1];
			}	
			for(int j = 0; j < 15; j++) {
				topic[j] = ch[j + 6];
			}
			for(int k = 0; ch[k + 22] != ')'; k++) {
				score[k] = ch[k + 22];
			}
		str_ID = ID;
		str_score = score;
		str_topic = topic;
		groupID = atoi(str_ID);//current groupID
		switch(ch[6]) {
			case 'h' :  hist_flag = 1;
					   hist_score += atoi(str_score);
						//printf("%d \n",hist_score);
			           break;
			case 'c' :  cos_flag = 1;
					   cos_score += atoi(str_score);
						//printf("%d \n",cos_score);
				       break;
			case 'e' :  enter_flag = 1;
					   enter_score += atoi(str_score);
						//printf("%d \n",enter_score);
				       break;
			case 's' :  spor_flag = 1;
					   spor_score += atoi(str_score);
						//printf("%d \n",spor_score);
				       break;
			case 'p' :  pho_flag = 1;
					   pho_score += atoi(str_score);
						//printf("%d \n",pho_score);
				       break;
			case 'a' :  art_flag = 1;
					   art_score += atoi(str_score);
						//printf("%d \n",art_score);
				       break;
		}
	
		while(1) { //while start
			int tempID; //read from stdin
			char output[100] = {' '};
			output[0] = '(';
			output[5] = ',';
			output[21] = ',';
			if(gets(ch) != NULL) {
						for(int i = 0; i < 4; i++) {
							ID[i] =  ch[i+1];
						}	
						for(int j = 0; j < 15; j++) {
							topic[j] = ch[j + 6];
						}
						for(int k = 0; ch[k + 22] != ')'; k++) {
							score[k] = ch[k + 22];
						}
						str_ID = ID;
						str_score = score;
						str_topic = topic;
						tempID = atoi(ID);
						if(tempID == groupID) {
				
							switch(ch[6]) {
								case 'h' :  hist_flag = 1;
											//printf("111%s \n",str_score);

										   hist_score += atoi(str_score);
							
										   break;
								case 'c' :  cos_flag = 1;
											//printf("222%s \n",str_score);
								
										   cos_score += atoi(str_score);
								
										   break;
								case 'e' :  enter_flag = 1;
											//printf("333%s \n",str_score);
								
										   enter_score += atoi(str_score);
								
										   break;
								case 's' :  spor_flag = 1;
											//printf("444%s \n",str_score);
								
										   spor_score += atoi(str_score);
								
										   break;
								case 'p' :  pho_flag = 1;
											//printf("555%s \n",str_score);
								
										   pho_score += atoi(str_score);
								
										   break;
								case 'a' :  art_flag = 1;
											//printf("666%s \n",str_score);
								
										   art_score += atoi(str_score);
											//printf("11111+%d \n",hist_score);
											//printf("2222+%d \n",cos_score);
											//printf("3333+%d \n",enter_score);
											//printf("4444+%d \n",spor_score);
											//printf("5555+%d \n",pho_score);
											//printf("66666+%d \n",art_score);
										   break;
							}
							for(int i = 0; i < 200; i++) {
										ch[i] = ' ';
							}
							for(int i = 0; i < 8; i++) {
										score[i] = '\0';
							}
						}
						else {
								printf("\n");
								printf("The result for user %04d is : \n",groupID);
								if(hist_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",hist_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = history[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									hist_flag = 0;
									hist_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(enter_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",enter_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = entertain[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									enter_flag = 0;
									enter_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(cos_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",cos_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = cosmetics[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									cos_flag = 0;
									cos_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(spor_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",spor_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = sports[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									spor_flag = 0;
									spor_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(pho_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",pho_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = photography[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									pho_flag = 0;
									pho_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(art_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",art_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = art[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									art_flag = 0;
									art_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
						
					
								switch(ch[6]) {
								case 'h' :  hist_flag = 1;
											//printf("111%s \n",str_score);

										   hist_score += atoi(str_score);
							
										   break;
								case 'c' :  cos_flag = 1;
											//printf("222%s \n",str_score);
								
										   cos_score += atoi(str_score);
								
										   break;
								case 'e' :  enter_flag = 1;
											//printf("333%s \n",str_score);
								
										   enter_score += atoi(str_score);
								
										   break;
								case 's' :  spor_flag = 1;
											//printf("444%s \n",str_score);
								
										   spor_score += atoi(str_score);
								
										   break;
								case 'p' :  pho_flag = 1;
											//printf("555%s \n",str_score);
								
										   pho_score += atoi(str_score);
								
										   break;
								case 'a' :  art_flag = 1;
											//printf("666%s \n",str_score);
								
										   art_score += atoi(str_score);
											//printf("11111+%d \n",hist_score);
											//printf("2222+%d \n",cos_score);
											//printf("3333+%d \n",enter_score);
											//printf("4444+%d \n",spor_score);
											//printf("5555+%d \n",pho_score);
											//printf("66666+%d \n",art_score);
										   break;
							}
							for(int i = 0; i < 200; i++) {
										ch[i] = '\0';
							}
							for(int i = 0; i < 8; i++) {
										score[i] = '\0';
							}
				
								printf("************************ \n");
								printf("\n");
								printf("Please continue to input user %04d's information \n",tempID);
								groupID = tempID;
					
								 
						}
				}//judge EOF end.
				else {
							printf("\n");
								printf("The result for user %04d is : \n",groupID);
								if(hist_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",hist_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = history[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									hist_flag = 0;
									hist_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(enter_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",enter_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = entertain[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									enter_flag = 0;
									enter_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(cos_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",cos_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = cosmetics[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									cos_flag = 0;
									cos_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(spor_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",spor_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = sports[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									spor_flag = 0;
									spor_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(pho_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",pho_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = photography[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									pho_flag = 0;
									pho_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
								if(art_flag == 1) {
									char temp[4];
									char tempscore[10] = "\0";
									//printf("%d",groupID);
									sprintf(temp,"%04d",groupID);
									sprintf(tempscore,"%d",art_score);
									for(int i = 1; i < 5; i++) {
										output[i] = temp[i - 1];
									}
									for(int i = 6; i < 21; i++) {
										output[i] = art[i - 6];
									}
									strcat(output,tempscore);
									strncat(output,paren,1);
									//printf("The result is : ");
									//printf("******************");
									for(int i = 0; output[i] != '\0'; i++) {
										printf("%c",output[i]);
									}
									//printf("%s",output);
									//printf("******************");
									art_flag = 0;
									art_score = 0;
									for(int i = 0; i < 10; i++) {
										tempscore[i] = '0';
									}
									for(int i = 0; i < 100; i++) {
										output[i] = ' ';
									}
									for(int i = 0; i < 4; i++) {
										temp[i] = '\0';
									}
									//for(int i = 0; i < 8; i++) {
									//	score[i] = '\0';
									//}
									output[0] = '(';
									output[5] = ',';
									output[21] = ',';
									output[22] = '\0';
									printf("\n");
								}
						exit(0);
						
				}
		} //while end
		return 0;
	}
