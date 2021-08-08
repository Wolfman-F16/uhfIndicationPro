/*
 * eepromdata.h
 *
 *  Created on: 22.04.2010
 *      Author: Wolfman
 */

#ifndef EEPROMDATA_S_
#define EEPROMDATA_S_

#define _A   (0x0020)
#define _B   (0x0400)
#define _C   (0x0002)
#define _D   (0x0010)
#define _E   (0x0800)
#define _F   (0x0001)
#define _G1  (0x8000)
#define _G2  (0x4000)
#define _H   (0x0008)
#define _J   (0x0004)
#define _K   (0x2000)
#define _L   (0x1000)
#define _M   (0x0100)
#define _N   (0x0200)
#define _Dp  (0x0040)

// Display requires the following letters
// ERASE, M-LOAD, FMT.CHG, VER/OP, REMOTE, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0
// 8 bits organized as follows: a, b, c, d, e, f, g, dp as specified in Kingbright datasheet for common cathode
// NOTE: bit order is reversed
.eseg
_EEPROM:
// channel
.db '1'
.db '2'
// frequency
.db '2'
.db '5'
.db '7'
.db '8'
.db '0'
.db '0'
// brightness day
.db 200
// brightness night
.db 20
// day/night
.db 0
// version
.db '0', '2'

.org 0x10
_FONT7_NUM:
// 0
.db  0b1110111
// 1
.db  0b0000110
// 2
.db  0b1011101
// 3
.db  0b1011110
// 4
.db  0b0101110
// 5
.db  0b1101010
// 6
.db  0b0111011
// 7
.db  0b1000110
// 8
.db  0b1111111
// 9
.db  0b1101110

.org 0x2D
_FONT_NUM:
// -
.dw  (_G1 | _G2)
// .
.dw  (_Dp)
// /
.dw  (_N | _K)
// 0
.dw  (_A | _B | _C | _D | _E | _F)
// 1
.dw  (_B | _C)
// 2
.dw  (_A | _B | _E | _D | _G1 | _G2)
// 3
.dw  (_A | _B | _C | _D | _G1 | _G2)
// 4
.dw  (_F | _G1 | _G2 | _B | _C)
// 5
.dw  (_A | _F | _G1 | _G2 | _C | _D)
// 6
.dw  (_F | _E | _D | _C | _G1 | _G2)
// 7
.dw  (_A | _B | _C)
// 8
.dw  (_A | _B | _C | _D | _E | _F | _G1 | _G2)
// 9
.dw  (_A | _B | _C | _F | _G1 | _G2)
// whitespace
.dw 0

_FONT_CHAR:
.org 0x41
// A
.dw  (_A | _B | _C | _E | _F | _G1 | _G2)
// B
.dw 0
// C
.dw  (_A | _D | _E | _F)
// D
.dw  (_A | _B | _C | _D | _J | _M)
// E
.dw  (_A | _D | _E | _F | _G1 | _G2)
// F
.dw  (_A | _E | _F | _G1 | _G2)
// G
.dw  (_A | _C | _D | _E | _F  | _G2)
// H
.dw  (_B | _C | _E | _F | _G1 | _G2)
// I
.dw (_J | _M)
// J
.dw 0
//K
.dw 0
// L
.dw  (_F | _E | _D)
// M
.dw  (_F | _E | _B | _C | _H | _K)
//N
.dw 0
// O
.dw  (_A | _B | _C | _D | _E | _F)
// P
.dw  (_A | _B | _J | _M | _G2)
//Q
.dw 0
// R
.dw  (_A | _B | _J | _M | _L | _G2)
// S
.dw  (_A | _H | _L | _D)
// T
.dw  (_A | _J | _M)
//U
.dw 0
// V
.dw  (_F | _E | _N | _K)

.cseg

#endif /* EEPROMDATA_S_ */
