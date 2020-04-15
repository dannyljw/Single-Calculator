#include<stdio.h>
#include<stdlib.h>
#include<string.h>
	int gcd(int a, int b){
		if(b==0){
		return a;
		}
		else {
		return gcd(b, a%b);
		}
	}

	
	int main(int argc, char *argv[])
	{
		FILE *fp =NULL;
		char *line[100];
		char line2[100][100];
		size_t len = 0;
		ssize_t read;
		char *substr = NULL;
		int value1, value2;
		int R[15]={0, };
		char opcode;
		int i=1;
		int cnt = 0;


			fp=fopen("text.txt", "r");
			if(fp == NULL){
				printf("no such fille: %s\n", "text.txt");
				return 0;
				}

  			for(int j = 0; (read=(getline(&line[j],&len,fp))) != -1; j++){
				printf("\n\n\nthe %dth line of the txt file \n",i);	
				printf("Retrieved line of length %zu :\n ", read);
				
				printf("%s",line[j]);
				strcpy(line2[j], line[j]);
//line has the first line of txt file.		
				if(read >= 7){
					substr = strtok(line[j], " "); 
					printf("opcode : %s\n", substr);
					opcode = *substr;
		

					if(opcode == 'H'){
						printf("this is halt!!! \n");
						return 0;
					}		
//substring contains opcode from now on

					substr = strtok(NULL," ");	 
					printf("opr1: %s\n", substr);
//cut and oprand1 is printed
	
					 if(*substr !='R'){
						value1 = strtol(substr, NULL, 16);
						printf("opr1: 0x%x \n", value1);
						printf("%d\n",value1);
					}
					else {
						i=atoi(substr+1);
//making an index
						value1=R[i];
						printf("R[%d] is %d \n",i, R[i]);
					}			
//oprand1 has stored perfectely
					
					substr = strtok(NULL, " ");
					printf("opr2: %s", substr);
	
					if(*substr != 'R'){
						value2= strtol(substr, NULL, 16);
						printf("opr2: 0x%x \n", value2);
						printf("%d\n", value2);
					}
					
					else {
//code about indexing R
						i=atoi(substr +1);
						value2 = R[i];
						printf("R[%d] is %d \n", i ,R[i]);
					}
				}
			
				else{
					substr = strtok(line[j], " "); 
					printf("opcode : %s\n", substr);
					opcode = *substr;

					if(opcode == 'J'){
						substr = strtok(NULL, " ");
						value1 = strtol(substr, NULL, 16);
						printf("Jump to -> %s\n", line2[value1-1]);
						strcpy(line[value1-1], line2[value1-1]);
						
						substr = strtok(line[value1-1], " ");
						opcode = *substr;
						printf("opcode : %s\n", substr);
						substr = strtok(NULL, " ");
						printf("opr1: %s\n", substr);

						 if(*substr !='R'){
							value1 = strtol(substr, NULL, 16);
							printf("opr1: 0x%x \n", value1);
							printf("%d\n",value1);
						}
						else {
							i=atoi(substr+1);
//making an index
							value1=R[i];
							printf("R[%d] is %d \n",i, R[i]);
						}
						substr = strtok(NULL, " ");
						printf("opr2: %s", substr);

						 if(*substr !='R'){
							value2 = strtol(substr, NULL, 16);
							printf("opr2: 0x%x \n", value2);
							printf("%d\n",value2);
						}
						else {
							i=atoi(substr+1);
//making an index
							value1=R[i];
							printf("R[%d] is %d \n",i, R[i]);
						}

					}

					else{
						if(opcode == 'H'){
						printf("this is halt!!! \n");
						return 0;
						}		
//substring contains opcode from now on

						substr = strtok(NULL," ");	 
						printf("opr1: %s\n", substr);
//cut and oprand1 is printed
	
						 if(*substr !='R'){
							value1 = strtol(substr, NULL, 16);
							printf("opr1: 0x%x \n", value1);
							printf("%d\n",value1);
						}
						else {
							i=atoi(substr+1);
//making an index
							value1=R[i];
							printf("R[%d] is %d \n",i, R[i]);
						}
					}			
				}
	
				switch (opcode){
				case '+':
					R[0] = value1 + value2;
					break;
				case '-':
					R[0] = value1 - value2;
					break;
				case '*':
					R[0] = value1 * value2;
					break;
				case '/':
					if(value2 !=0){
					R[0] = value1 / value2;
					}
					else{
						printf("error!!! \nyour number contains 0 in it \n");
					}
					break;

				case 'M':
					printf("++++++doing MOV operation++++++\n");
					R[i] = value2;
					printf("R[%d] is %d\n", i, R[0]);
					printf("R[%d] = %d \n", i, value2);
					break;				
				case 'G':
					gcd(value1, value2);
					printf("GCD will be %d\n", gcd(value1, value2));
					break;
				case 'C':
					if (value1 == value2){
						R[0]=0;
						printf("\nBy compare op21=opr2, R[0] will become %d\n",R[0]);
						}
					else if (value1 > value2){
						R[0]=1;
						printf("\nBy compare opr1>opr2, R[0] will become %d\n",R[0]);				
						}
					else if (value1 < value2){
						R[0]=-1;
						printf("\nBy compare opr1<opr2, R[0] will become %d\n",R[0]);
						}
					break;	
				default:
					break;
				}
		printf("The result is %d\n", R[0]);		


		value1=0;
		value2=0;
		i++;
		}

	fclose(fp);        
	return 0;
}

