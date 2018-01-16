#include "klotz.h"

void    menu_page_game(void)
{
    clear_LCD_menu(MENU_BK_CLR);
    print_LCD_window(0, 15, 128, 2, 0xFFFF);
    print_LCD_img(MENU_BAR_B_X, MENU_BAR_Y(1), menu_bar_b);
    print_menu(game_mode, GAME_SIZE, menu_game_str);
}

void    menu_game(void)
{
    if (but == RIGHT_SHORT)
        mode_page[(mode = MODE_MENU)]();
    else if (but == LEFT_SHORT)
    {
        if (++game_mode == GAME_SIZE)
            game_mode = 0;
        print_menu(game_mode, GAME_SIZE, menu_game_str);
    }
}