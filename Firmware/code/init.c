#include "klotz.h"

void    init_change_notice(void)
{
    __builtin_disable_interrupts();

    CNCONBbits.ON = 1;
    CNENBbits.CNIEB5 = 1;                           // Enable RPB5 pin for interrupt detection

    IPC8bits.CNIP = 3;
    IPC8bits.CNIS = 2;
    IFS1bits.CNBIF = 0;                             // Reset CN interrupt
    IEC1bits.CNBIE = 1;                             // Enable CN interrupts
    INTCONbits.MVEC = 1;

    __builtin_enable_interrupts();
}

void    init_arrays(void)
{
    mode_loop[MODE_TIME] = mode_time;
    time_loop[TIME_CLOCK] = time_clock;
    clk_set_loop[CLOCK_YEAR] = clock_set_YEAR;
    clk_set_loop[CLOCK_MONTH] = clock_set_MONTH;
    clk_set_loop[CLOCK_DAY] = clock_set_DAY;
    clk_set_loop[CLOCK_WDAY] = clock_set_WDAY;
    clk_set_loop[CLOCK_HR] = clock_set_HR;
    clk_set_loop[CLOCK_MIN] = clock_set_MIN;
    time_loop[TIME_COUNT] = time_count;
    count_set_loop[COUNT_SEC] = count_set_SEC;
    count_set_loop[COUNT_MIN] = count_set_MIN;
    count_set_loop[COUNT_HR] = count_set_HR;
    time_loop[TIME_STOP] = time_stop;

    mode_loop[MODE_TEMP] = mode_temp;
    mode_loop[MODE_GAME] = mode_game;
    mode_loop[MODE_GYRO] = mode_gyro;
    mode_loop[MODE_MENU] = mode_menu;
    menu_loop[MENU_LUM] = menu_lum;
    menu_loop[MENU_BUZ] = menu_buz;
    menu_loop[MENU_LANG] = menu_lang;
    menu_loop[MENU_ROT] = menu_rot;
    menu_loop[MENU_ABOUT] = menu_about;
    menu_loop[MENU_TIME] = menu_time;
    menu_loop[MENU_GAME] = menu_game;
    menu_loop[MENU_ALARM] = menu_alarm;
    menu_loop[MENU_INV] = menu_inv;

    mode_loop[MODE_MENU] = mode_menu;
    mode_page[MODE_TIME] = mode_page_time;
    time_page[TIME_CLOCK] = time_page_clock;
    time_page[TIME_COUNT] = time_page_count;
    time_page[TIME_STOP] = time_page_stop;

    mode_page[MODE_TEMP] = mode_page_temp;
    mode_page[MODE_GAME] = mode_page_game;
    mode_page[MODE_GYRO] = mode_page_gyro;
    mode_page[MODE_MENU] = mode_page_menu;
    menu_page[MENU_LUM] = menu_page_lum;
    menu_page[MENU_BUZ] = menu_page_buz;
    menu_page[MENU_LANG] = menu_page_lang;
    menu_page[MENU_GAME]= menu_page_game;
    menu_page[MENU_ROT] = menu_page_rot;
    menu_page[MENU_ABOUT] = menu_page_about;
    menu_page[MENU_TIME]= menu_page_time;
    menu_page[MENU_ALARM]= menu_page_alarm;
    menu_page[MENU_INV]= menu_page_inv;

    if (MODE_TEST != MODE_SIZE)
    {
        mode_loop[MODE_TEST] = mode_test;
        mode_page[MODE_TEST] = mode_page_test;
    }
}

void    init_pins(void)
{
    TRISB = 0;
    TRISA = 0;
    LATB = 0;
    LATA = 0;
}

void    init_protocols(void)
{
    init_timers();
    init_ADC();
    init_IND();
    init_PWM();
    init_LCD();                             // protocol ? more like device, please split into init_protocol (SPI) and init_device (LCD)
    init_RTC();
    init_BUT();                             // also init_device
    init_BUZ();                             // init_device
    init_alpha();
    init_strings();
    init_GYRO();                            // init_device
    init_change_notice();                   // init_but_interrupt
}

void    init_variables(const u8 boot)
{
    if (boot)
    {
        mode = MODE_TIME;                                   // start up MODE
        buz_state = TRUE;                                   // sound is on
        lang_mode = LANG_FR;                                // French
        menu_mode = MENU_LUM;                               // start up MENU
        lum_lvl = LUM_LVL(1);                               // choose level of brightness
        rot_state = TRUE;                                   // activated rotation
        inv_state = FALSE;                                  // display invertation
        temp_mode = TEMP_CUR;                               // display current temp
    }
    if (mode == MENU_SET)
        mode = MODE_MENU;
    but = FALSE;                                            // no button pressed
    gyro_trig = FALSE;
    temp_trig = FALSE;
    game_trig = FALSE;
    count_trig = FALSE;
    stop_trig = FALSE;
    blink_trig = FALSE;
    blink_time = FALSE;
    init_alarm(boot);
    init_time(boot);                                        
    init_game(boot);
    bat_state = 5;                                          // battery is fully charged
}

void    init_rot(void)
{
    u8 ori = ROT_INIT;
    
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
        set_LCD_rot(ori);
    }
}