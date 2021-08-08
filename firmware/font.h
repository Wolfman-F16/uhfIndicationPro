/*
 * font.h
 *
 *  Created on: 06.07.2021
 *      Author: Wolfman
 */

#ifndef FONT_H_
#define FONT_H_

#include <inttypes.h>

#define _A   (0x0020)
#define _B   (0x0400)
#define _C   (0x0002)
#define _D   (0x0010)
#define _E   (0x0800)
#define _F   (0x0001)
#define _G1  (0x8000)
#define _G2  (0x4000)
#define _H   (0x0008)
#define _I   (0x0004)
#define _K   (0x2000)
#define _L   (0x1000)
#define _M   (0x0100)
#define _N   (0x0200)
#define _Dp  (0x0040)


extern const uint8_t RADIO_INIT_DATA[];

extern const uint8_t FONT7_NUM[];
extern const uint16_t FONT_NUM[];
extern const uint16_t FONT_CHAR[];

#endif /* FONT_H_ */
