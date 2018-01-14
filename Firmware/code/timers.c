#include "klotz.h"

void    init_timer1(void)
{
    T1CONbits.ON = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 2;                    //Prescale de 64
    TMR1 = 0;
    T1CONbits.ON = 1;
    IFS0bits.T1IF = 1;
}

void    init_timer2(void)
{
    T2CONbits.ON = 0;
    T2CONbits.TCS = 0;
    T2CONbits.TCKPS = 6;                    // Setting prescale to 64
    PR2 = 624;
    TMR2 = 0;                               // Init Timer2
    T2CONbits.ON = 1;
    IFS0bits.T2IF = 1;
}

void    init_timer3(void)
{
    T3CONbits.ON = 0;
    T3CONbits.TCS = 0;
    T3CONbits.TCKPS = 6;                   //Prescale de 64
    TMR3 = 0;
    T3CONbits.ON = 1;
    IFS0bits.T3IF = 1;
}

void    init_timer4(void)
{
    T4CONbits.ON = 0;
    T4CONbits.TCS = 0;
    T4CONbits.TCKPS = 7;                   //Prescale de 256
    TMR4 = 0;
    T4CONbits.ON = 1;
    IFS0bits.T4IF = 1;
}

void    init_timer5(void)
{
    T5CONbits.ON = 0;
    T5CONbits.TCS = 0;
    T5CONbits.TCKPS = 6;                    //Prescale de 64
    TMR5 = 0;
    T5CONbits.ON = 1;
    IFS0bits.T5IF = 1;
}

void    init_timers(void)
{
    init_timer1();
    init_timer2();
    init_timer3();
    init_timer4();
    init_timer5();
}
