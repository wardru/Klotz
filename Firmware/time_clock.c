#include "klotz.h"

void    print_WDAY(const u8 x, const u8 y)
{
    u8 wday;

    wday = (time_set) ? clock.WDAY01 : RDb.WDAY01;
    print_LCD_str(x, y, time_wday_str[wday][lang_mode]);
}

void    print_clock(const s8 force)
{
    static unsigned char blink = 0;
    
    if (!time_set || force)
    {
        if (mode == MODE_TIME && time_mode == TIME_CLOCK)
        {
            if (force || (!RTb.SEC01 && !RTb.SEC10))
            {
                print_LCD_char_BIG(4 * X_BIG + 1 - 9, Y_TIME, alpha_N[RTb.MIN01]);
                print_LCD_char_BIG(3 * X_BIG + 1 - 9, Y_TIME, alpha_N[RTb.MIN10]);
            }
            if (force || (!RTb.MIN01 && !RTb.MIN10))
            {
                print_LCD_char_BIG(1 * X_BIG + 1, Y_TIME, alpha_N[RTb.HR01]);
                print_LCD_char_BIG(0 * X_BIG + 1, Y_TIME, alpha_N[RTb.HR10]);
            }
            if (date_print)
            {
                print_LCD_char(ROW(16), Y_SEC, alpha_n[RTb.SEC01]);
                print_LCD_char(ROW(15), Y_SEC, alpha_n[RTb.SEC10]);
                if (force || (!RTb.HR01 && !RTb.HR10))
                {
                    print_LCD_char(ROW(9), Y_DATE, alpha_n[RDb.DAY10]);
                    print_LCD_char(ROW(10), Y_DATE, alpha_n[RDb.DAY01]);
                    print_WDAY(ROW(1), Y_DATE);
                }
                if (force || (RDb.DAY01 == 1 && !RDb.DAY10))
                {
                    print_LCD_char(ROW(12), Y_DATE, alpha_n[RDb.MONTH10]);
                    print_LCD_char(ROW(13), Y_DATE, alpha_n[RDb.MONTH01]);
                }
                if (force || (RDb.MONTH01 == 1 && !RDb.MONTH10))
                {
                    print_LCD_char(ROW(15), Y_DATE, alpha_n[RDb.YEAR10]);
                    print_LCD_char(ROW(16), Y_DATE, alpha_n[RDb.YEAR01]);
                }
            }
            else if ((blink = !blink))
                print_LCD_window(62, Y_TIME + 17, 4, 16, BK_CLR);
            else
            {
                print_LCD_window(62, Y_TIME + 17, 4, 4, 0xFFFF);                 // Print blinking double dot for hour
                print_LCD_window(62, Y_TIME + 29, 4, 4, 0xFFFF);
                
            }
        }
        else if ((!RTb.SEC10 && !RTb.SEC01) || force)
        {
            print_LCD_char(ROW(0), LINE(0), alpha_n[RTb.HR10]);
            print_LCD_char(ROW(1), LINE(0), alpha_n[RTb.HR01]);

            print_LCD_char(ROW(3), LINE(0), alpha_n[RTb.MIN10]);
            print_LCD_char(ROW(4), LINE(0), alpha_n[RTb.MIN01]);
        }
    }
}

void    init_clock(void)
{
    clock.YEAR10 = RDb.YEAR10;
    clock.YEAR01 = RDb.YEAR01;
    clock.MONTH10 = RDb.MONTH10;
    clock.MONTH01 = RDb.MONTH01;
    clock.DAY10 = RDb.DAY10;
    clock.DAY01 = RDb.DAY01;
    clock.WDAY01 = RDb.WDAY01;

    clock.HR10 = RTb.HR10;
    clock.HR01 = RTb.HR01;
    clock.MIN10 = RTb.MIN10;
    clock.MIN01 = RTb.MIN01;
    clock.SEC10 = RTb.SEC10;
    clock.SEC01 = RTb.SEC01;
}

