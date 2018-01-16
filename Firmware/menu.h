#ifndef MENU_H
 #define MENU_H

// #define MENU_BK_CLR        0x6B6D
 #define MENU_BK_CLR        0x0000
 #define MENU_BAR_B_SX    88
 #define MENU_BAR_B_YSIZE    20
 #define MENU_BAR_S_SIZE_X    78
 #define MENU_BAR_S_SIZE_Y    20
 #define MENU_BAR_B_X     20
 #define MENU_BAR_S_X     25
 #define MENU_BAR_Y(Y)      (Y) * 25 + 26

 extern unsigned char lang_mode;

 extern const unsigned char menu_bar_s[3120];
 extern const unsigned char menu_bar_b[3520];
 
#endif

