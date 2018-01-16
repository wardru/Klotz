#ifndef STRINGS_H
 #define	STRINGS_H

 #include "mode.h"

 #define BLINK_FREQ 4

 extern unsigned short  blink_trig;
 extern unsigned short  blink_time;
 
 extern const unsigned char *mode_menu_str[MENU_SIZE][LANG_SIZE];
 extern const unsigned char *mode_game_str[2][LANG_SIZE];
 extern const unsigned char *menu_game_str[GAME_SIZE][LANG_SIZE];
 extern const unsigned char *alarm_str[ALARM_SIZE][LANG_SIZE];
 extern const unsigned char *time_wday_str[7][LANG_SIZE];
 extern const unsigned char *time_mode_str[TIME_SIZE - 1][LANG_SIZE];

 extern const unsigned char mode_gyro_str[LANG_SIZE][6];
 extern const unsigned char menu_lang_str[LANG_SIZE][9];
 extern const unsigned char mode_temp_str[LANG_SIZE][18];

#endif

