/*
 *      fak.c
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int be_verbose = 0;
int use_recursive = 0;

void fak_it(mpz_t *x)
{
	mpz_t i;
	mpz_t returnvalue;
	
	mpz_init_set_ui(returnvalue, 1);
	
	for(mpz_init_set_ui(i,1); mpz_cmp(i,*x)<=0; mpz_add_ui(i,i,1)) {
		if (be_verbose == 1) {
			printf("VERB: ");
			mpz_out_str(NULL,10,i);
			printf(" * ");
			mpz_out_str(NULL,10,returnvalue);
			printf("\n");
		}
		mpz_mul(returnvalue,returnvalue,i);
	}
	mpz_set(*x,returnvalue);

	//cleanup
	mpz_clear(i);
	mpz_clear(returnvalue);
}

int fak_rk(int x)
{
	if(x <= 1) {return 1;}
	else {return x*fak_rk(x-1);}
}

int main(int argc, char** argv)
{	
	if ((argc < 2) || (argc > 3)) {
		printf("Usage: %s <number> [-r|-v]\n\n-r Use recursive calculation method\n-v Use iterativ with verbose output\n", argv[0]);
		return 1;
	}	
	
	if (argc == 3) {
		if (!strcmp(argv[2],"-r")) {
			be_verbose = 0;
			use_recursive = 1;
		}
		if (!strcmp(argv[2],"-v")) {
			be_verbose = 1;
			use_recursive = 0;
		}
	}
	
	int number = atoi(argv[1]);
	
	if (number == 0) {
		printf("Usage: %s <number> [-r|-v]\n\n-r Use recursive calculation method\n-v Use iterativ with verbose output\n", argv[0]);
		return 1;		
	}
	
	mpz_t num;
	mpz_init_set_str (num, argv[1], 10);
	
	if (use_recursive == 1) {
		printf("result: %d\nused recursive method\n", fak_rk(number));
	}
	else {
		fak_it(&num);
		if(be_verbose) printf("result: ");
		mpz_out_str(NULL,10,num);
		printf("\n");
		if(be_verbose) printf("used iterativ method\n");
	}

	mpz_clear(num);

	return 0;
}
