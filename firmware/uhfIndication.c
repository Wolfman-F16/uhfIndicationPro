/*
 * UhfIndication.c
 *
 *  Created on: 30.01.2010
 *      Author: Wolfman
 */
#include <avr/eeprom.h>
#include "uhfIndication.h"
#include "shift.h"
#include "serial.h"
#include "font.h"

uint8_t asciiTable[128];
uint8_t table[512] EEMEM;
volatile uint8_t swTimer[3];

/*
 * sets light test on
 */
void setLightTestOn()
{
  uint8_t i = 0;

  radio.channelString[i++] = '8';
  radio.channelString[i++] = '8';
  i = 0;
  radio.frequencyString[i++] = '8';
  radio.frequencyString[i++] = '8';
  radio.frequencyString[i++] = '8';
  radio.frequencyString[i++] = '8';
  radio.frequencyString[i++] = '8';
  radio.frequencyString[i++] = '8';
}

/*
 * disables light test
 */
void setLightTestOff()
{
  uint8_t i = 0;

  radio.channelString[i++] = '1';
  radio.channelString[i++] = '4';
  i = 0;
  radio.frequencyString[i++] = '3';
  radio.frequencyString[i++] = '6';
  radio.frequencyString[i++] = '7';
  radio.frequencyString[i++] = '8';
  radio.frequencyString[i++] = '2';
  radio.frequencyString[i++] = '5';
}

/**
 *
 */
void setLightBlank(void)
{
  PORT_OUT_SHFT &= ~_BV(PIN_SHFT_CLR);
  PORT_OUT_SHFT |= _BV(PIN_SHFT_CLR);

  uint8_t i = 0;

  radio.channelString[i++] = ' ';
  radio.channelString[i++] = ' ';
  i = 0;
  radio.frequencyString[i++] = 'X';
  radio.frequencyString[i++] = 'X';
  radio.frequencyString[i++] = '.';
  radio.frequencyString[i++] = 'X';
  radio.frequencyString[i++] = 'X';
  radio.frequencyString[i++] = 'X';
}

/*
 * updates displays
 */
void updateDisplay()
{
  uint8_t value;
  uint16_t digitpattern;

  acceptByte();
  value = radio.frequencyString[status.currFrequency];
  if (value > '9') {
    loadFreqByte(FONT_CHAR[value - 'A']);
  } else {
    if (status.currFrequency == 2) {
      digitpattern = FONT_NUM[value - '-'] | _Dp;
    } else {
      digitpattern = FONT_NUM[value - '-'];
    }
    loadFreqByte(digitpattern);
  }
  loadChanByte(FONT7_NUM[radio.channelString[status.currChannel] - '0']);
}
