//      compare.c
//      
//      Copyright 2010 Robin Nehls <nehls@mi.fu-berlin.de>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This functions compares 2 strings and returns how many char are the 
// same in percent. Stings may have different length. In this case chars
// will be compared until one sting runs out of chars
float percent_the_same(char* str1, char* str2) {
	unsigned int i, total=0, same=0;
	if (str1 == NULL || str2 == NULL) {
		return -1.0;
	}
	for (i=0; str1[i] != 0 && str2[i] != 0 ;++i) {
		total++;
		if (str1[i] == str2[i]) {
			same++;
		}
	}
	return ((float)same/(float)total)*100.0;
}

// This function compares 2 strings and returnes the total of chars each
// pair of chars are appart.
int chars_appart(char* str1, char* str2) {
	unsigned int i, total=0;
	if (str1 == NULL || str2 == NULL) {
		return -1;
	}
	for (i=0; str1[i] != 0 && str2[i] != 0 ;++i) {
		total += abs(str1[i]-str2[i]);
	}
	return total;
}

int minimum(int a, int b, int c) {
	int min=a;
	if(b<min) {
		min=b;
	}
	if(c<min) {
		min=c;
	}
	return min;
}

// This funktion returns the levenshtein distance of 2 given strings
int levenshtein_distance(char* s,char* t) {
	int k,i,j,n,m,cost,*d,distance;
	n=strlen(s)+1; 
	m=strlen(t)+1;
	if(n != 0 && m != 0) {
		d=malloc((sizeof(int))*(m)*(n));
		
		for(k=0;k<n;k++) {
			d[k]=k;
		}
		
		for(k=0;k<m;k++) {
			d[k*n]=k;
		}
		
		for(i=1;i<n;i++) {
			for(j=1;j<m;j++) {
				if(s[i-1]==t[j-1]) {
					cost=0;
				}
				else {
					cost=1;
				}
				d[j*n+i]=minimum(d[(j-1)*n+i]+1,d[j*n+i-1]+1,d[(j-1)*n+i-1]+cost);
			}
		}
		distance=d[n*m-1];
		free(d);
		return distance;
	}
	else {
		return 0;
	}
}
