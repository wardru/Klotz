#include "klotz.h"

u8 buz_state;

void    init_BUZ(void)
{
    T_BUZ = 0;
    L_BUZ = 0;
}

void    set_BUZ(u8 i)
{
    L_BUZ = i;
}

void    menu_page_buz(void)
{
    clear_LCD_pg(BK_CLR);
    print_LCD_img(BUZ_SPEAKER_X, BUZ_SPEAKER_Y, speaker);
    if (buz_state)
        print_LCD_img(BUZ_WAVES_X, BUZ_WAVES_Y, waves_G);
    else
        print_LCD_img(BUZ_CROSS_X, BUZ_CROSS_Y, cross_R);
}

void    menu_buz(void)
{
    if (but == LEFT_SHORT)                                       // short LEFT click
    {
        if ((buz_state = !buz_state))
            print_LCD_img(BUZ_WAVES_X, BUZ_WAVES_Y, waves_G);
        else
        {
            clear_LCD_img(BUZ_WAVES_X, BUZ_WAVES_Y, waves_G, BK_CLR);
            print_LCD_img(BUZ_CROSS_X, BUZ_CROSS_Y, cross_R);
        }
    }
    else if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
}


