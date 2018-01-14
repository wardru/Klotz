#include "klotz.h"

unsigned short  blink_trig;
unsigned short  blink_time;

const unsigned char menu_lang_str[LANG_SIZE][9] =
{
    "Francais", "English", "Deutsch"
};

const unsigned char mode_gyro_str[LANG_SIZE][6] =
{
    "axe", "axis", "Achse"
};

const unsigned char mode_temp_str[LANG_SIZE][18] =
{
    "moyenne jour.", "daily average", "Tagesdurchschnitt"
};

size_t ft_strlen(const u8 *s)
{
    const u8 *tmp;
    
    tmp = s;
    while (*tmp)
        tmp++;
    return (tmp - s);
}

void    blank(const u8 x, const u8 y, const u8 nb, const u8 big)
{
    if (nb)
        print_LCD_window(x + big * 2, y + !big, (nb * (X_STA + big * 20)) - big * 4, Y_STA + (big * 20) - !big, BLA_CLR);
}

const unsigned char *mode_menu_str[MENU_SIZE][LANG_SIZE];
const unsigned char *mode_game_str[2][LANG_SIZE];
const unsigned char *menu_game_str[GAME_SIZE][LANG_SIZE];
const unsigned char *alarm_str[ALARM_SIZE][LANG_SIZE];
const unsigned char *time_wday_str[7][LANG_SIZE];
const unsigned char *time_mode_str[TIME_SIZE - 1][LANG_SIZE];

