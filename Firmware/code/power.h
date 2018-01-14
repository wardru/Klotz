#ifndef POWER_H
 #define POWER_H

 #define PWR_VOL 3190
 #define LUM_LVL(X) ((X < 1) ? 1 : ((X > 7) ? 7 : X))

 #define BAT_X   109
 #define BAT_Y   3

 extern const unsigned char battery[258];
 extern const unsigned char battery_R[26];
 extern const unsigned char battery_G[26];
 extern const unsigned char battery_O[26];

 extern unsigned char bat_state;

#endif