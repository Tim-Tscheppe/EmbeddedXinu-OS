/**
 * COSC 3250 - Project 3
 * Inner workings of kprintf.c.
 * @author Sam Schulz, Tim Tscheppe
 * Instructor Dennis Brylow
 * TA-BOT:MAILTO samuel.schulz@marquette.edu, timothy.tscheppe@marquette.edu
 */

/**
 * @file kprintf.c
 */

/* Embedded Xinu, Copyright (C) 2009, 2022.  All rights reserved. */

#include <xinu.h>

/**
 * Synchronously read a character from a UART.  This blocks until a character is
 * available.  The interrupt handler is not used.
 *
 * @return
 *      The character read from the UART cast to an <code>int</code>.
 *      If ASCII value 4 is seen, return special constant EOF instead.
 */
syscall kgetc(void)
{
    volatile struct pl011_uart_csreg *regptr;

    /* Pointer to the UART control and status registers.  */
    regptr = (struct pl011_uart_csreg *)0x3F201000;

    // TODO: Check UART flags register, and
    //       once the receiver is not empty, get and return character c.
    //       If ASCII value 4 is seen, return special constant EOF instead.
    
	while (regptr -> fr & PL011_FR_RXFE)
	{}
	
	int c = 0;
	c = regptr -> dr;

	if (c == 4)
	{
		return EOF;
	}
		
	else
	{
		return c;
	}

	return SYSERR;
}

/**
 * kcheckc - check to see if a character is available.
 * @return true if a character is available, false otherwise.
 */
syscall kcheckc(void)
{
    volatile struct pl011_uart_csreg *regptr;
    regptr = (struct pl011_uart_csreg *)0x3F201000;

    // TODO: Check the UART for characters, and return true or false.

	if (regptr -> fr & PL011_FR_RXFF)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
	
    return SYSERR;
}

/**
 * Synchronously write a character to a UART.  This blocks until the character
 * has been written to the hardware.  The interrupt handler is not used.
 *
 * @param c
 *      The character to write.
 *
 * @return
 *      The character written to the UART.
 */
syscall kputc(uchar c)
{
    volatile struct pl011_uart_csreg *regptr;

    /* Pointer to the UART control and status registers.  */
    regptr = (struct pl011_uart_csreg *)0x3F201000;

    // TODO: Check UART flags register.
    //       Once the Transmitter FIFO is not full, send character c.
    //       Special handling -- if c is newline, transmit carriage return
    //       followed by newline.

	while (regptr -> fr & PL011_FR_TXFF)
	{}

	if (c == '\n')
	{
		regptr -> dr = '\r';
		while (regptr -> fr & PL011_FR_TXFF)
		{}
		regptr -> dr = '\n';
	}
	
	regptr -> dr = (int)c;
	return c;

	return SYSERR;
}

/**
 * kernel printf: formatted, synchronous output to SERIAL0.
 *
 * @param format
 *      The format string.  Not all standard format specifiers are supported by
 *      this implementation.  See _doprnt() for a description of supported
 *      conversion specifications.
 * @param ...
 *      Arguments matching those in the format string.
 *
 * @return
 *      The number of characters written.
 */
syscall kprintf(const char *format, ...)
{
    int retval;
    va_list ap;

    va_start(ap, format);
    retval = _doprnt(format, ap, (int (*)(int, int))kputc, 0);
    va_end(ap);
    return retval;
}