#ifndef     KLOTZ_H
 #define    KLOTZ_H

 #include <xc.h>
 #include "pins.h"
 #include "time.h"
 #include "screen.h"
 #include "power.h"
 #include "colors.h"
 #include <math.h>
 #include "fonts.h"
 #include "gyro.h"
 #include "menu.h"
 #include "rotation.h"
 #include "strings.h"
 #include "buz.h"
 #include "mode.h"
 #include <stdlib.h>
 #include <sys/attribs.h>

 #define ABS(A)   (A > 0) ? A : -A
 #define NEG(A)   (A < 0) ? 1 : 0

// BUTTONS DEFINES
 #if ROT_INIT == ROT_UP
  #define LEFT_BUT P_BUT0
  #define RIGHT_BUT P_BUT1
 #else
  #define LEFT_BUT P_BUT1
  #define RIGHT_BUT P_BUT0
 #endif
 #define LEFT_LONG   1
 #define LEFT_SHORT  2
 #define RIGHT_LONG  3
 #define RIGHT_SHORT 4

 #define ALARM(X) ((X < ALARM_OFF) ? ALARM_OFF : ((X > ALARM_SIZE) ? ALARM_SIZE : X))

 typedef signed char    s8;
 typedef signed short   s16;
 typedef signed int    s32;
 typedef unsigned char  u8;
 typedef unsigned short u16;
 typedef unsigned int  u32;

 extern u8 but;
 extern u8 buz_state;
 extern u8 alarm_mode;
 extern s8 mode;
 extern u8 menu_mode;
 extern u8 lum_lvl;
 extern const unsigned char logo[32768];
 extern u8 inv_state;
 extern u16 game_score;
 extern u8 game_mode;
 extern u8 game_trig;
 extern u8 game_state;
 extern u8 alarm_state;

 void (*clk_set_loop[CLOCK_SIZE])(void);
 void    clock_set_YEAR(void);
 void    clock_set_MONTH(void);
 void    clock_set_DAY(void);
 void    clock_set_WDAY(void);
 void    clock_set_HR(void);
 void    clock_set_MIN(void);

 void (*count_set_loop[COUNT_SIZE])(void);
 void    count_set_SEC(void);
 void    count_set_MIN(void);
 void    count_set_HR(void);

 void (*mode_loop[MODE_SIZE])(void);
 void    mode_time(void);
 void    mode_temp(void);
 void    mode_gyro(void);
 void    mode_game(void);
 void    mode_menu(void);
 void    mode_test(void);
 void (*mode_page[MODE_SIZE])(void);
 void    mode_page_time(void);
 void    mode_page_temp(void);
 void    mode_page_gyro(void);
 void    mode_page_menu(void);
 void    mode_page_test(void);

 void (*menu_loop[MENU_SIZE])(void);
 void    menu_lum(void);
 void    menu_buz(void);
 void    menu_lang(void);
 void    menu_rot(void);
 void    menu_about(void);
 void    menu_time(void);
 void    menu_game(void);
 void    menu_alarm(void);
 void    menu_inv(void);
 void (*menu_page[MENU_SIZE])(void);
 void    menu_page_lum(void);
 void    menu_page_buz(void);
 void    menu_page_lang(void);
 void    mode_page_game(void);
 void    menu_page_rot(void);
 void    menu_page_about(void);
 void    menu_page_time(void);
 void    menu_page_game(void);
 void    menu_page_alarm(void);
 void    menu_page_inv(void);

 void (*time_loop[TIME_SIZE])(void);
 void    time_clock(void);
 void    time_count(void);
 void    time_stop(void);
 void (*time_page[TIME_SIZE])(void);
 void    time_page_clock(void);
 void    time_page_count(void);
 void    time_page_stop(void);

#endif

