//      wavefile.c
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
#include <ofa1/ofa.h>

#include "wavfile.h"

struct audio_data* load_wave(char* filename) {
	
	FILE *f = fopen(filename,"r");
	
	if (!f) {
		printf("Could not open file\n");
		return NULL;
	}
	
	unsigned char hdr[36];
	
	if (!fread(hdr,36,1,f)) {
		printf("Could now read wave header\n");
		fclose(f);
		return NULL;
	}
	
	int wave_type = hdr[20] + (hdr[21] << 8);
	// Type 1 is PCM/Uncompressed
	if (wave_type != 1) {
		printf("wave file does not seem to be PCM/Uncompressed\n");
		fclose(f);
		return NULL;
	}
	
	int channels = hdr[22] + (hdr[23] << 8);
	if (channels < 1 || channels > 2) {
		printf("Only mono or sterio wave files supported\n");
		fclose(f);
		return NULL;
	}
	
	int bits = hdr[34] + (hdr[35] << 8);
	if (bits != 16) {
		printf("Olny 16 bit wave files are supported\n");
		fclose(f);
		return NULL;
    }
	
	long extraBytes = hdr[16] + (hdr[17] << 8) + (hdr[18] << 16) + (hdr[19] << 24) - 16;
	//skip header
	if (fseek(f,36 + extraBytes, SEEK_SET) == -1) {
		printf("Could not skip header\n");
		fclose(f);
		return NULL;
	}
	
	unsigned char b[8];
	if (!fread(b,8,1,f)) {
		printf("Strange wave file.\n");
		fclose(f);
		return NULL;
	}
	
	if (b[0] == 'f' && b[1] == 'a' && b[2] == 'c' && b[3] == 't') {
		// Skip the fact block
		if (!fseek(f, 36 + extraBytes + 12, SEEK_SET)) {
			printf("Strange wave file.\n");
			fclose(f);
			return NULL;
		}
		//read next frame
		if (!fread(b,8,1,f)) {
			printf("Strange wave file.\n");
			fclose(f);
			return NULL;
		}
	}
	
	if (b[0] != 'd' || b[1] != 'a' || b[2] != 't' || b[3] != 'a') {
		printf("Strange wave file.\n");
		fclose(f);
		return NULL;
	}
	
	long bytes = b[4] + (b[5] << 8) + (b[6] << 16) + (b[7] << 24);
	long sample_rate = hdr[24] + (hdr[25] << 8) + (hdr[26] << 16) + (hdr[27] << 24);
	int sampleSize = 135;
	long bytesInNSecs = sampleSize * sample_rate * 2 * channels;
	bytes = bytes > bytesInNSecs ? bytesInNSecs : bytes;
	
	struct audio_data *data = malloc(sizeof(struct audio_data));
	
	data->sample_rate = sample_rate; 
	data->byte_order = OFA_LITTLE_ENDIAN;
	data->size = bytes/2;
	data->is_sterio = (channels == 2 ? 1 : 0);
	data->sampels = malloc(bytes);
	if (!fread(data->sampels,bytes,1,f)) {
		printf("Close, but no cigar. Failed to read the actual data");
		fclose(f);
		free(data->sampels);
		free(data);
		return NULL;
	}
	
	return data;
};
