#include<msp430.h>
void main()
{
 	WDTCTL = WDTPW + WDTHOLD;
	P1DIR = BIT6;
	P1OUT = BIT6;
	for(;;);
}

