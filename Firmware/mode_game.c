#include "klotz.h"

u16 game_score;
u8 game_trig;
u8 game_mode;

void    init_game(u8 boot)
{
    if (boot)
        game_mode = GAME_10S;
    game_score = 0;
}

void    mode_page_game(void)
{
    clear_LCD_pg(MENU_BK_CLR);
    print_LCD_str((18 - ft_strlen(mode_game_str[0][lang_mode])) * X_STA / 2 + 2, Y_DATE, mode_game_str[0][lang_mode]);
    if (game_score < 10)
        print_LCD_nb_BIG(38 + X_BIG / 2, Y_TIME, 0, game_score, 0);
    else if (game_score < 100)
        print_LCD_nb_BIG(38 + X_BIG, Y_TIME, 0, game_score, 0);
    else
        print_LCD_nb_BIG(38 + 3 * X_BIG / 2, Y_TIME, 0, game_score, 0);
    if (!game_score)
        print_LCD_str((18 - ft_strlen(mode_game_str[1][lang_mode])) * X_STA / 2 + 2, Y_SEC, mode_game_str[1][lang_mode]);
}

void    mode_game(void)
{
    static u16 game_cnt = 0;
    static u8 len = 0;

    if (but == RIGHT_SHORT)
    {
        len = ft_strlen(mode_game_str[1][lang_mode]);
        game_cnt = 500 * (game_mode + 1);
        blank((18 - len) * X_STA / 2 + 2, Y_SEC, len, STA);
        blank(24, Y_TIME, 3, 1);
        print_LCD_nb_BIG(38 + X_BIG / 2, Y_TIME, 0, (game_score = 0), 0);
    }
    if (game_cnt)
    {
        if (but == LEFT_SHORT)
        {
            if (++game_score < 10)
                print_LCD_nb_BIG(38 + X_BIG / 2, Y_TIME, 0, game_score, 0);
            else if (game_score < 100)
                print_LCD_nb_BIG(38 + X_BIG, Y_TIME, 0, game_score, 0);
            else
                print_LCD_nb_BIG(38 + 3 * X_BIG / 2, Y_TIME, 0, game_score, 0);
        }
        if (game_trig)
        {
            game_trig = 0;
            if (but == RIGHT_LONG)
                game_cnt = 0;
            else if (!(--game_cnt) && (alarm_state = 1))
                print_LCD_str((18 - ft_strlen(mode_game_str[1][lang_mode])) * X_STA / 2 + 2, Y_SEC, mode_game_str[1][lang_mode]);
        }
    }
}