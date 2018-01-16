#include "klotz.h"

unsigned char date_print;

void    menu_page_time(void)
{
    u8 tmp;
    
    tmp = time_mode;
    mode = MODE_TIME;
    time_mode = TIME_CLOCK;
    clear_LCD(BK_CLR);
    print_LCD_tk(1);
    if (date_print)
    {
        print_LCD_window(ROW(11) + 3, Y_DATE + 9, 1, 2, 0xFFFF);                 // Print 1. dot date
        print_LCD_window(ROW(14) + 3, Y_DATE + 9, 1, 2, 0xFFFF);                 // Print 2. dot date
    }
    print_LCD_window(62, Y_TIME + 17, 4, 4, 0xFFFF);                 // Print double dot for count
    print_LCD_window(62, Y_TIME + 29, 4, 4, 0xFFFF);
    mode = MENU_SET;
    time_mode = tmp;
}

void    menu_time(void)
{
    if (but == RIGHT_SHORT)
    {
        mode_page[(mode = MODE_MENU)]();
        print_LCD_tk(1);
    }
    else if (but == LEFT_SHORT)
    {
        date_print = !date_print;
        menu_page_time();
    }
}