#include "klotz.h"

u8 rot_state;

void    menu_page_rot(void)
{
    clear_LCD_pg(BK_CLR);
    print_LCD_img(ROT_CIRCLE_X, ROT_CIRCLE_Y, rot_circle);
    if (rot_state)
        print_LCD_img(ROT_HOOK_X, ROT_HOOK_Y, check_G);
    else
        print_LCD_img(ROT_CROSS_X, ROT_CROSS_Y, cross_R);
}

void    menu_rot(void)
{
    if (but == LEFT_SHORT)                                       // short LEFT click
    {
        if ((rot_state = !rot_state))
            print_LCD_img(ROT_HOOK_X, ROT_HOOK_Y, check_G);
        else
        {
            clear_LCD_img(ROT_HOOK_X, ROT_HOOK_Y, check_G, BK_CLR);
            print_LCD_img(ROT_CROSS_X, ROT_CROSS_Y, cross_R);
        }
    }
    else if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
}