void    clock_set_YEAR(void)
{
    if (but == LEFT_SHORT)
    {
        if (clock.YEAR10 == 9 && clock.YEAR01 == 9)
        {
            clock.YEAR10 = 0;
            clock.YEAR01 = 0;
        }
        else if (clock.YEAR01 == 9 && !(clock.YEAR01 = 0))
            clock.YEAR10++;
        else
            clock.YEAR01++;
        print_LCD_char(ROW(15), Y_DATE, alpha_n[clock.YEAR10]);
        print_LCD_char(ROW(16), Y_DATE, alpha_n[clock.YEAR01]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(ROW(15), Y_DATE, 2, 0);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char(ROW(15), Y_DATE, alpha_n[clock.YEAR10]);
        print_LCD_char(ROW(16), Y_DATE, alpha_n[clock.YEAR01]);
    }
}

void    clock_set_MONTH(void)
{
    if (but == RIGHT_SHORT)
    {
        print_LCD_char(ROW(15), Y_DATE, alpha_n[clock.YEAR10]);
        print_LCD_char(ROW(16), Y_DATE, alpha_n[clock.YEAR01]);
    }
    else if (but == LEFT_SHORT)
    {
        if (clock.MONTH10 == 1 && clock.MONTH01 == 2)
        {
            clock.MONTH10 = 0;
            clock.MONTH01 = 1;
        }
        else if (clock.MONTH01 == 9 && !(clock.MONTH01 = 0))
            clock.MONTH10++;
        else
            clock.MONTH01++;
        print_LCD_char(ROW(12), Y_DATE, alpha_n[clock.MONTH10]);
        print_LCD_char(ROW(13), Y_DATE, alpha_n[clock.MONTH01]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(ROW(12), Y_DATE, 2, 0);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char(ROW(12), Y_DATE, alpha_n[clock.MONTH10]);
        print_LCD_char(ROW(13), Y_DATE, alpha_n[clock.MONTH01]);
    }
}

void    clock_set_DAY(void)
{
    u8 day = clock.DAY10 * 10 + clock.DAY01;
    u8 month = clock.MONTH10 * 10 + clock.MONTH01;
    u8 year = clock.YEAR10 * 10 + clock.YEAR01;
    u8 limit10 = 3;
    u8 limit01 = 1;
    if (but == RIGHT_SHORT)
    {
        print_LCD_char(ROW(12), Y_DATE, alpha_n[clock.MONTH10]);
        print_LCD_char(ROW(13), Y_DATE, alpha_n[clock.MONTH01]);
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day == 31)
            {
                print_LCD_char(ROW(9), Y_DATE, alpha_n[(clock.DAY10 = 0)]);
                print_LCD_char(ROW(10), Y_DATE, alpha_n[(clock.DAY01 = 1)]);
            }
            limit01 = 0;
        }
        else if (month == 2)                                                //leap year calculation
        {
            if (day >= 30)
            {
                print_LCD_char(ROW(9), Y_DATE, alpha_n[(clock.DAY10 = 0)]);
                print_LCD_char(ROW(10), Y_DATE, alpha_n[(clock.DAY01 = 1)]);
            }
            limit10 = 2;
            limit01 = !(year % 4) ? (!(year & 100) ? (!(year % 400) ? 9 : 8) : 9) : 8;
        }
    }
    else if (but == LEFT_SHORT)
    {
        if (clock.DAY10 >= limit10 && clock.DAY01 >= limit01)
        {
            clock.DAY10 = 0;
            clock.DAY01 = 1;
        }
        else if (clock.DAY01 == 9 && !(clock.DAY01 = 0))
            clock.DAY10++;
        else
            clock.DAY01++;
        print_LCD_char(ROW(9), Y_DATE, alpha_n[clock.DAY10]);
        print_LCD_char(ROW(10), Y_DATE, alpha_n[clock.DAY01]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(ROW(9), Y_DATE, 2, 0);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char(ROW(9), Y_DATE, alpha_n[clock.DAY10]);
        print_LCD_char(ROW(10), Y_DATE, alpha_n[clock.DAY01]);
    }
}

void    clock_set_WDAY(void)
{
    if (but == RIGHT_SHORT)
    {
        print_LCD_char(ROW(9), Y_DATE, alpha_n[clock.DAY10]);
        print_LCD_char(ROW(10), Y_DATE, alpha_n[clock.DAY01]);
    }
    else if (but == LEFT_SHORT)
    {
        if (clock.WDAY01 == 6)
            clock.WDAY01 = 0;
        else
            clock.WDAY01++;
        print_WDAY(ROW(1), Y_DATE);
    }
    else if (blink_time == BLINK_FREQ)
        blank(ROW(1), Y_DATE, 3, 0);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
        print_WDAY(ROW(1), Y_DATE);
}

void    clock_set_HR(void)
{
    if (but == RIGHT_SHORT)
    {
        print_LCD_window(62, Y_TIME + 17, 4, 4, 0xFFFF);                 // Print double dot for hour
        print_LCD_window(62, Y_TIME + 29, 4, 4, 0xFFFF);
        if (date_print)
            print_WDAY(ROW(1), Y_DATE);
    }
    else if (but == LEFT_SHORT)
    {
        if (clock.HR10 == 2 && clock.HR01 == 3)
        {
            clock.HR10 = 0;
            clock.HR01 = 0;
        }
        else if (clock.HR01 == 9 && !(clock.HR01 = 0))
            clock.HR10++;
        else
            clock.HR01++;
        print_LCD_char_BIG(CX(0, X_BIG), Y_TIME, alpha_N[clock.HR10]);
        print_LCD_char_BIG(CX(1, X_BIG), Y_TIME, alpha_N[clock.HR01]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(CX(0, X_BIG), Y_TIME, 2, 1);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char_BIG(CX(0, X_BIG), Y_TIME, alpha_N[clock.HR10]);
        print_LCD_char_BIG(CX(1, X_BIG), Y_TIME, alpha_N[clock.HR01]);
    }
}

void    clock_set_MIN(void)
{
    if (but == RIGHT_SHORT)
    {
        print_LCD_char_BIG(CX(0, X_BIG), Y_TIME, alpha_N[clock.HR10]);
        print_LCD_char_BIG(CX(1, X_BIG), Y_TIME, alpha_N[clock.HR01]);
    }
    else if (but == LEFT_SHORT)
    {
        if (clock.MIN10 == 5 && clock.MIN01 == 9)
        {
            clock.MIN10 = 0;
            clock.MIN01 = 0;
        }
        else if (clock.MIN01 == 9 && !(clock.MIN01 = 0))
            clock.MIN10++;
        else
            clock.MIN01++;
        print_LCD_char_BIG(CX(3, X_BIG) - 9, Y_TIME, alpha_N[clock.MIN10]);
        print_LCD_char_BIG(CX(4, X_BIG) - 9, Y_TIME, alpha_N[clock.MIN01]);
    }
    else if (blink_time == BLINK_FREQ)
        blank(CX(3, X_BIG) - 9, Y_TIME, 2, 1);
    else if (blink_time == BLINK_FREQ * 2 && !(blink_time = 0))
    {
        print_LCD_char_BIG(CX(3, X_BIG) - 9, Y_TIME, alpha_N[clock.MIN10]);
        print_LCD_char_BIG(CX(4, X_BIG) - 9, Y_TIME, alpha_N[clock.MIN01]);
    }
}

void    time_page_clock(void)
{
    blank(ROW(0), LINE(0), 5, STA);
    clear_LCD_pg(BK_CLR);
    print_clock(1);
    if (date_print)
    {
        print_LCD_window(ROW(11) + 3, Y_DATE + 9, 1, 2, 0xFFFF);                 // Print 1. dot date
        print_LCD_window(ROW(14) + 3, Y_DATE + 9, 1, 2, 0xFFFF);                 // Print 2. dot date
    }
    print_LCD_window(62, Y_TIME + 17, 4, 4, 0xFFFF);                 // Print double dot for hour
    print_LCD_window(62, Y_TIME + 29, 4, 4, 0xFFFF);
}

void    time_clock(void)
{
    if (but == RIGHT_SHORT)
    {
        if (!time_set)
        {
            init_clock();
            time_set++;
            if (date_print)
                print_LCD_str(ROW(15), Y_SEC, "00");
            else
                time_set = 5;
        }
        else if (++time_set == 7)
        {
            time_set = 0;
            write_time_and_date();
        }
    }
    if (time_set)
        set_time();
}