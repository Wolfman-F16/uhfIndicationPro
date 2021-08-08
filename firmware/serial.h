/*
 * serial.h
 *
 *  Created on: 04.10.2009
 *      Author: Wolfman
 */

#ifndef SERIAL_H_
#define SERIAL_H_

/****************************   Structures      *******************************/
typedef struct {
  unsigned rx:1;


} serialStatus_t;

typedef union {
  uint16_t i16;
  struct {
    uint8_t i8l;
    uint8_t i8h;
  };
} UINT16_T;

/****************************   GLOBAL VARIABLES    **************************/
extern volatile uint8_t         rxValue;
extern volatile serialStatus_t  serialStatus;

/****************************   FUNCTION DECLARATIONS ************************/
void initSerial(void);
void sendUartByte(uint8_t );
void sendUartBits(uint8_t );
void sendUartString_P(uint8_t*);
void sendUartString_n(uint8_t *, uint8_t );
void sendUartNewline(void);
int checkBaudError(void);

#endif /* SERIAL_H_ */
