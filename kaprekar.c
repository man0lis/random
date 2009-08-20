#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checknumber(char* value)
{
	int x; 		//counter in forloops
	char check;	//check character for last for
	//check if number is 4 digits long
	if(strlen(value) != 4) {
		printf("The number must be 4 digits long.\n");
		return 1;
	}
	
	//check if string only contains numbers
	for(x=strlen(value)-1;x>=0;--x) {
		//check if every digit if between 0 and 9 (in ascii code)
		if(value[x] < 48 || value[x] > 57) {
			printf("Value contains invalid chars\n");
			return 1;
		}
	}
	
	//check if all numbers are the same
	check = value[0];
	for(x=strlen(value)-1;x>0;--x) {
		if(check != value[x]) {
			return 0;
		}
	}
	printf("The number must consist of at least 2 different digits.\n");
	return 1;
}

void bubbleSort(char* array, int array_size, int type)
{
	int i, j, temp;

	for (i = (array_size - 1); i > 0; i--) {
		for (j = 1; j <= i; j++) {
			if(type == 1) {
				if (array[j-1] < array[j]) {
					temp = array[j-1];
					array[j-1] = array[j];
					array[j] = temp;
				}
			}
			else {
				if (array[j-1] > array[j]) {
					temp = array[j-1];
					array[j-1] = array[j];
					array[j] = temp;
				}
			}
		}
	}
}


int main(int argc, char **argv)
{
	if(argc == 2) {
		//check number
		if(checknumber(argv[1]) == 0) {
			
			char number_buf_1[5];
			char number_buf_2[5];
			char result_buf[5];
			int number1;
			int number2;
			int result;
			
			//initial copy of the given value to the resultbuffer
			strcpy(result_buf,argv[1]);
			
			//calc series
			while(result != 6174) {
				//copy last result into numberbuffers
				strcpy(number_buf_1,result_buf);
				strcpy(number_buf_2,result_buf);
				//sort number_buf_1 ascending
				bubbleSort(number_buf_1,4,1);
				//sort number_buf_2 descending
				bubbleSort(number_buf_2,4,2);
				//convert buffer to actual numbers
				number1 = atoi(number_buf_1);
				number2 = atoi(number_buf_2);
				//calc result
				result = number1 - number2;
				//print current calculation
				printf("%d - %d = %d\n",number1,number2,result);
				//write result in the result_buffer
				sprintf(result_buf,"%04d",result);
			}
			printf("7641 - 1467 = 6174\n");
			printf("Found Equilibrium. Be happy :)\n");
			
		}
		else {
			printf("The entered value %s is not valid\n",argv[1]);
			return 1;
		}
	}
	else {
		printf("Usage: %s <number>\n",argv[0]);
		printf("Number have to consist of 4 digits (but not all the same) Leading zeros are allowed.\n");
		return 1;
	}
	return 0;
}
