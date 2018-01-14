#include "klotz.h"

void    menu_page_about(void)
{
    clear_LCD_menu(MENU_BK_CLR);
    print_LCD_window(0, 15, 128, 2, 0xFFFF);
    print_LCD_str(ROW(1), LINE(2), "For more informations please visit:");
    print_LCD_str(ROW(3), LINE(4), "www.klotz.ch");
    print_LCD_str(ROW(0), LINE(6), "designed, build and coded by:");
    print_LCD_str(ROW(0), LINE(8), "agouby et mheutsch");
    print_LCD_window(ROW(8) + 3, LINE(6) + 10, 1, 3, 0xFFFF);
}

void    menu_about(void)
{
    if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
    else if (but == LEFT_SHORT)
    {
        set_LUM(0);
        print_128(logo);
        set_LUM(lum_lvl);
        delay_ms(1300);
        set_LUM(0);
        clear_LCD_tk(BK_CLR);
        print_LCD_tk(1);
        menu_page_about();
        set_LUM(lum_lvl);
    }
}