void    init_strings(void)
{
    mode_menu_str[MENU_LUM][LANG_FR] = "Luminosite";
    mode_menu_str[MENU_LUM][LANG_EN] = "Brightness";
    mode_menu_str[MENU_LUM][LANG_DE] = "Helligkeit";
    
    mode_menu_str[MENU_BUZ][LANG_FR] = "Son";
    mode_menu_str[MENU_BUZ][LANG_EN] = "Sound";
    mode_menu_str[MENU_BUZ][LANG_DE] = "Ton";
    
    mode_menu_str[MENU_LANG][LANG_FR] = "Langage";
    mode_menu_str[MENU_LANG][LANG_EN] = "Language";
    mode_menu_str[MENU_LANG][LANG_DE] = "Sprache";
    
    mode_menu_str[MENU_ROT][LANG_FR] = "Rotation";
    mode_menu_str[MENU_ROT][LANG_EN] = "Rotation";
    mode_menu_str[MENU_ROT][LANG_DE] = "Rotation";
    
    mode_menu_str[MENU_ABOUT][LANG_FR] = "A propos";
    mode_menu_str[MENU_ABOUT][LANG_EN] = "About";
    mode_menu_str[MENU_ABOUT][LANG_DE] = "Info";
    
    mode_menu_str[MENU_TIME][LANG_FR] = "Heure";
    mode_menu_str[MENU_TIME][LANG_EN] = "Time";
    mode_menu_str[MENU_TIME][LANG_DE] = "Uhrzeit";
    
    mode_menu_str[MENU_GAME][LANG_FR] = "Jeu";
    mode_menu_str[MENU_GAME][LANG_EN] = "Game";
    mode_menu_str[MENU_GAME][LANG_DE] = "Spiel";
    
    mode_menu_str[MENU_ALARM][LANG_FR] = "Alarme";   
    mode_menu_str[MENU_ALARM][LANG_EN] = "Alarm";
    mode_menu_str[MENU_ALARM][LANG_DE] = "Alarm";
    
    mode_menu_str[MENU_INV][LANG_FR] = "Inver coul";   
    mode_menu_str[MENU_INV][LANG_EN] = "Invert col";
    mode_menu_str[MENU_INV][LANG_DE] = "Farb umkeh";
    
    menu_game_str[GAME_5S][LANG_FR] = "faci 5s ";
    menu_game_str[GAME_5S][LANG_EN] = "easy 5s ";
    menu_game_str[GAME_5S][LANG_DE] = "leic 5s ";
    
    menu_game_str[GAME_10S][LANG_FR] = "medi 10s";
    menu_game_str[GAME_10S][LANG_EN] = "medi 10s";
    menu_game_str[GAME_10S][LANG_DE] = "mitt 10s";
    
    menu_game_str[GAME_15S][LANG_FR] = "diff 15s";
    menu_game_str[GAME_15S][LANG_EN] = "hard 15s";
    menu_game_str[GAME_15S][LANG_DE] = "hart 15s";
    
    menu_game_str[GAME_20S][LANG_FR] = "pro 20s";
    menu_game_str[GAME_20S][LANG_EN] = "pro 20s";
    menu_game_str[GAME_20S][LANG_DE] = "pro 20s";
    
    alarm_str[ALARM_OFF][LANG_FR] = "desactive";
    alarm_str[ALARM_OFF][LANG_EN] = "disabled";
    alarm_str[ALARM_OFF][LANG_DE] = "inaktiv";

    alarm_str[ALARM_1][LANG_FR] = "1 fois";
    alarm_str[ALARM_1][LANG_EN] = "1 time";
    alarm_str[ALARM_1][LANG_DE] = "1 Mal";

    alarm_str[ALARM_2][LANG_FR] = "3 fois";
    alarm_str[ALARM_2][LANG_EN] = "3 times";
    alarm_str[ALARM_2][LANG_DE] = "3 Mal";

    alarm_str[ALARM_3][LANG_FR] = "5 fois";
    alarm_str[ALARM_3][LANG_EN] = "5 times";
    alarm_str[ALARM_3][LANG_DE] = "5 Mal";
    
    time_wday_str[0][LANG_FR] = "DIM";
    time_wday_str[0][LANG_EN] = "SUN";
    time_wday_str[0][LANG_DE] = "SO";

    time_wday_str[1][LANG_FR] = "LUN";
    time_wday_str[1][LANG_EN] = "MON";
    time_wday_str[1][LANG_DE] = "MO";

    time_wday_str[2][LANG_FR] = "MAR";
    time_wday_str[2][LANG_EN] = "TUE";
    time_wday_str[2][LANG_DE] = "DI";

    time_wday_str[3][LANG_FR] = "MER";
    time_wday_str[3][LANG_EN] = "WED";
    time_wday_str[3][LANG_DE] = "MI";
    
    time_wday_str[4][LANG_FR] = "JEU";
    time_wday_str[4][LANG_EN] = "THU";
    time_wday_str[4][LANG_DE] = "DO";

    time_wday_str[5][LANG_FR] = "WEN";
    time_wday_str[5][LANG_EN] = "FRI";
    time_wday_str[5][LANG_DE] = "FR";

    time_wday_str[6][LANG_FR] = "SAM";
    time_wday_str[6][LANG_EN] = "SAT";
    time_wday_str[6][LANG_DE] = "SA";

    time_mode_str[TIME_COUNT - 1][LANG_FR] = "Minuterie";
    time_mode_str[TIME_COUNT - 1][LANG_EN] = "Timer";
    time_mode_str[TIME_COUNT - 1][LANG_DE] = "Zeituhr";

    time_mode_str[TIME_STOP - 1][LANG_FR] = "Chronometre";
    time_mode_str[TIME_STOP - 1][LANG_EN] = "Stop watch";
    time_mode_str[TIME_STOP - 1][LANG_DE] = "Stoppuhr";

    mode_game_str[0][LANG_FR] = "SCORE";
    mode_game_str[0][LANG_EN] = "SCORE";
    mode_game_str[0][LANG_DE] = "PUNKTZAHL";

    mode_game_str[1][LANG_FR] = "FINI";
    mode_game_str[1][LANG_EN] = "OVER";
    mode_game_str[1][LANG_DE] = "FERTIG";
}