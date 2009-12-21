//      lissajous.c
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


#include <stdio.h>
#include <math.h>

#define SCALEX 1
#define SCALEY 1

double lissajous_x(double t, int a, double delta)
{
    return SCALEX * sin(a*t+delta);
}

double lissajous_y(double t, int b)
{
    return SCALEY * sin(b*t);
}

int main(int argc, char** argv)
{
	double t,a=2,b=3,delta=0;
    if(argc==3) {
        a=atoi(argv[1]);
        b=atoi(argv[2]);
    }
    FILE *output,*dem = fopen("lissajous.dem", "w");
    char str[100];
    fprintf(dem,"set term png notransparent\n");
    for(delta=0;delta<M_PI*2;delta+=0.01) {
        sprintf(str,"lissajous%03.0f.out",delta*100);
        output = fopen(str, "w");
        for(t=0;t<=100;t+=0.01) {
            fprintf(output,"%f %f\n",lissajous_x(t,a,delta),lissajous_y(t,b));
        }
        fclose(output);
        fprintf(dem,"set out \"%s.png\"\n",str);
        fprintf(dem,"plot\"%s\" with line title \"%.2f\"\n",str,delta);
    }
    fprintf(dem,"!rm lissajous*.out\n");
    fprintf(dem,"!ffmpeg -r 25 -i lissajous%%3d.out.png -y -an lissajous.avi\n");
    fprintf(dem,"!rm lissajous*.out.png\n");
    fprintf(dem,"!rm lissajous.dem\n");
    fclose(dem);
    system("gnuplot lissajous.dem");
	return 0;
}
