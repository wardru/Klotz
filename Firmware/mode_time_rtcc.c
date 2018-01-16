#include "klotz.h"

u8 time_set;
u8 time_mode;
u16 blink_time;
t_clock clock;
t_count count;
t_stop stop;

void    init_RTC(void)
{
    while (!OSCCONbits.SOSCRDY)
        ;
    RTCCONbits.SIDL = 0;
    RTCCONbits.RTSECSEL = 0;
    RTCCONbits.RTCOE = 0;
    SYSKEY = 0xaa996655; // write first unlock key to SYSKEY
    SYSKEY = 0x556699aa; // write second unlock key to SYSKEY
    RTCCONbits.RTCWREN = 1;
    RTCCONbits.ON = 0;
    while (RTCCONbits.RTCCLKON)
        ;
    RTCTIME = 0x23540000;
    RTCDATE = 0x17091801;
    RTCCONbits.ON = 1;
    while (!RTCCONbits.RTCCLKON)
        ;
    RTCCONbits.RTCWREN = 0;
}

void    init_time(const u8 boot)
{
    if (boot)
    {
        time_mode = TIME_CLOCK;
        date_print = TRUE;
        init_clock();
    }
    init_count();
    init_stop();
    time_set = FALSE;
}

void    write_RTC(const u32 date, const u32 time)
{
    RTCCONbits.RTCWREN = 1;
    RTCCONCLR = 0x8000; // turn off the RTCC
    while(RTCCON & 0x40)
        ;
    RTCDATE = date;
    RTCTIME = time;
    RTCCONSET = 0x8000; // turn on the RTCC
    while(!(RTCCON & 0x40))
        ;
    RTCCONbits.RTCWREN = 0;
}

void    write_time_and_date(void)
{
    u32 date;
    u32 time;
    
    date = (clock.YEAR10 * 16 + clock.YEAR01) << 24 | (clock.MONTH10 * 16 + clock.MONTH01) << 16 | (clock.DAY10 * 16 + clock.DAY01) << 8 | clock.WDAY01;
    time = (clock.HR10 * 16 + clock.HR01) << 24 | (clock.MIN10 * 16 + clock.MIN01) << 16;
    write_RTC(date, time);
    print_clock(1);
}

void    set_time(void)
{
    if (blink_trig && ++blink_time)
        blink_trig = 0;
    if (but)
        blink_time = 0;
    if (time_mode == TIME_CLOCK)
        clk_set_loop[time_set - 1]();
    else if (time_mode == TIME_COUNT)
        count_set_loop[time_set - 1]();
}

void    mode_page_time(void)
{
    time_page[time_mode]();
}

void    mode_time(void)
{
    if (but == LEFT_SHORT && !time_set)
    {
        if (++time_mode == TIME_SIZE)
            time_mode = 0;
        else if (time_mode == TIME_CLOCK + 1)
            print_LCD_tk(1);
        mode_page_time();
    }
    time_loop[time_mode]();
}