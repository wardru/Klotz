#include "klotz.h"

void    init_LCD_pins(void)
{
    RPB13R = 0b0011;    //Setting pin 13 (SPI_DATA) to SDO1
    T_RS = 0;     //Setting pin 7 (RS) to output
    L_RS = 0;
    T_RESET = 0;    //Setting pin 10 (RESET) to output
    L_RESET = 0;
    T_CS = 0;    //Setting pin 11 (CS) to output
    L_CS = 0;
    T_SCLK = 0;    //Setting pin 14 (SCLK) to output
    L_SCLK = 0;
}

void    set_CS(const u8 i)
{
    L_CS = i;
}

void    set_RESET(const u8 i)
{
    L_RESET = i;
}

void    set_RS(const u8 i)
{
    L_RS = i;
}

void    write_LCD(const u32 write)
{
    SPI1BUF = write;
    while(!SPI1STATbits.SPIRBF)
        ;
    SPI1BUF;
}

void    cmd_LCD(const u32 cmd)
{
    set_RS(0);
    write_LCD(cmd);
    set_RS(1);
}

void    set_LCD_window(const u16 x1, const u16 y1, const u16 x2, const u16 y2)
{
    cmd_LCD(ST7735_CASET);
    write_LCD(0x00);
    write_LCD(x1);
    write_LCD(0x00);
    write_LCD(x1 + x2);
    cmd_LCD(ST7735_RASET);
    write_LCD(0x00);
    write_LCD(y1);
    write_LCD(0x00);
    write_LCD(y1 + y2);
    cmd_LCD(ST7735_RAMWR);
}

void    set_LCD_rot(const u8 rot)           // point == '0x68' origin | '0x08' 90° right | '0xC8' 90° left | '0xA8' 180°
{
    set_CS(0);
    cmd_LCD(ST7735_MADCTL);
    write_LCD(rot);
    shift.x = 0;
    shift.y = 0;
    if (rot == ROT_DOWN)
        shift.x = 32;
    else if (rot == ROT_LEFT)
        shift.y = 32;
    set_CS(1);
}

void    rot_LCD(void)
{
    static u8 ori = ROT_INIT;
    static u8 last = ROT_INIT;

    if (ABS(gyr.acc[2]) < 2500)                // 40°deg on a side
    {
        if (ori != ROT_UP && gyr.acc[1] < -3548 && gyr.acc[0] < 2049)                      // switch at 60°deg
            ori = ROT_UP;
        else if (ori != ROT_LEFT && gyr.acc[0] > 3548 && gyr.acc[1] > -2049)               // switch at 60°deg
            ori = ROT_LEFT;
        else if (ori != ROT_RIGHT && gyr.acc[0] < -3548 && gyr.acc[1] < 2049)             // switch at 40°deg
            ori = ROT_RIGHT;
        else if (ori != ROT_DOWN && gyr.acc[1] > 3548 && gyr.acc[0] > -2049)                // switch at 60°deg
            ori = ROT_DOWN;
        if (last != ori)
        {
            set_LUM(0);
            set_LCD_rot((last = ori));
            clear_LCD_tk(BK_CLR);
            print_LCD_tk(1);
            (mode == MENU_SET) ? menu_page[menu_mode]() : mode_page[mode]();
            set_LUM(lum_lvl);
        }
    }
}

void    init_LCD(void)
{
    init_LCD_pins();
    set_LUM(0);
    init_SPI();
    set_RESET(0);
    delay_ms(10);
    set_RESET(1);
    delay_ms(10);
    set_CS(0);
    cmd_LCD(ST7735_SWRESET);//Sleep exit
    delay_ms(120);
    cmd_LCD(ST7735_SLPOUT);
    delay_ms(120);
    cmd_LCD(ST7735_FRMCTR1);
    write_LCD(0x01);
    write_LCD(0x2C);
    write_LCD(0x2D);
    cmd_LCD(ST7735_FRMCTR2);
    write_LCD(0x01);
    write_LCD(0x2C);
    write_LCD(0x2D);
    cmd_LCD(ST7735_FRMCTR3);
    write_LCD(0x01);
    write_LCD(0x2C);
    write_LCD(0x2D);
    write_LCD(0x01);
    write_LCD(0x2C);
    write_LCD(0x2D);
    cmd_LCD(ST7735_INVCTR); //Column inversion
    write_LCD(0x07);
    cmd_LCD(ST7735_PWCTR1);
    write_LCD(0x5C);
    write_LCD(0x1C);
    write_LCD(0x84);
    cmd_LCD(ST7735_PWCTR2);
    write_LCD(0x0A);
    write_LCD(0x00);
    cmd_LCD(ST7735_PWCTR3);
    write_LCD(0x8A);
    write_LCD(0x2A);
    cmd_LCD(ST7735_PWCTR4);
    write_LCD(0x8A);
    write_LCD(0xEE);
    cmd_LCD(ST7735_PWCTR5);
    write_LCD(0x0E);
    cmd_LCD(ST7735_VMCTR1);
    write_LCD(0x00);
    cmd_LCD(ST7735_COLMOD);
    write_LCD(0x5);
    set_CS(1);

    set_LCD_rot(ROT_INIT);
    set_LCD_window(0, 0, 127, 127);

    set_CS(0);
    cmd_LCD(ST7735_GMCTRP1);
    write_LCD(0x02);
    write_LCD(0x1C);
    write_LCD(0x07);
    write_LCD(0x12);
    write_LCD(0x37);
    write_LCD(0x32);
    write_LCD(0x29);
    write_LCD(0x2D);
    write_LCD(0x29);
    write_LCD(0x25);
    write_LCD(0x2B);
    write_LCD(0x39);
    write_LCD(0x00);
    write_LCD(0x01);
    write_LCD(0x03);
    write_LCD(0x10);
    cmd_LCD(ST7735_GMCTRN1);
    write_LCD(0x03);
    write_LCD(0x1D);
    write_LCD(0x07);
    write_LCD(0x06);
    write_LCD(0x2E);
    write_LCD(0x2C);
    write_LCD(0x29);
    write_LCD(0x2D);
    write_LCD(0x2E);
    write_LCD(0x2E);
    write_LCD(0x37);
    write_LCD(0x3F);
    write_LCD(0x00);
    write_LCD(0x00);
    write_LCD(0x02);
    write_LCD(0x10);
    cmd_LCD(ST7735_NORON);
    delay_ms(10);
    cmd_LCD(ST7735_DISPON);
    delay_ms(100);
    cmd_LCD(ST7735_RAMWR);
    delay_ms(100);
    set_CS(1);
    clear_LCD_pg(BK_CLR);
}