#include "klotz.h"

u8 lum_lvl;

void    init_PWM(void)                                                  // Pulse Width Modulation for "MENU_LUM" application
{
    RPA1R = 0b0101; // Setting BK pin as Output Compare
    OC2CONbits.OCTSEL = 0; // Selecting Timer2
    OC2CONbits.OCM = 0b110; // Setting OC to PWM mode, fault pin disabled
    OC2RS = 0; // Duty cycle: This screen has NO luminosity after init
    OC2R = 0; // Initializing duty cycle
    OC2CONbits.ON = 1; // Starting PWM
}

void    set_LUM(const u8 lvl)
{
    OC2RS = (7 - lvl) * 90;
}

void    menu_page_lum(void)
{
    clear_LCD_pg(BK_CLR);
    print_LCD_window((lum_lvl - 1) * 15 + 19, 60, 90 - (lum_lvl - 1) * 15, 7, 0x4A69);  // grey bar                  // grey bar
    print_LCD_window(19, 60, (lum_lvl - 1) * 15, 7, 0xFF00 + lum_lvl);       // white bar
    print_LCD_window(8, 63, 5, 1, 0xFFFF);                              // minus sign
    print_LCD_window(115, 63, 5, 1, 0xFFFF);                            // plus sign 1
    print_LCD_window(117, 61, 1, 5, 0xFFFF);                            // plus sign 2
}

void    menu_lum(void)
{
    if (but == LEFT_SHORT)
    {
        if (lum_lvl < 7)
        {
            print_LCD_window((lum_lvl - 1) * 15 + 19, 60, 15, 7, 0xFF00 + lum_lvl);       // white bar
            set_LUM(++lum_lvl);
        }
        else
        {
            set_LUM((lum_lvl = 1));
            print_LCD_window(19, 60, 90, 7, 0x4A69);                    // grey bar
        }
    }
    else if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
}