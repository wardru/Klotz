#include "klotz.h"

u8 count_trig;

void    init_count(void)
{
    count.HR = 0;
    count.MIN = 0;
    count.SEC = 0;
    count.sum = 0;
}

void    count_print(u8 force)
{
    if (!count.HR)
    {
        if (count.sum == 3599)
            blank(ROW(15), Y_SEC, 2, 0);
        print_LCD_nb_BIG(3 * X_BIG + 19, Y_TIME, 0, count.SEC, 0);
        if (count.SEC == 59 || force)
        {
            print_LCD_nb_BIG(1 * X_BIG + 1, Y_TIME, 0, count.MIN, 0);
            if (count.MIN < 10)
                print_LCD_char_BIG(0 * X_BIG + 1, Y_TIME, char_BIG_0);
        }
        if (count.SEC < 10)
            print_LCD_char_BIG(2 * X_BIG + 19, Y_TIME, char_BIG_0);
    }
    else
    {
        print_LCD_nb(ROW(16), Y_SEC, 0, count.SEC, 0);
        if (count.SEC == 59 || force)
        {
            print_LCD_nb_BIG(3 * X_BIG + 19, Y_TIME, 0, count.MIN, 0);
            if (count.MIN == 59 || force)
            {
                print_LCD_nb_BIG(1 * X_BIG + 1, Y_TIME, 0, count.HR, 0);
                if (count.HR < 10)
                    print_LCD_char_BIG(0 * X_BIG + 1, Y_TIME, char_BIG_0);
            }
            if (count.MIN < 10)
                print_LCD_char_BIG(2 * X_BIG + 19, Y_TIME, char_BIG_0);
        }
        if (count.SEC < 10)
            print_LCD_char(ROW(15), Y_SEC, char_0);
    }
}

void    count_set_SEC(void)
{
    if (but == LEFT_SHORT)
    {
        if (count.SEC == 59)
            count.SEC = 0;
        else
            count.SEC++;
        print_LCD_char(ROW(15), Y_SEC, alpha_n[count.SEC / 10]);
        print_LCD_char(ROW(16), Y_SEC, alpha_n[count.SEC % 10]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(ROW(15), Y_SEC, 2, 0);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char(ROW(15), Y_SEC, alpha_n[count.SEC / 10]);
        print_LCD_char(ROW(16), Y_SEC, alpha_n[count.SEC % 10]);
    }
}

void    count_set_MIN(void)
{
    if (but == RIGHT_SHORT)
    {
        print_LCD_char(ROW(15), Y_SEC, alpha_n[count.SEC / 10]);
        print_LCD_char(ROW(16), Y_SEC, alpha_n[count.SEC % 10]);
    }
    else if (but == LEFT_SHORT)
    {
        if (count.MIN == 59)
            count.MIN = 0;
        else
            count.MIN++;
        print_LCD_char_BIG(CX(3, X_BIG) - 9, Y_TIME, alpha_N[count.MIN / 10]);
        print_LCD_char_BIG(CX(4, X_BIG) - 9, Y_TIME, alpha_N[count.MIN % 10]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(CX(3, X_BIG) - 9, Y_TIME, 2, 1);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char_BIG(CX(3, X_BIG) - 9, Y_TIME, alpha_N[count.MIN / 10]);
        print_LCD_char_BIG(CX(4, X_BIG) - 9, Y_TIME, alpha_N[count.MIN % 10]);
    }
}

void    count_set_HR(void)
{
    if (but == RIGHT_SHORT)
    {
        print_LCD_char_BIG(CX(3, X_BIG) - 9, Y_TIME, alpha_N[count.MIN / 10]);
        print_LCD_char_BIG(CX(4, X_BIG) - 9, Y_TIME, alpha_N[count.MIN % 10]);
    }
    else if (but == LEFT_SHORT)
    {
        if (count.HR == 99)
            count.HR = 0;
        else
            count.HR++;
        print_LCD_char_BIG(CX(0, X_BIG), Y_TIME, alpha_N[count.HR / 10]);
        print_LCD_char_BIG(CX(1, X_BIG), Y_TIME, alpha_N[count.HR % 10]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(CX(0, X_BIG), Y_TIME, 2, BIG);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char_BIG(CX(0, X_BIG), Y_TIME, alpha_N[count.HR / 10]);
        print_LCD_char_BIG(CX(1, X_BIG), Y_TIME, alpha_N[count.HR % 10]);
    }
}

void    write_count(void)
{
    u32 tmp = count.HR * 3600 + count.MIN * 60 + count.SEC;

    if (tmp)
        count.sum = tmp + 1;
    if (count.sum < 3600)
        blank(ROW(15), Y_SEC, 2, 0);
    count_print(1);
}

void    time_page_count(void)
{
    clear_LCD_pg(BK_CLR);
    print_LCD_window(62, Y_TIME + 17, 4, 4, 0xFFFF);                 // Print double dot for count
    print_LCD_window(62, Y_TIME + 29, 4, 4, 0xFFFF);
    print_LCD_str(ROW(1), Y_SEC, time_mode_str[time_mode - 1][lang_mode]);
    count_print(1);
}

void    time_count(void)
{
    static u32 last = 0;
    
    if (but == RIGHT_SHORT )
    {
        if (!time_set++)
        {
            init_count();
            count_print(1);
            print_LCD_str(ROW(15), Y_SEC, "00");
        }
        else if (time_set == 4 && !(time_set = 0))
            write_count();
    }
    if (time_set)
        set_time();
    else if (last != count.sum)
    {
        last = count.sum;
        count.HR = count.sum / 3600;
        count.MIN = (count.sum % 3600) / 60;
        count.SEC = count.sum % 60;
        count_print(0);
    }
}

void    calc_count(void)
{
    static count_cnt = 0;
    
    if (count.sum && !count_cnt--)
    {
        count_cnt = 999;
        if (!--count.sum && alarm_mode)
            alarm_state = 1;
    }
    else if (!count.sum && count_cnt)
        count_cnt = 0;
}