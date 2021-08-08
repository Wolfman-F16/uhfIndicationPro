/*
 * shift.c
 *
 *  Created on: 30.01.2010
 *      Author: Wolfman
 */
#include "uhfIndication.h"
#include "shift.h"

/*
 * latches data in shift register to its outputs
 */
void acceptByte()
{
  PORT_OUT_SHFT |= (1 << PIN_SHFT_RCK);
  PORT_OUT_SHFT &= ~(1 << PIN_SHFT_RCK);
}

/*
 * loads byte to shift register
 */
void loadFreqByte(uint16_t word)
{
  int i = 0;

  for(i = 0; i < (BYTE_LENGTH * 2); i++) {
    if (word & 0x8000) {
      PORT_OUT_SHFT |= _BV(PIN_SHFT_DAT);
    } else {
      PORT_OUT_SHFT &= ~_BV(PIN_SHFT_DAT);
    }
    PORT_OUT_SHFT |= _BV(PIN_SHFT_SCK);
    word = word << 1;
    PORT_OUT_SHFT &= ~_BV(PIN_SHFT_SCK);
  }
}

/*
 * loads byte to shift register
 */
void loadChanByte(uint8_t byte)
{
  int i = 0;

  for(i = 0; i < BYTE_LENGTH; i++) {
    if (byte & 0x80) {
      PORT_OUT_SHFT |= _BV(PIN_SHFT_DAT);
    } else {
      PORT_OUT_SHFT &= ~_BV(PIN_SHFT_DAT);
    }
    PORT_OUT_SHFT |= _BV(PIN_SHFT_SCK);
    byte = byte << 1;
    PORT_OUT_SHFT &= ~_BV(PIN_SHFT_SCK);
  }
}
