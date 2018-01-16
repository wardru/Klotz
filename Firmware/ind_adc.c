#include "klotz.h"

void    init_ADC(void)
{
    AD1CON1CLR = 0x8000;
    AD1CON1 = 0x00E0;
    AD1CON2 = 0;
    AD1CON3 = 0x0f01;
    AD1CON1SET = 0x8000;
    T_IND = 1;
//    T_TEMP = 1;                                                         // temp sensor temp
}

u32     read_analog(const u8 pin)
{
    AD1CHS = pin << 16;         // AD1CHS<16:19> controls which analog pin goes to the ADC

    AD1CON1bits.SAMP = 1;       // Begin sampling
    while(AD1CON1bits.SAMP)     // wait until acquisition is done
        ;
    while(!AD1CON1bits.DONE)    // wait until conversion done
        ;
    return (ADC1BUF0);          // result stored in ADC1BUF0
}