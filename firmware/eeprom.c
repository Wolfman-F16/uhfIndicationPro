/*
 * eeprom.c
 *
 *  Created on: Jul 5, 2021
 *      Author: wolfgang
 */
#if 0
#include <avr/eeprom.h>
#include "font.h"

#define VERSION_IDX     (uint8_t*)12

void checkEeprom()
{
  uint8_t value;

  value = eeprom_read_byte(VERSION_IDX);

  if (value != 2) {
    /* store radio data into eeprom */
    eeprom_write_block(RADIO_INIT_DATA, 0, sizeof(RADIO_INIT_DATA));

    /* store 7 seg number data into eeprom */
    eeprom_write_block(FONT7_NUM, (uint8_t*)0x10, 10);

    /* store 14 seg numeric data into eeprom */
    eeprom_write_block(FONT_NUM, (uint8_t*)0x2D, 10);

    /* store 14 seg alpha data into eeprom */
    eeprom_write_block(FONT_CHAR, (uint8_t*)0x41, 10);

  }
}
#endif
