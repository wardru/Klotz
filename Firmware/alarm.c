#include "klotz.h"

u8  alarm_mode;
u8  alarm_state;

void    init_alarm(const u8 boot)
{
    if (boot)
        alarm_mode = ALARM_2;
    alarm_state = FALSE;
}

void    alarm(void)
{
    static u16 alarm_cnt = 0;
    
    if (alarm_state && !alarm_cnt--)
    {
        alarm_cnt = 749;
        if (alarm_state++ % 2)
            set_BUZ(1);
        else if (alarm_state == 3 + (alarm_mode - 1) * 4)         // alarm_mode times buzzering
            set_BUZ((alarm_state = 0));
        else
            set_BUZ(0);
    }
    else if(!alarm_state && alarm_cnt)
        alarm_cnt = 0;
}