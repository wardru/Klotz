#ifndef TIME_H
 #define TIME_H

 #define RDb RTCDATEbits
 #define RTb RTCTIMEbits
 #define Y_DATE 27
 #define Y_TIME 50
 #define Y_SEC  88

 
typedef struct  s_clock
{
    unsigned char YEAR10;
    unsigned char YEAR01;
    unsigned char MONTH10;
    unsigned char MONTH01;
    unsigned char DAY10;
    unsigned char DAY01;
    unsigned char WDAY01;

    unsigned char HR10;
    unsigned char HR01;
    unsigned char MIN10;
    unsigned char MIN01;
    signed char SEC01;
    unsigned char SEC10;
}               t_clock;

typedef struct  s_count
{
    unsigned char HR;
    unsigned char MIN;
    unsigned char SEC;
    signed int sum;
}               t_count;

typedef struct s_stop
{
    unsigned char HR;
    unsigned char MIN;
    unsigned char SEC;
    unsigned char run;
    signed int sum;
    unsigned short cnt;
}              t_stop;

 extern t_clock         clock;
 extern t_count         count;
 extern t_stop          stop;
 extern unsigned char   date_print;
 extern unsigned char   time_mode;
 extern unsigned char   time_set;
 extern unsigned char   count_trig;
 extern unsigned char   stop_trig;


#endif

