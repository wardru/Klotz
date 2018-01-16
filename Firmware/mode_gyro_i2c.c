#include "klotz.h"

u8 gyro_mode;
u8 gyro_trig;
t_gyr gyr;
t_rot shift;

void    init_I2C(void)                                              // Inter-Integrated Circuit for "MODE_GYRO" application
{
    I2Cb.ON = 0;
    I2Cb.SIDL = 0;       // Stop in Idle Mode bit                        -> Continue module operation when the device enters Idle mode
    I2Cb.A10M = 0;       // 10-bit Slave Address Flag bit                -> I2CxADD register is a 7-bit slave address
    I2Cb.DISSLW = 1;     // Slew Rate Control Disable bit                -> Slew rate control disabled for Standard Speed mode (100 kHz)
    I2Cb.ACKDT = 0;
    I2Cb.ON = 1;
    I2C1BRG = 0x30;
}

void    start_GYRO(const u8 addr)
{
    I2Cb.SEN = 1;
    while(I2Cb.SEN)            // SEN is to be cleared when I2C Start procedure has been completed
        ;
    I2C1TRN = addr;
    while (I2C1STATbits.TRSTAT)
            ;
    while (I2C1STATbits.ACKSTAT)
        ;
}

void    restart_GYRO(const u8 addr)
{
    I2Cb.RSEN = 1;
    while(I2Cb.RSEN)            // RSEN is to be cleared when I2C Start procedure has been completed
        ;
    I2C1TRN = addr;
    while (I2C1STATbits.TRSTAT)
            ;
    while (I2C1STATbits.ACKSTAT)
        ;
    
}

void    stop_GYRO(void)
{
    I2Cb.PEN = 1;
    while(I2Cb.PEN)          // PEN is to be cleared when I2C Start procedure has been completed
        ;
}

void    write_GYRO(const u8 regi)
{
    I2C1TRN = regi;
    while (I2C1STATbits.TRSTAT)
        ;
    while (I2C1STATbits.ACKSTAT)
        ;
}

u8    read_GYRO(const u8 ack)
{
    u8 buf;
    
    I2Cb.RCEN = 1;
    while (I2Cb.RCEN)
        ;
    while (I2C1STATbits.TBF)
        ;
    buf = I2C1RCV;
    while (I2C1STATbits.RBF)
        ;
    I2Cb.ACKDT = ack;
    I2Cb.ACKEN = 1;
    while(I2Cb.ACKEN)
        ;
    return (buf);
}

void    writeByte(const u8 addr1, const u8 addr2, const u8 val)
{
    start_GYRO(addr1 << 1);
    write_GYRO(addr2);
    write_GYRO(val);
    stop_GYRO();
}

void    init_GYRO(void)
{
    init_I2C();
    T_LS0 = 0;
    
    gyro_mode = GYRO_Z;

    writeByte(0x68, 0x6B, 0x00);         // wake up
    delay_ms(150);
    writeByte(0x68, 0x6B, 0x01);         // set clock on x-gyro
    writeByte(0x68, 0x1B, 0x10);         // use 1000 deg/s ([32.8])
    writeByte(0x68, 0x1C, 0x10);         // use +/-8g (ATENTION: if changed, change also GYRO_cali)
}

void    read_GYRO_data(void)
{
        start_GYRO(0xD0);
        write_GYRO(0x3B);
        restart_GYRO(0xD1);
        gyr.acc_x = (read_GYRO(0) << 8) | read_GYRO(0);
        gyr.acc_y = (read_GYRO(0) << 8) | read_GYRO(0);
        gyr.acc_z = (read_GYRO(0) << 8) | read_GYRO(0);
        gyr.temp[TEMP_CUR] =  (read_GYRO(0) << 8) | read_GYRO(0);
        gyr.rot_x = (read_GYRO(0) << 8) | read_GYRO(0);
        gyr.rot_y = (read_GYRO(0) << 8) | read_GYRO(0);
        gyr.rot_z = (read_GYRO(0) << 8) | read_GYRO(1);
        stop_GYRO();
}

void    cali_GYRO(const u8 fast)
{
    u16 i;
    s8  x = 0;
    s8  y = 0;
    s8  z = 0;
    u16 cyc;
    
    i = 0;
    gyr.rot_x_cali = 0;
    gyr.rot_y_cali = 0;
    gyr.rot_z_cali = 0;
    gyr.acc_x_cali = 0;
    gyr.acc_y_cali = 0;
    gyr.acc_z_cali = 0;
    gyr.rot[0] = 0;
    gyr.rot[1] = 0;
    gyr.rot[2] = 0;
    gyr.acc[0] = 0;
    gyr.acc[1] = 0;
    gyr.acc[2] = 0;
    if (!fast)
    {
        clear_LCD_pg(BK_CLR);
        print_LCD_str(ROW(0), LINE(4), "calibrating gyro..");
    }
    delay_ms(500);
    read_GYRO_data();
    if (gyr.acc_x < -3000)
        x = -1;
    else if (gyr.acc_y < -3000)
        y = -1;
    else if (gyr.acc_z < -3000)
        z = -1;
    else if (gyr.acc_x > 3000)
        x = 1;
    else if (gyr.acc_y > 3000)
        y = 1;
    else if (gyr.acc_z > 3000)
        z = 1;
    else
        return ;
    cyc = (fast) ? CALI_CYC / 2 : CALI_CYC;
    while (i++ <= cyc)
    {
        read_GYRO_data();
        gyr.rot_x_cali += gyr.rot_x;
        gyr.rot_y_cali += gyr.rot_y;
        gyr.rot_z_cali += gyr.rot_z;
        gyr.acc_x_cali += gyr.acc_x;
        gyr.acc_y_cali += gyr.acc_y;
        gyr.acc_z_cali += gyr.acc_z;
        delay_ms(4000 / CALI_CYC);
    }
    gyr.rot_x_cali /= cyc;
    gyr.rot_y_cali /= cyc;
    gyr.rot_z_cali /= cyc;
    gyr.acc_x_cali /= cyc;
    gyr.acc_y_cali /= cyc;
    gyr.acc_z_cali /= cyc;
    gyr.acc_x_cali -= x * 4096;
    gyr.acc_y_cali -= y * 4096;
    gyr.acc_z_cali -= z * 4096;
    if (!fast)
        blank(ROW(0), LINE(4), 18, STA);
}

