/*
 * File:   isr.c
 * Author: dell
 *
 * Created on 24 June, 2025, 5:16 PM
 */


#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
	static unsigned short count;
   
    
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
			count = 0;
		}
		TMR0IF = 0;
	}
    
}
