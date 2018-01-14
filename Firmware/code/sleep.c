#include "klotz.h"

void    sleep_but(u8 i)
{
    CNCONBbits.ON = i;
    IEC1bits.CNBIE = i;
}

void    sleep_cmp(u8 i)
{
    IEC1bits.CMP3IE = i;
    CM3CONbits.ON = i;
    CVRCONbits.ON = i;
}

void    sleep(void)
{   
    (but) ? sleep_cmp(0) : sleep_but(0);
    set_LUM(0);
    clear_LCD(BK_CLR);
//    delay_ms(500);                                  // wait for user to release button
    
    T_RS = 0;
    T_SCL = 0;
    T_SDA = 0;
    T_RESET = 0;
    T_CS = 0;
    T_TEMP = 0;
    T_SPI = 0;
    T_SCLK = 0;
    L_RS = 0;
    L_SCL = 0;
    L_SDA = 0;
    L_RESET = 0;
    L_CS = 0;
    L_SPI = 0;
    L_SCLK = 0;
    
    L_LS0 = 1;
    PMD1bits.AD1MD = 1;
    SYSKEY = 0x0;  // write invalid key to force lock
    SYSKEY = 0xAA996655;  // Write Key1 to SYSKEY
    SYSKEY = 0x556699AA;  // Write Key2 to SYSKEY
    OSCCONSET = 0x10; // set Power-Saving mode to Sleep
    SYSKEY = 0x0;  // write invalid key to force lock    
    asm volatile ("wait");
    sleep_cmp(1);
//    if (!CM3CONbits.COUT)
//    {
//        sleep_but(0);
//        SYSKEY = 0x0;  // write invalid key to force lock
//        SYSKEY = 0xAA996655;  // Write Key1 to SYSKEY
//        SYSKEY = 0x556699AA;  // Write Key2 to SYSKEY
//        OSCCONSET = 0x10; // set Power-Saving mode to Sleep
//        SYSKEY = 0x0;  // write invalid key to force lock
//        asm volatile ("wait");
//    }
    SYSKEY = 0xAA996655;  // Write Key1 to SYSKEY
    SYSKEY = 0x556699AA;  // Write Key2 to SYSKEY
    sleep_but(1);
    PMD1bits.AD1MD = 0;
    L_LS0 = 0;
    init_LCD();
//    init_ADC();
    init_GYRO();
    init_variables(FALSE);
//    if (read_IND() > 2150)
    print_logo_mode();
}