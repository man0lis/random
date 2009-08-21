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

int fak_it(int x)
{
	int i;
	int returnvalue = 1;
	for(i=1;i<=x;++i) {
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
	int ergebnis;
	printf("Berechne fak(10) Iterativ\n");
	ergebnis=fak_it(10);
	printf("Ergebnis: %d\n", ergebnis);
	printf("Berechne fak(10) Rekursiv\n");
	ergebnis=fak_rk(10);
	printf("Ergebnis: %d\n", ergebnis);

	return 0;
}
