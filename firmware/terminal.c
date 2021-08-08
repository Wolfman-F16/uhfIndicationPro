/*
 * terminal.c
 *
 *  Created on: Jul 4, 2021
 *      Author: wolfgang
 */
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "terminal.h"
#include "serial.h"
#include "uhfIndication.h"
#include "shift.h"



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

/* ------------------------------------------------------------------------- */
const uint8_t sVersion[] PROGMEM = "UHF Indication Pro Board SW version \0";
const uint8_t sOCR1A[] PROGMEM = "OCR1A\r\n\0";
const uint8_t sVoltage[] PROGMEM = "\r\nVoltage \0";

#define RX_BUFFER_SIZE      16

static uint8_t rxBuffer[RX_BUFFER_SIZE];
// serial terminal
static uint8_t rxIndex = 0;
static uint16_t pwmVal = 0;

static void printVoltage(void);

void processUart(uint8_t rxValue)
{
      switch (rxValue) {
      case KEY_ENTER:
        //process buffer content
        if (rxIndex <= CHANNEL_LENGTH) {
          for (uint8_t i = 0; i < CHANNEL_LENGTH; i++) {
            radio.channelString[i] = rxBuffer[i];
          }
        } else {
          for (uint8_t i = 0; i < FREQ_LENGTH; i++) {
            radio.frequencyString[i] = rxBuffer[i];
          }
        }
        rxIndex = 0;
        sendUartNewline();
        break;
      case KEY_BACKSPACE:
        // buffer index-- , check boundary
        rxBuffer[rxIndex] = 0;
        // intentional fall-through
      case KEY_LT_ARROW:
        // buffer index-- , check boundary
        if (rxIndex > 0)
          rxIndex--;
        break;
      case KEY_RT_ARROW:
        // buffer index++ , check boundary
        if (rxIndex < RX_BUFFER_SIZE)
          rxIndex++;
        break;
      case 'd':
        radio.day = TRUE;
        break;
      case 'n':
        radio.day = FALSE;
        break;
      case 'q':
        sendUartString_P((uint8_t*) sVersion);
        sendUartBits(radio.version);
        if (radio.day == TRUE) {
          sendUartByte('D');
        } else {
          sendUartByte('N');
        }
        sendUartNewline();
        sendUartString_P((uint8_t*) sOCR1A);
        sendUartBits(OCR1AH);
        sendUartBits(OCR1AL);
        // break intentionally left out
      case 'p':
        sendUartByte('B');
        sendUartBits(PINB);
        break;
      case 'u':
        acceptByte();
        break;
      case 'c':
        sendUartNewline();
        sendUartByte(radio.channelString[0]);
        sendUartByte(radio.channelString[1]);
        break;
      case 'f':
        sendUartNewline();
        sendUartByte(radio.frequencyString[0]);
        sendUartByte(radio.frequencyString[1]);
        sendUartByte(radio.frequencyString[2]);
        sendUartByte('.');
        sendUartByte(radio.frequencyString[3]);
        sendUartByte(radio.frequencyString[4]);
        sendUartByte(radio.frequencyString[5]);
        break;
      case ']':
        pwmVal += 10;
        OCR1A = pwmVal;
        break;
      case '[':
        pwmVal -= 10;
        OCR1A = pwmVal;
        break;
      case 'v':
        printVoltage();
        break;
      default:
        if (rxIndex > RX_BUFFER_SIZE - 1) {
          // error buffer overflow
        } else {
          if (rxValue == ' ') { /* convert whitespace */
            rxValue = 'X';
          }
          rxBuffer[rxIndex++] = rxValue;
        }
        break;
      }
}

/**/
void printVersion()
{
  sendUartString_P((uint8_t*)sVersion);
}

static void printVoltage()
{
  uint16_t value;
  uint8_t volt;
  uint8_t millivolt;

  sendUartString_P((uint8_t*) sVoltage);

  value = ADCH * 50 / 255;

  volt = (uint8_t)value /10;
  millivolt = (value - volt*10);


  sendUartByte(volt + '0');
  sendUartByte('.');
  sendUartByte((millivolt) + '0');
  sendUartNewline();
  sendUartBits(ADCH);
}

