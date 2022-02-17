/**
 * @file     main.c
 */
/* Embedded Xinu, Copyright (C) 2009, 2022.  All rights reserved. */

#include <xinu.h>

/**
 * Main process.  You can modify this routine to customize what Embedded Xinu
 * does when it starts up.
 */
process main(void)
{
    kprintf("Hello Xinu World!\n");

    kprintf("Enter your codebreaker text:\n");

    // TODO: Put your main program for codebreaker here.
    //       Replace any calls to printf() with kprintf().
    //       Replace any calls to getchar() with kgetc().

    while (1)
        ;

    return 0;
}
