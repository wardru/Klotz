#include "klotz.h"

void    init_SPI(void)
{
    SPI1CONbits.ON = 0;
    SPI1CONbits.MSTEN = 1;
    SPI1CONbits.SIDL = 0;
    SPI1CONbits.DISSDO = 0;
    SPI1CONbits.SSEN = 0;
    SPI1CONbits.SMP = 0;
    SPI1CONbits.CKP = 0;
    SPI1BRG = 0x0;
    SPI1CONbits.CKE = 1;
    SPI1CONbits.MODE16 = 0;
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.ON = 1;
}

void    print_LCD_window(u8 x, u8 y, const u8 sx, const u8 sy, const u16 color)
{
    x += shift.x;
    y += shift.y;
    u8 ty = y;
    u8 tx = x;
    
    set_CS(0);
    set_LCD_window(x, y, sx - 1, sy - 1);
    while (ty < y + sy)
    {
        tx = x; 
        while (tx < x + sx)
        {
            write_LCD(color >> 8);
            write_LCD(color);
            tx++;
        }
        ty++;
    }
    set_CS(1);
}

void    clear_LCD(const u16 color)
{
    print_LCD_window(0, 0, 128, 128, color);
}

void    clear_LCD_pg(const u16 color)
{
    print_LCD_window(0, 15, 128, 113, color);
}

void    clear_LCD_menu(const u16 color)
{
    print_LCD_window(0, 17, 128, 111, color);
}

void    clear_LCD_tk(const u16 color)
{
    print_LCD_window(0, 0, 128, 15, color);
}

void    print_LCD_tk(const u8 force)
{
    print_BAT(force);
    print_clock(force);
    if (force && !(mode == MODE_TIME && time_mode == TIME_CLOCK))
    {
        print_LCD_window(ROW(2) + 3, LINE(0) + 5, 1, 2, 0xFFFF);                 // Print double dot for hour
        print_LCD_window(ROW(2) + 3, LINE(0) + 9, 1, 2, 0xFFFF);
    }
}

void    print_LCD_char(u8 x, u8 y, const u8 *c)
{
    u16 cell;
    u16 size;
    
    x += shift.x;
    y += shift.y;
    cell = 1;
    size = (c[0]) ? 1836 : 196;
    set_CS(0);
    set_LCD_window(x, y, X_STA + c[0] * 20 - 1, Y_STA + c[0] * 20 - 1);
    while (cell <= size)
        write_LCD(c[cell++]);                                                      //sliver
    set_CS(1);
}

void    print_LCD_char_BIG(u8 x, u8 y, const u8 *c)
{
    s32 len;
    
    x += shift.x;
    y += shift.y;
    len = 1;
    set_CS(0);
    set_LCD_window(x, y, X_BIG - 1, Y_BIG - 1);
    while (len <= 1836)
        write_LCD(c[len++]);                                                    //silver
    set_CS(1);
}

void    print_LCD_str(u8 x, u8 y, const u8 *str)
{
    while (*str)
    {
        if (x + X_STA > 127 && (x = 1))
            y += Y_STA;
        if (*str >= 97 && *str <= 122)
            print_LCD_char(x, y, alpha_l[*str - 97]);
        else if (*str >= 65 && *str <= 90)
            print_LCD_char(x, y, alpha_L[*str - 65]);
        else if (*str >= 48 && *str <= 57)
            print_LCD_char(x, y, alpha_n[*str - 48]);
        else if (*str == '.')
            print_LCD_window(x + 3, y + 9, 1, 2, 0xFFFF);
        else if (*str == ':')
        {
            print_LCD_window(x + 3, y + 5, 1, 2, 0xFFFF);
            print_LCD_window(x + 3, y + 9, 1, 2, 0xFFFF);
        }
        else
            blank(x, y, 1, STA);
        x += X_STA;
        str++;
    }
}

u8      cnt_digit(const s32 nb)
{
    if (nb >= 10)
        return (1 + cnt_digit(nb / 10));
    else if (nb < 0)
        return (1 + cnt_digit(nb / 10));
    return (1);
}

