/*
 *      powers.c
 *      
 *      Copyright 2009 Robin Nehls <nehls@mi.fu-berlin.de>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <sys/ioctl.h> 

int print_with_line(char* str)
{
	//This code trys to get the size of the terminal
	//and prints the given string with a line to the
	//of the terminal
	struct winsize ws;
	if (!ioctl(0,TIOCGWINSZ,&ws)) {
		int x,length;
		length = ws.ws_col - strlen(str);
		printf("%s",str);
		for(x=0;x<length;x++) {
			printf("-");
		}
		printf("\n");
	}
	else {
		printf("%s\n",str);
	}
	
	return 0;
}

int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("Use: %s <number> <limit> [-v]\n",argv[0]);
		return 1;
	}
	
	int i,limit;
	char str[255];
	
	//Define variables for the big numbers
	mpz_t result;
	mpz_t input;

	//Init it and set it to a value from a str
	mpz_init_set_str (input, argv[1], 10);
	mpz_init_set_str (result, argv[1], 10);
	
	limit = atoi(argv[2]);
	
	for(i=2;i<=limit;i++){
		//Multiplay the numbers
		mpz_mul(result,input,result);
		//Write result to stout if output is not disabled
		if (argc == 4) {
			sprintf(str,"-[ %s^%d ]-",argv[1],i);
			print_with_line(str);
			mpz_out_str(NULL,10,result);
			printf("\n");
		}
	}

    printf("\nresult: ");
    mpz_out_str(NULL,10,result);
    printf("\n");
	
	//Clean up
	mpz_clear(result);

	return 0; 
}
