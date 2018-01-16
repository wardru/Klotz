#include "klotz.h"

void    mode_page_test(void)
{
    clear_LCD(BK_CLR);
    print_LCD_str(ROW(0), LINE(0), "012345678901234567");
    print_LCD_char(ROW(0), LINE(1), char_1);
    print_LCD_char(ROW(0), LINE(2), char_2);
    print_LCD_char(ROW(0), LINE(3), char_3);
    print_LCD_char(ROW(0), LINE(4), char_4);
    print_LCD_char(ROW(0), LINE(5), char_5);
    print_LCD_char(ROW(0), LINE(6), char_6);
    print_LCD_char(ROW(0), LINE(7), char_7);
    print_LCD_char(ROW(0), LINE(8), char_8);
}

void    mode_test(void)
{
    static int print = 0;

    if (but == RIGHT_SHORT)
        cali_GYRO(0);
    else if (but == LEFT_SHORT)
    {
        delay_ms(1000);
        print = gyr.acc_x;
        print_LCD_nb(ROW(6), LINE(3), NEG(print), ABS(print), 0);
        print = gyr.acc_y;
        print_LCD_nb(ROW(6), LINE(5), NEG(print), ABS(print), 0);
        print = gyr.acc_z;
        print_LCD_nb(ROW(6), LINE(7), NEG(print), ABS(print), 0);
        print = gyr.acc_x_cali;
        print_LCD_nb(ROW(11), LINE(3), NEG(print), ABS(print), 0);
        print = gyr.acc_y_cali;
        print_LCD_nb(ROW(11), LINE(5), NEG(print), ABS(print), 0);
        print = gyr.acc_z_cali;
        print_LCD_nb(ROW(11), LINE(7), NEG(print), ABS(print), 0);
        print = gyr.acc_x - gyr.acc_x_cali;
        print_LCD_nb(ROW(17), LINE(3), NEG(print), ABS(print), 0);
        print = gyr.acc_y - gyr.acc_y_cali;
        print_LCD_nb(ROW(17), LINE(5), NEG(print), ABS(print), 0);
        print = gyr.acc_z - gyr.acc_z_cali;
        print_LCD_nb(ROW(17), LINE(7), NEG(print), ABS(print), 0);
    }
}