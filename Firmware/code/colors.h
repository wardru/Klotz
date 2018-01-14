#ifndef COLORS_H
 #define COLOR_H

 #define MSB_BK BK_CLR >> 8
 #define LSB_BK BK_CLR & 0xFF
// #define MSB_BK 0x00
// #define LSB_BK 0x00

// #define BK_CLR  0x7A20        // Brown
// #define BK_CLR  0x18E3        // Beauty
// #define BK_CLR  0x0007
 #define BK_CLR  0x0000        // BLACK
// #define BK_CLR  0x1800

// #define BLA_CLR  0xFFFF     // blank COLOR
 #define BLA_CLR  BK_CLR

#endif