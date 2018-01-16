/*
 *  This .h file gives a fast and easy access to the configuration of the pins.
 */

#ifndef PINS_H
 #define PINS_H

 #define I0b        IFS0bits
 #define I2Cb       I2C1CONbits

 #define TAb        TRISAbits
 #define TBb        TRISBbits
 #define LAb        LATAbits
 #define LBb        LATBbits
 #define PAb        PORTAbits
 #define PBb        PORTBbits

 #define T_CMP      TAb.TRISA0
 #define L_CMP      LAb.LATA0
 #define P_CMP      PAb.PORTA0

 #define T_LS0      TBb.TRISB3                       // peripheric devices
 #define L_LS0      LBb.LATB3
 #define P_LS0      PBb.PORTB3
 #define T_LS1      TAb.TRISA1                       // screen back_light
 #define L_LS1      LAb.LATA1
 #define P_LS1      PAb.PORTA1

 #define T_BUZ      TBb.TRISB2
 #define L_BUZ      LBb.LATB2
 #define P_BUZ      PBb.PORTB2

 #define T_BUT0     TBb.TRISB5
 #define L_BUT0     LBb.LATB5
 #define P_BUT0     PBb.RB5
 #define T_BUT1     TBb.TRISB6
 #define L_BUT1     LBb.LATB6
 #define P_BUT1     PBb.RB6

 #define T_IND      TBb.TRISB15
 #define L_IND      TBb.LATB15
 #define P_IND      TBb.PORTB15

 #define T_SCLK     TBb.TRISB14
 #define L_SCLK     LBb.LATB14
 #define P_SCLK     LBb.PORTB14

 #define T_SPI      TBb.TRISB13
 #define L_SPI      LBb.LATB13
 #define P_SPI      LBb.PORTB13

 #define T_TEMP     TBb.TRISB12
 #define L_TEMP     LBb.LATB12
 #define P_TEMP     PBb.PORTB12

 #define T_CS       TBb.TRISB11
 #define L_CS       LBb.LATB11
 #define P_CS       PBb.PORTB11

 #define T_RESET    TBb.TRISB10
 #define L_RESET    LBb.LATB10
 #define P_RESET    PBb.PORTB10

 #define T_SDA      TBb.TRISB9
 #define L_SDA      LBb.LATB9
 #define P_SDA      PBb.PORTB9

 #define T_SCL      TBb.TRISB8
 #define L_SCL      LBb.LATB8
 #define P_SCL      PBb.PORTB8

 #define T_RS       TBb.TRISB7
 #define L_RS       LBb.LATB7
 #define P_RS       PBb.PORTB7

#endif