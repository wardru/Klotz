#include "klotz.h"

u8 menu_mode;

void    print_menu(const u8 mode, const u8 size, const u8 *(*str)[LANG_SIZE])                    //printing the menu
{
    if (mode != 0)
    {
        print_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(0), menu_bar_s);
        print_LCD_str((18 - ft_strlen(str[mode - 1][lang_mode])) * X_STA / 2 + 1, MENU_BAR_Y(0) + 3, str[mode - 1][lang_mode]);
    }
    else
        clear_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(0), menu_bar_s, MENU_BK_CLR);
    blank(ROW(4), MENU_BAR_Y(1) + 3, 10, STA);
    print_LCD_str((18 - ft_strlen(str[mode][lang_mode])) * X_STA / 2 + 1, MENU_BAR_Y(1) + 3, str[mode][lang_mode]);
    if (mode != size - 1)
    {
        print_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(2), menu_bar_s);
        print_LCD_str((18 - ft_strlen(str[mode + 1][lang_mode])) * X_STA / 2 + 1, MENU_BAR_Y(2) + 3, str[mode + 1][lang_mode]);
        if (mode != size - 2)
        {
            print_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(3) - 3, menu_bar_s);
            print_LCD_str((18 - ft_strlen(str[mode + 2][lang_mode])) * X_STA / 2 + 1, MENU_BAR_Y(3), str[mode + 2][lang_mode]);
        }
        else
            clear_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(3) - 3, menu_bar_s, MENU_BK_CLR);
    }
    else
        clear_LCD_img(MENU_BAR_S_X, MENU_BAR_Y(2), menu_bar_s, MENU_BK_CLR);
}

void    mode_page_menu(void)
{
    clear_LCD_menu(MENU_BK_CLR);
    print_LCD_window(0, 15, 128, 2, 0xFFFF);
    print_LCD_img(MENU_BAR_B_X, MENU_BAR_Y(1), menu_bar_b);
    print_menu(menu_mode, MENU_SIZE, mode_menu_str);
}

void    mode_menu(void)
{
    if (but == RIGHT_SHORT && (mode = MENU_SET))
        menu_page[menu_mode]();
    else if (but == LEFT_SHORT)
    {
        if (++menu_mode == MENU_SIZE)
            menu_mode = 0;
        print_menu(menu_mode, MENU_SIZE, mode_menu_str);
    }
}