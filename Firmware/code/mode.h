#ifndef MODE_H
 #define MODE_H

 #define TRUE       1
 #define FALSE      0

// MODE_MODE DEFINES
 #define MODE_TIME  0
 #define MODE_TEMP  1
 #define MODE_GYRO  2
 #define MODE_GAME  3
 #define MODE_MENU  4
 #define MODE_TEST  5
 #define MODE_SIZE  5                                       // increase by one to get a TEST mode

// MENU_MODE DEFINES
 #define MENU_SET  -1                                       // do not change
 #define MENU_LUM   0
 #define MENU_BUZ   1
 #define MENU_ROT   2
 #define MENU_TIME  3
 #define MENU_GAME  4
 #define MENU_LANG  5
 #define MENU_ALARM 6
 #define MENU_INV   7
 #define MENU_ABOUT 8
 #define MENU_SIZE  9

// LANG_MODE DEFINES
 #define LANG_FR    0
 #define LANG_EN    1
 #define LANG_DE    2
 #define LANG_SIZE  3

// TIME_MODE DEFINES
 #define TIME_CLOCK 0                                       // do not change
 #define TIME_COUNT 1
 #define TIME_STOP  2
 #define TIME_SIZE  3

// CLOCK_MODE DEFINES
 #define CLOCK_YEAR  0
 #define CLOCK_MONTH 1
 #define CLOCK_DAY   2
 #define CLOCK_WDAY  3
 #define CLOCK_HR    4
 #define CLOCK_MIN   5
 #define CLOCK_SIZE  6

// COUNT_MODE DEFINES
 #define COUNT_SEC  0
 #define COUNT_MIN  1
 #define COUNT_HR   2
 #define COUNT_SIZE 3

// GAME_MODE DEFINES
 #define GAME_5S    0
 #define GAME_10S   1
 #define GAME_15S   2
 #define GAME_20S   3
 #define GAME_SIZE  4

// ALARM_MODE DEFINES
 #define ALARM_OFF  0
 #define ALARM_1    1
 #define ALARM_2    2
 #define ALARM_3    3
 #define ALARM_SIZE 4

// GYRO_MODE DEFINES
 #define GYRO_X     0
 #define GYRO_Y     1
 #define GYRO_Z     2
 #define GYRO_SIZE  3

// TEMP_MODE DEFINES
 #define TEMP_CUR   0
 #define TEMP_AVG   1
 #define TEMP_SIZE  2

#endif