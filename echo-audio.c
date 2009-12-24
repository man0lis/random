//      echo-audio.c
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
#include "portaudio.h"

// this callbackfunction is called by portaudio whenever a new buffer
// is ready for processing
static int callMeBack(void *inputBuffer,
                      void *outputBuffer,
                      unsigned long framesPerBuffer,
                      PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData
                     )
{
    //needed for reading the arrays
    float *input  = (float *) inputBuffer;
    float *output = (float *) outputBuffer;
    unsigned int i;
    
    //if inputbuffer is not ready yet return
    if(inputBuffer == NULL) {
        return 0;
    }
    
    for(i=0;i<framesPerBuffer;i++) {
        //Set output to input
        *output++ = *input++;
        //twice because we get a sterio signal
        *output++ = *input++;
    }
    return 0;
}

int main(int argc, char** argv)
{
    PaError errorCode;
    PaStream *stream;
    
	//initialize internal structures of portaudio
    errorCode = Pa_Initialize();
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        return EXIT_FAILURE;
    }
    
    // Open the default input and output devices with 2 chanels per
    // device, outputformat Float 32bit, 44100 hz samplerate and 512
    // frames per buffer. callMeBack is the callbackfunction and no
    // userdata is supplied
    errorCode = Pa_OpenDefaultStream(&stream,2,2,paFloat32,44100.0,512,callMeBack,NULL);
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        Pa_Terminate();
        return EXIT_FAILURE;
    }
    
    //Start stream processing
    errorCode = Pa_StartStream(stream);
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        Pa_CloseStream(stream);
        Pa_Terminate();
        return EXIT_FAILURE;
    }
    
    //Wait for 20sec
    //TODO: make a wait for signal
    Pa_Sleep(20000);
    
    //Stop the stream
    Pa_StopStream(stream);
    //Close the stream
    Pa_CloseStream(stream);
    //Kill Portaudio
    Pa_Terminate();
	return EXIT_SUCCESS;
}
