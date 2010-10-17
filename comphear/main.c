//      main.c
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
#include <ofa1/ofa.h>

#include "wavfile.h"
#include "compare.h"

int main(int argc, char** argv) {
	
	if (argc != 3) {
		printf("Usage: %s file1.wav file2.wav\n",argv[0]);
		return 1;
	}
	
	struct audio_data *data1 = load_wave(argv[1]);
	if (data1 == NULL) {
		printf("Could not load wave file: %s\n",argv[1]);
		return 1;
	}
	
	struct audio_data *data2 = load_wave(argv[2]);
	if (data2 == NULL) {
		printf("Could not load wave file: %s\n",argv[2]);
		return 1;
	}
	
	const char *print1 = ofa_create_print(data1->sampels,data1->byte_order,data1->size,data1->sample_rate,data1->is_sterio);
	char *myprint1 = malloc(strlen(print1));
	strcpy(myprint1,print1);
	const char *print2 = ofa_create_print(data2->sampels,data2->byte_order,data2->size,data2->sample_rate,data2->is_sterio);
	char *myprint2 = malloc(strlen(print2));
	strcpy(myprint2,print2);
	
	printf("Fingerprint1:\n%s\n", myprint1);
	printf("Fingerprint2:\n%s\n", myprint2);
	
	printf("Fingerprints are %f%% the same\n",percent_the_same(myprint1, myprint2));
	printf("Fingerprints are %d chars apart\n",chars_appart(myprint1, myprint2));
	printf("The levenshtein distance of the Fingerprints is %d\n",levenshtein_distance(myprint1, myprint2));
	
	return 0;
}
