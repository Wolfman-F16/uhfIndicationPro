/*
 * terminal.h
 *
 *  Created on: 06.06.2010
 *      Author: Wolfman
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_


// string arrays

// key definitions
#define KEY_ENTER       0x0D
#define KEY_LT_ARROW    0x1D
#define KEY_RT_ARROW    0x1C
#define KEY_BACKSPACE   0x7F


void printVersion();
void processUart(uint8_t rxValue);

#endif /* TERMINAL_H_ */
