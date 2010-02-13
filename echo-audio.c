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
#include "SDL/SDL.h"
#include "complex.h"
#include "fftw3.h"
#include <signal.h>

typedef struct
{
    SDL_Surface *screen;
    Uint32      color;
    Uint32      color2;
}
paUserData;

#define WINDOW_X 1024
#define WINDOW_Y 200
#define FRAMES_PER_BUFFER 1024

fftw_complex *in, *out;
fftw_plan p;

volatile int stop = 0;

void signalCallback(int i) {
    stop=1;
}

// function that draws a single pixel to a surface
void DrawPixel(SDL_Surface *Surface, int x, int y,Uint16 color)
{
  Uint16 *Pixel;
  Pixel = (Uint16 *)Surface->pixels + y*Surface->pitch/2 + x*2;
  *Pixel = color;
}

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
    // needed for working with the given values
    float *input  = (float *) inputBuffer;
    float *output = (float *) outputBuffer;
    paUserData *data = (paUserData*)userData;
    unsigned int i;
    double max;

    SDL_Surface *waveform;

    // if inputbuffer is not ready yet return
    if(inputBuffer == NULL) {
        return 0;
    }

    // create a black surface
    waveform = SDL_CreateRGBSurface(SDL_SWSURFACE,WINDOW_X,WINDOW_Y,32,0,0,0,0);

    for(i=0;i<framesPerBuffer;i++) {
        // make sure the x does not leave the screen
        int x = i%WINDOW_X;
        // calculate the y values (centered) and make sure y does not
        // leave the screen
        int y = abs((int)(*output*WINDOW_Y/2.0 + WINDOW_Y/2.0) % WINDOW_Y);
        // Put a pixel for the current value to the surface
        DrawPixel(waveform, x, y, data->color);

        // Set output to input
        in[i] = *input;
        *output++ = *input++;
        // twice because we get a sterio signal
        *output++ = *input++;
    }
    
    fftw_execute(p);
    max=0;
    for(i=0;i<framesPerBuffer;i++) {
        if (creal(out[i])>max) max = creal(out[i]);
    }
    
    for(i=0;i<framesPerBuffer;i++) {
        // make sure the x does not leave the screen
        int x = i%WINDOW_X;
        // calculate the y values (centered) and make sure y does not
        // leave the screen
        int y = abs((int)((creal(out[i])/max)*WINDOW_Y)) % WINDOW_Y;
        // Put a pixel for the current value to the surface
        DrawPixel(waveform, x, y, data->color2);
    }    

    // Apply image to screen
    SDL_BlitSurface(waveform, NULL, data->screen, NULL);
    // Update Screen
    SDL_Flip(data->screen);
    // kill the surface
    SDL_FreeSurface(waveform);

    return 0;
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalCallback);
    
    // surface that will hold the background
    SDL_Surface *screen = NULL;

    // initialize SDL video subsystem
    if(  SDL_Init(SDL_INIT_VIDEO) == -1 ) {
        return EXIT_FAILURE;
    }

    // Set up the screen with WINDOW_X*WINDOW_Y px size, 32 bit color and a
    // softwaresurface
    screen = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_SWSURFACE);
    if( screen == NULL ) {
        return EXIT_FAILURE;
    }

    // Set the window caption
    SDL_WM_SetCaption("Echo-Audio v0.1", NULL);

    // Fill user data struct
    paUserData data;
    data.screen = screen;
    data.color = SDL_MapRGB(screen->format,0x00,0xFF,0x00);
    data.color2 = SDL_MapRGB(screen->format,0x00,0xFF,0xFF);

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAMES_PER_BUFFER);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAMES_PER_BUFFER);

    p = fftw_plan_dft_1d(FRAMES_PER_BUFFER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // var for errorCode and the stream that will be used
    PaError errorCode;
    PaStream *stream;
    // initialize internal structures of portaudio
    errorCode = Pa_Initialize();
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        return EXIT_FAILURE;
    }

    // Open the default input and output devices with 2 chanels per
    // device, outputformat Float 32bit, 44100 hz samplerate and 
    // FRAMES_PER_BUFFER frames per buffer. callMeBack is the
    // callbackfunction and no userdata is supplied
    errorCode = Pa_OpenDefaultStream(&stream,2,2,paFloat32,44100.0,FRAMES_PER_BUFFER,callMeBack,&data);
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        Pa_Terminate();
        return EXIT_FAILURE;
    }

    // Start stream processing
    errorCode = Pa_StartStream(stream);
    if (errorCode != paNoError) {
        fprintf(stderr, "FUUUUUUU... %s\n", Pa_GetErrorText(errorCode));
        Pa_CloseStream(stream);
        Pa_Terminate();
        return EXIT_FAILURE;
    }

    while (!stop) {
        Pa_Sleep(300);
    }
    
    // Stop the stream
    Pa_StopStream(stream);
    // Close the stream
    Pa_CloseStream(stream);
    // Kill Portaudio
    Pa_Terminate();

    fftw_destroy_plan(p);

    // Quit SDL
    SDL_Quit();

    printf("Bye.\n");

    return EXIT_SUCCESS;
}
