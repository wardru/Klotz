#include "klotz.h"

u8 lang_mode;

void    print_menu_lang(void)               //printing a sub-menu in the menu
{
    if (lang_mode != 0)
    {
        print_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(0), menu_bar_s);
        print_LCD_str((18 - ft_strlen(menu_lang_str[lang_mode - 1])) * X_STA / 2 + 1, MENU_BAR_Y(0) + 3, menu_lang_str[lang_mode - 1]);
    }
    else
        clear_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(0), menu_bar_s, MENU_BK_CLR);
    blank(ROW(4), MENU_BAR_Y(1) + 3, 10, STA);
    print_LCD_str((18 - ft_strlen(menu_lang_str[lang_mode])) * X_STA / 2 + 1, MENU_BAR_Y(1) + 3, menu_lang_str[lang_mode]);
    if (lang_mode != LANG_SIZE - 1)
    {
        print_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(2), menu_bar_s);
        print_LCD_str((18 - ft_strlen(menu_lang_str[lang_mode + 1])) * X_STA / 2 + 1, MENU_BAR_Y(2) + 3, menu_lang_str[lang_mode + 1]);
        if (lang_mode != LANG_SIZE - 2)
        {
            print_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(3) - 3, menu_bar_s);
            print_LCD_str((18 - ft_strlen(menu_lang_str[lang_mode + 2])) * X_STA / 2 + 1, MENU_BAR_Y(3), menu_lang_str[lang_mode + 2]);
        }
        else
            clear_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(3) - 3, menu_bar_s, MENU_BK_CLR);
    }
    else
        clear_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(2), menu_bar_s, MENU_BK_CLR);
}

void    menu_page_lang(void)
{
    clear_LCD_menu(MENU_BK_CLR);
    print_LCD_window(0, 15, 128, 2, 0xFFFF);
    print_LCD_img(MENU_BAR_B_X, MENU_BAR_Y(1), menu_bar_b);
    print_menu_lang();
}

void    menu_lang(void)
{
    if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
    else if (but == LEFT_SHORT)
    {
        if (++lang_mode == 3)
            lang_mode = 0;
        print_menu_lang();
    }
}