void    print_LCD_nb_new(u8 x, u8 y, u8 nd, s32 nb, const u8 dot)
{
    if (nb < 0 && (nb = -nb))
    {
        x += X_STA;
        y += Y_STA;
        print_LCD_window(x + 2, y + 6, 4, 1, 0xFFFF);
    }
    if (!nd--)
        print_LCD_nb_new(x + X_STA, y + Y_STA, nd, nb / 10, dot);
    if (nd && dot)
    {
        print_LCD_window(x + 3, y + 9, 1, 2, 0xFFFF);
        x += X_STA;
    }
    print_LCD_char(x, y, alpha_n[nb % 10]);
}

void    print_LCD_nb(u8 x, const u8 y, u8 s, const u32 nb, const u8 dot)
{
    static u8 i;
    u8 dot_shft;
    
    dot_shft = dot * X_STA;
    if (nb / 10 && ++i)
        print_LCD_nb(x, y, s, nb / 10, dot);
    else if (s)
        print_LCD_window(x - (i + 1) * X_STA + 2 - dot_shft, y + 6, 4, 1, 0xFFFF);
    if (!i && dot)
    {
        print_LCD_window(x + 3 - dot_shft, y + 9, 1, 2, 0xFFFF);
        x += X_STA;
    }
    print_LCD_char(x - ((i) ? i-- * X_STA : i) - dot_shft, y, alpha_n[nb % 10]);
}

void    print_LCD_nb_BIG(u8 x, const u8 y, u8 s, const u32 nb, const u8 dot)
{
    static u8 i;
    u8 dot_shft;

    dot_shft = dot * X_BIG;
    if (nb / 10 && ++i)
        print_LCD_nb_BIG(x, y, s, nb / 10, dot);
    else if (s)
    {
        s = x - (i + 1) * X_BIG - dot_shft;
        print_LCD_window(s + 2, y, 22, 17, BK_CLR);
        print_LCD_window(s + 8, y + 17, 16, 4, 0xFFFF);
        print_LCD_window(s + 2, y + 21, 23, 15, BK_CLR);
    }
    if (!i && dot)
    {
        print_LCD_window(x + 6 - dot_shft, y + 30, 4, 4, 0xFFFF);
        x += X_BIG - DOT_BIG;
    }
    print_LCD_char_BIG(x - ((i) ? i-- * X_BIG : 0) - dot_shft, y, alpha_N[nb % 10]);
}

void    print_LCD_img(const u8 x, const u8 y, const char *img)
{
    u16 i = 2;
    u16 len = img[0] * img[1] * 2 + 2;
    set_CS(0);
    set_LCD_window(x + shift.x, y + shift.y, img[0] - 1, img[1] - 1);
    while (i < len)
        write_LCD(img[i++]);
    set_CS(1);
}

void    clear_LCD_img(const u8 x, const u8 y, const char *img, const u16 color)
{
    u16 len = img[0] * img[1] + 1;
    set_CS(0);
    set_LCD_window(x + shift.x, y + shift.y, img[0] - 1, img[1] - 1);
    while (len--)
    {
        write_LCD(color >> 8);
        write_LCD(color);
    }
    set_CS(1);
}

void    print_128(const u8 *photo)
{
    u16 len = 0;
    set_CS(0);
    set_LCD_window(0 + shift.x, 0 + shift.y, 127, 127);
    while (len < 32768)
        write_LCD(photo[len++]);
    set_CS(1);
}

void    inv_LCD_clr(const u8 inv)
{
    set_CS(0);
    if (inv)
        cmd_LCD(0x21);
    else
        cmd_LCD(0x20);
    set_CS(1);
}

void    print_logo_mode(void)
{
    print_128(logo);
    set_LUM(lum_lvl);
    cali_GYRO(TRUE);
    calc_GYRO_TEMP();
    init_rot();
    set_LUM(0);
    clear_LCD_tk(BK_CLR);
    print_LCD_tk(1);
    mode_page[mode]();
    set_LUM(lum_lvl);
}