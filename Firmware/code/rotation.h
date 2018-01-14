#ifndef ROTATION_H
 #define ROTATION_H

 #define ROT_UP         0x68
 #define ROT_RIGHT      0x08
 #define ROT_DOWN       0xA8
 #define ROT_LEFT       0xC8
 #define ROT_INIT       ROT_DOWN

 #define ROT_CIRCLE_X   27
 #define ROT_CIRCLE_Y   27

 #define ROT_HOOK_X     ROT_CIRCLE_X + 22
 #define ROT_HOOK_Y     ROT_CIRCLE_Y + 23

 #define ROT_CROSS_X    ROT_CIRCLE_X + 27
 #define ROT_CROSS_Y    ROT_CIRCLE_Y + 27

 extern unsigned char rot_state;
 extern const unsigned char rot_circle[10952];
 extern const unsigned char check_G[1620];

#endif