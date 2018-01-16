#include "klotz.h"

void    menu_page_alarm(void)
{
    clear_LCD_menu(MENU_BK_CLR);
    print_LCD_window(0, 15, 128, 2, 0xFFFF);
    print_LCD_img(MENU_BAR_B_X, MENU_BAR_Y(1), menu_bar_b);
    print_menu(alarm_mode, ALARM_SIZE, alarm_str);
}

void    menu_alarm(void)
{
    if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
    else if (but == LEFT_SHORT)
    {
        if (++alarm_mode == ALARM_SIZE)
            alarm_mode = 0;
        print_menu(alarm_mode, ALARM_SIZE, alarm_str);
    }
}