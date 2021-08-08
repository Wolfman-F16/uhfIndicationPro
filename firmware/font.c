/*
 * font.c
 *
 *  Created on: Jul 6, 2021
 *      Author: wolfgang
 */

#include "font.h"

// Display requires the following letters
// ERASE, M-LOAD, FMT.CHG, VER/OP, REMOTE, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0

const uint8_t RADIO_INIT_DATA[] = {
// channel
 '1', '2',
 // frequency
 '2' , '5', '7', '8', '0', '0',
// brightness day
 22,
// brightness night
 123,
// day/night
 0,
// version
 2
};

const uint8_t FONT7_NUM[] = {
// 0
 0b1110111,
// 1
 0b0000110,
// 2
 0b1011101,
// 3
 0b1011110,
// 4
 0b0101110,
// 5
 0b1111010,
// 6
 0b0111011,
// 7
 0b1000110,
// 8
 0b1111111,
// 9
 0b1101110
};

const uint16_t FONT_NUM[] = {
// -
 (_G1 | _G2),
// .
 (_Dp),
// /
 (_N | _K),
// 0
 (_A | _B | _C | _D | _E | _F | _K | _N),
// 1
 (_B | _C),
// 2
 (_A | _B | _D | _N | _G2),
// 3
 (_A | _B | _C | _D | _G2),
// 4
 (_F | _G1 | _G2 | _B | _C),
// 5
 (_A | _F | _G1 | _L | _D),
// 6
 (_F | _E | _D | _C | _G1 | _G2),
// 7
 (_A | _B | _C),
// 8
 (_A | _B | _C | _D | _E | _F | _G1 | _G2),
// 9
 (_A | _B | _C | _F | _G1 | _G2),
};

const uint16_t FONT_CHAR[] = {
// A
 (_A | _B | _C | _E | _F | _G1 | _G2),
// B
 (_A | _B | _C | _D | _I | _G2 | _M),
// C
 (_A | _D | _E | _F),
// D
 (_A | _B | _C | _D | _I | _M),
// E
 (_A | _D | _E | _F | _G1),
// F
 (_A | _E | _F | _G1),
// G
 (_A | _C | _D | _E | _F  | _G2),
// H
 (_B | _C | _E | _F | _G1 | _G2),
// I
 (_A | _I | _M | _D),
// J
 0,
//K
 (_E | _F | _K | _L | _G1),
// L
 (_F | _E | _D),
// M
 (_F | _E | _B | _C | _H | _K),
//N
 (_F | _E | _B | _C | _H | _L),
// O
 (_A | _B | _C | _D | _E | _F),
// P
 (_A | _B | _I | _M | _G2),
//Q
 0,
// R
 (_A | _B | _F | _E | _L | _G1 | _G2),
// S
 (_A | _F | _G1 | _G2 | _C | _D),
// T
 (_A | _I | _M),
//U
 0,
// V
 (_F | _E | _N | _K),
// W
 (_B | _C| _L | _N | _E | _F),
 // whitespace
   0,
};
