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

int main(int argc, char **argv)
{
	if(argc == 2) {
		//check number
		if(checknumber(argv[1]) == 0) {
			//calc series
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
