#include "klotz.h"

u8 stop_trig;

void    init_stop(void)
{
    stop.HR = 0;
    stop.MIN = 0;
    stop.SEC = 0;
    stop.run = 0;
    stop.sum = 0;
    stop.cnt = 0;
}

void    stop_print(void)
{
    if (!stop.HR)
    {
        if (stop.MIN < 10)
            print_LCD_char_BIG(0 * X_BIG + 1, Y_TIME, char_BIG_0);
        print_LCD_nb_BIG(1 * X_BIG + 1, Y_TIME, 0, stop.MIN, 0);
        if (stop.SEC < 10)
            print_LCD_char_BIG(2 * X_BIG + 19, Y_TIME, char_BIG_0);
        print_LCD_nb_BIG(3 * X_BIG + 19, Y_TIME, 0, stop.SEC, 0);
    }
    else
    {
        if (stop.HR < 10)
            print_LCD_char_BIG(0 * X_BIG + 1, Y_TIME, char_BIG_0);
        print_LCD_nb_BIG(1 * X_BIG + 1, Y_TIME, 0, stop.HR, 0);
        if (stop.MIN < 10)
            print_LCD_char_BIG(2 * X_BIG + 19, Y_TIME, char_BIG_0);
        print_LCD_nb_BIG(3 * X_BIG + 19, Y_TIME, 0, stop.MIN, 0);
        if (stop.SEC < 10)
            print_LCD_char(ROW(15), Y_SEC, char_0);
        print_LCD_nb(ROW(16), Y_SEC, 0, stop.SEC, 0);
    }
}

void    time_page_stop(void)
{
    clear_LCD_pg(BK_CLR);
    print_LCD_window(62, Y_TIME + 17, 4, 4, 0xFFFF);                 // Print double dot for count
    print_LCD_window(62, Y_TIME + 29, 4, 4, 0xFFFF);
    print_LCD_str(ROW(1), Y_SEC, time_mode_str[time_mode - 1][lang_mode]);
    stop_print();
}

void    time_stop(void)
{
    static u32 last = 0;
    
    if (but == RIGHT_SHORT )
    {
        if ((stop.run = !stop.run))
        {
            stop.sum = 0;
            stop.HR = 0;
            stop.MIN = 0;
            stop.SEC = 0;
            stop.cnt = 0;
        }
        if (!stop.sum)
            blank(ROW(15), Y_SEC, 2, 0);
    }
    else if (last != stop.sum)
    {
        last = stop.sum;
        stop.HR = stop.sum / 3600;
        stop.MIN = (stop.sum % 3600) / 60;
        stop.SEC = stop.sum % 60;
        stop_print();
    }
}

void    calc_stop(void)
{
    static u16 stop_cnt = 0;
    
    if (stop.run && !stop_cnt--)
    {
        stop_cnt = 999;
        stop.sum++;
    }
    else if (!stop.run)
        stop_cnt = 999;
}