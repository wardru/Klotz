#include "klotz.h"

s8 mode;

 void   __ISR(_CHANGE_NOTICE_VECTOR, IPL3SOFT) ChangeNotice_Handler(void)
 { 
//    u32 port = PORTB; // clear port mismatch
    PORTB; // clear port mismatch

    IFS1bits.CNBIF = 0; //CLEAR CNB Interrupt FLAG
 } 
 
 void   __ISR(_COMPARATOR_3_VECTOR, IPL3SOFT)Cmp3_IntHandler(void)
{
    IFS1bits.CMP3IF = 0; // Clear the CMP3 interrupt flag
}

void    activate_periph(void)
{
    PMD1 = 0xFFFFEFFE;
    PMD2 = 0xFFFFFFFB;
    PMD3 = 0xFFFDFFFF;
    PMD4 = 0;
    PMD5 = 0xFFFEFEFF;
    PMD6 = 0xFFFFFFFE;
}

int     main(void)
{
    u16 trig;
    
    trig = 0;
    
    init_pins();
    init_arrays();
    activate_periph();
    init_protocols();
    init_variables(TRUE);
    print_logo_mode();
    while (1)
    {     
//        if (!CM3CONbits.COUT)
//            sleep();
        if (I0b.T1IF)                                   // 1ms timer
        {
            PR1 = 625;
            I0b.T1IF = 0;
            alarm();
            calc_count();
            calc_stop();
        }
        if (I0b.T5IF)                                   // 10ms timer
        {
            PR5 = 6250;
            I0b.T5IF = 0;
            if ((but = get_BUT()) && alarm_state && !(alarm_state = 0))
                but = 0;
            if (but == RIGHT_LONG)
            {
                if (mode == MODE_TIME)
                {
                    if (time_set && !(time_set = 0))
                    {
                        if (time_mode == TIME_CLOCK)
                            write_time_and_date();
                        else if (time_mode == TIME_COUNT)
                            write_count();
                    }
                }
                else if (mode == MENU_SET && menu_mode == MENU_INV)
                    print_LCD_window(38, 8, 53, 7, BK_CLR);
                mode = (mode + 1 == MODE_SIZE) ? 0 : mode + 1;
                set_LUM(0);
                if (mode == MODE_TIME + 1)
                    print_LCD_tk(TRUE);
                mode_page[mode]();
                set_LUM(lum_lvl);
            }
            else if (but == LEFT_LONG)
                sleep();
            (mode == MENU_SET) ? menu_loop[menu_mode]() : mode_loop[mode]();
            game_trig = 1;
        }
        if (I0b.T4IF)
        {
            PR4 = 6250;                                 // 40ms timer
            I0b.T4IF = 0;
            calc_GYRO_TEMP();
        }
        if (I0b.T3IF)                                   // 100ms timer
        {
            PR3 = 62500;
            I0b.T3IF = 0;
            gyro_trig = 1;
            temp_trig = 1;
            blink_trig = 1;
            if (!but && rot_state)
                rot_LCD();
        }
        if (clock.SEC01 != RTb.SEC01)                   // 1sec timer
        {
            clock.SEC01 = RTb.SEC01;
            print_LCD_tk(0);
            if (!RTb.SEC01 && !RTb.SEC10 && !RTb.MIN01 && !RTb.MIN10)
            {
                if (!RTb.HR01 && !RTb.HR10)
                {
                    gyr.sum = gyr.temp[TEMP_CUR];
                    gyr.div = 1;
                    gyr.temp[TEMP_AVG] = gyr.sum;
                }
                else if (RTb.HR01 == 3 && !RTb.HR10)
                    cali_GYRO(1);
            }
        }
    }
    return (0);
}