#include "klotz.h"

u8 but;

void    init_BUT(void)
{
    T_BUT0 = 1;
    T_BUT1 = 1;
}

u8     get_BUT(void)
{
    static u8 left = 0;
    static s16 cnt = 0;
    
    if (RIGHT_BUT || LEFT_BUT)
    {
        if (cnt >= 0)
        {
            left = LEFT_BUT;
            if (cnt++ == 100 && (cnt = -1))
            {
                set_BUZ(0);
                return ((left) ? LEFT_LONG : RIGHT_LONG);
            }
            else if (cnt == 5)
                set_BUZ(0);
            else if (cnt == 1 || cnt == 95)
                set_BUZ((left && mode == MENU_SET && menu_mode == MENU_BUZ) ? !buz_state : buz_state);
        }
    }
    else if (cnt)
    {
        set_BUZ(0);
        if (cnt > 1 && !(cnt = 0))
            return ((left) ? LEFT_SHORT : RIGHT_SHORT);
        cnt = 0;
    }
    return (0);
}