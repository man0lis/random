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

int be_verbose = 0;
int use_recursive = 0;

int fak_it(int x)
{
	int i;
	int returnvalue = 1;
	for(i=1;i<=x;++i) {
		if (be_verbose == 1) printf("VERB: %d * %d\n",i,returnvalue);
		returnvalue=returnvalue*i;
	}
	return returnvalue;
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
	
	if (use_recursive == 1) {
		printf("result: %d\nused recursive method\n", fak_rk(number));
		return 0;
	}
	else {
		printf("result: %d\nused iterativ method\n", fak_it(number));
		return 0;
	}
}
