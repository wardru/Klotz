#ifndef GYRO_H
 #define GYRO_H

 #include "mode.h"

 #define CALI_CYC        1000 // Nb. of cycles to calibrate MPU6050
 #define ROT_DIV         80 // Gyro output DIVIDER;  32.75 deg/s * 25 Hz / 10

typedef struct  s_gyr
{
    signed short rot_x;
    signed short rot_y;
    signed short rot_z;
    signed int rot_x_cali;
    signed int rot_y_cali;
    signed int rot_z_cali;

    signed short acc_x;
    signed short acc_y;
    signed short acc_z;
    signed int acc_x_cali;
    signed int acc_y_cali;
    signed int acc_z_cali;

    signed short rot[GYRO_SIZE];
    signed short acc[GYRO_SIZE];

    signed short temp[TEMP_SIZE];
    unsigned char df;
    signed int sum;
    unsigned short div;
}               t_gyr;

typedef struct s_rot
{
    unsigned char  x;
    unsigned char  y;
}              t_rot;

 extern t_gyr gyr;
 extern t_rot shift;
 extern unsigned char gyro_mode;
 extern unsigned char gyro_trig;
 extern unsigned char temp_trig;
 extern unsigned char temp_mode;


#endif