#include "klotz.h"

u8 bat_state;

void    init_IND(void)
{
    T_CMP = 1;
    CVRCONbits.ON = 0;
    CVRCONbits.CVROE = 0;
    CVRCONbits.CVRR = 1;
    CVRCONbits.CVRSS = 0;
    CVRCONbits.CVR = 0x0F;                              // VDD / 24steps * CVR = INDinMIN
    CVRCONbits.ON = 1;

    CM3CONbits.ON = 0;
    CM3CONbits.COE = 0;
    CM3CONbits.CPOL = 1;
    CM3CONbits.COUT = 1;
    CM3CONbits.CREF = 1;
    CM3CONbits.CCH = 1;
    CM3CONbits.ON = 1;

    IPC7bits.CMP3IP = 1;
    IPC7bits.CMP3IS = 1;
    IFS1bits.CMP3IF = 0;
    IEC1bits.CMP3IE = 1;
}

unsigned short  read_IND(void)
{
    return (read_analog(9) * (PWR_VOL / 1023.0));
}

char    get_BAT(void)
{
    u16    ind; 

    ind = read_IND();
    if (ind > 2500 && bat_state >= 4)                               // green (three)
        return (4);
    else if (ind > 2300 && bat_state >= 3)                          // green (two)
        return (3);
    else if (ind > 2250 && bat_state >= 2)                          // orange
        return (2);
    else if (ind > 2160 && bat_state >= 1)                          // red
        return (1);
    return (0);
}

void    print_BAT(const u8 print)
{
    static s8 last = -1;

    bat_state = get_BAT();
    if ((last != bat_state) || print)
    {
        last = bat_state;
        print_LCD_img(BAT_X, BAT_Y, battery);
        if (bat_state == 4)
        {
            print_LCD_img(BAT_X + 3, BAT_Y + 2, battery_G);
            print_LCD_img(BAT_X + 7, BAT_Y + 2, battery_G);
            print_LCD_img(BAT_X + 11, BAT_Y + 2, battery_G);
        }
        else if (bat_state == 3)
        {
            print_LCD_img(BAT_X + 7, BAT_Y + 2, battery_G);
            print_LCD_img(BAT_X + 11, BAT_Y + 2, battery_G);
        }
        else if (bat_state == 2)
            print_LCD_img(BAT_X + 11, BAT_Y + 2, battery_O);
        else if (bat_state == 1)
        {
            print_LCD_img(BAT_X + 11, BAT_Y + 2, battery_R);
        }
//        else if (!print)
//            set_LUM((lum_lvl = 1));
    }
}