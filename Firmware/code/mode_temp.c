#include "klotz.h"

// For reading temp sensor, calc_GYRO_TEMP();
u8 temp_mode;
u8 temp_trig;

void    temp_avg(void)
{
    
}

void    mode_page_temp(void)
{
    clear_LCD_pg(BK_CLR);
    print_LCD_char(114, Y_TIME - 2, (gyr.df) ? char_F : char_C);
    print_LCD_img(109, Y_TIME, char_deg);
    print_LCD_nb_BIG(3 * X_BIG + 10, Y_TIME, NEG(gyr.temp[temp_mode]), ABS(gyr.temp[temp_mode]), 1);
    if (temp_mode == TEMP_AVG)
        print_LCD_str(ROW(0), Y_SEC, mode_temp_str[lang_mode]);
}

void    mode_temp(void)                                                      // mode_gyro mode_temp
{
    static s32 temp = 0;
    static s32 last = 0;
    static u16 temp_cnt = 0;
    static u8 i = 0;

    if (but == LEFT_SHORT)
    {
        if (++temp_mode == TEMP_SIZE)
        {
            temp_mode = 0;
            blank(ROW(0), Y_SEC, ft_strlen(mode_temp_str[lang_mode]), STA);
        }
        else
            print_LCD_str(ROW(0), Y_SEC, mode_temp_str[lang_mode]);
        temp_trig = 1;
        temp_cnt = 0;
        temp = gyr.temp[temp_mode] * 20;
    }
    else if (but == RIGHT_SHORT)                                  // switch degrees to fahrenheit
    {
        i = 0;
        if ((gyr.df = !gyr.df))
        {
            print_LCD_char(114, Y_TIME - 2, char_F);
            while (i < TEMP_SIZE)
                gyr.temp[i] = gyr.temp[i++] * 1.8 + 320;
            gyr.sum = gyr.sum * 1.8 + 320;
        }
        else
        {
            while (i < TEMP_SIZE)
                gyr.temp[i] = (gyr.temp[i++] - 320) / 1.8;
            gyr.sum = (gyr.sum - 320) / 1.8;
            print_LCD_char(114, Y_TIME - 2, char_C);
        }
        temp_trig = 1;
        temp_cnt = 0;
        temp = gyr.temp[temp_mode] * 20;
    }
    if (temp_trig)
    {
        temp_trig = 0;
        if (!temp_cnt--)
        {
            print_LCD_nb(ROW(17), LINE(8), NEG(i), ABS(i), 0);
            i++;
            temp_cnt = 19;
            temp /= temp_cnt + 1;
            if (last != temp)
            {
                i = 0;
                if (temp == 99)
                    blank(10, Y_TIME, 1, BIG);
                else if ((ABS(temp)) == 9 || !temp)
                    blank(10, Y_TIME, 2, BIG);
                print_LCD_nb_BIG(3 * X_BIG + 10, Y_TIME, NEG(temp), ABS(temp), 1);
            }
            last = temp;
            temp = 0;
        }
        temp += gyr.temp[temp_mode];
    }
}