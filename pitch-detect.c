//      pitch-detect.c
//
//      Copyright 2009 Robin Nehls <nehls@mi.fu-berlin.de>
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
#include <portaudio.h>
#include <fftw3.h>

#define VERSION "v0.1"

int main(int argc, char* argv[]) {
    //print version strings of linked libs
    printf("Pitch Detect %s\nUsing: %s and %s\n",VERSION, Pa_GetVersionText(),
            fftw_version);

    //initialize internal structures of portaudio
    PaError errorCode;
    fprintf(stderr, "Portaudio init: ");
    errorCode = Pa_Initialize();
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        return EXIT_FAILURE;
    }
    fprintf(stderr, "done.\n");





    //terminate portaudio
    fprintf(stderr, "Portaudio kill: ");
    errorCode = Pa_Terminate();
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
    }
    else {
        fprintf(stderr, "done.\n");
    }

    return EXIT_SUCCESS;
}