void    calc_GYRO_TEMP(void)
{
    static u32 cnt = 0;
    
    read_GYRO_data();
    gyr.rot[0] += (gyr.rot_x - gyr.rot_x_cali) / ROT_DIV ;
    gyr.rot[1] += (gyr.rot_y - gyr.rot_y_cali) / ROT_DIV ;
    gyr.rot[2] += (gyr.rot_z - gyr.rot_z_cali) / ROT_DIV ;
    if (!gyr.df)
        gyr.temp[TEMP_CUR] = gyr.temp[TEMP_CUR] / 34 + 305;
    else
        gyr.temp[TEMP_CUR] = (gyr.temp[TEMP_CUR] / 34 + 305) * 1.8 + 320;
    gyr.acc[0] = (gyr.acc_x - gyr.acc_x_cali);
    gyr.acc[1] = (gyr.acc_y - gyr.acc_y_cali);
    gyr.acc[2] = (gyr.acc_z - gyr.acc_z_cali);
    if (!cnt-- && (cnt = 7499))
    {
        gyr.sum += gyr.temp[TEMP_CUR];
        gyr.temp[TEMP_AVG] = gyr.sum / ++gyr.div;
    }
}

void    mode_page_gyro(void)
{
    clear_LCD_pg(BK_CLR);
    if (gyr.rot[gyro_mode] < -999 || gyr.rot[gyro_mode] > 9999)
    {
        print_LCD_img(ROW(4), ROT_CROSS_Y, cross_R);
        print_LCD_str(ROW(8), LINE(4) - 7, "out of");
        print_LCD_str(ROW(8), LINE(4) + 7, "reach");
    }
    else
        print_LCD_nb_BIG(4 * X_BIG + 1, Y_TIME, NEG(gyr.rot[gyro_mode]), ABS(gyr.rot[gyro_mode]), 1);
    print_LCD_char(ROW(0), Y_SEC, alpha_L[23 + gyro_mode]);             // current axis
    print_LCD_str(ROW(2), Y_SEC, mode_gyro_str[lang_mode]);                  // axis string
    print_LCD_window(ROW(1) + 2, Y_SEC + 6, 4, 1, 0xFFFF);              // minus sign
}

void    mode_gyro(void)
{
    static s8 err = 0;
    static s16 last = 0;
    
    if (but == RIGHT_SHORT)                                            // short RIGHT click
    {
        if (++gyro_mode == 3)
            gyro_mode = 0;
        print_LCD_window(3, Y_TIME, 77, Y_BIG, BK_CLR);
        print_LCD_char(ROW(0), Y_SEC, alpha_L[23 + gyro_mode]);          // current axis
        gyr.rot[gyro_mode] = 0;
    }
    else if (but == LEFT_SHORT)                                       // short LEFT click
    {
        cali_GYRO(0);
        mode_page_gyro();
    }
    if (gyro_trig && last != gyr.rot[gyro_mode])
    {
        gyro_trig = 0;
        if (!err)
        {
            if ((gyr.rot[gyro_mode] < -999 || gyr.rot[gyro_mode] > 9999) && (err = 1))
            {
                print_LCD_window(3, Y_TIME, 122, Y_BIG, BK_CLR);
                print_LCD_img(ROW(4), ROT_CROSS_Y, cross_R);
                print_LCD_str(ROW(8), LINE(4) - 7, "out of");
                print_LCD_str(ROW(8), LINE(4) + 7, "reach");
                last = 0;
            }
            else
            {
                last = gyr.rot[gyro_mode];
                blank(3, Y_TIME, 4 - cnt_digit(gyr.rot[gyro_mode]), BIG);
                print_LCD_nb_BIG(4 * X_BIG + 1, Y_TIME, NEG(gyr.rot[gyro_mode]), ABS(gyr.rot[gyro_mode]), 1);
            }
        }
        else if (err && gyr.rot[gyro_mode] > -1000 && gyr.rot[gyro_mode] < 9999 && !(err = 0))
            print_LCD_window(82, Y_TIME + 1, 16, 24, BK_CLR);
    }
}