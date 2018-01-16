#include "klotz.h"

u8  inv_state;

void    menu_page_inv(void)
{
    print_128(logo);
    print_LCD_tk(1);
    if (inv_state)
        print_LCD_str(ROW(0), LINE(8), "ON");
    else
        print_LCD_str(ROW(15), LINE(8), "OFF");
}

void    menu_inv(void)
{
    if (but == RIGHT_SHORT)
    {
        clear_LCD_tk(BK_CLR);
        print_LCD_tk(1);
        mode_page[(mode = MODE_MENU)]();
    }
    else if (but == LEFT_SHORT)
    {
        inv_LCD_clr((inv_state = !inv_state));
        menu_page_inv();
    }
}