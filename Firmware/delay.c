#include "klotz.h"

void    delay_ms(u32 ms)
{
    while (ms--)
    {
        PR1 = 625;                      //SYSCLK / 64
        I0b.T1IF = 0;
        while (!I0b.T1IF)
            ;
    }
}