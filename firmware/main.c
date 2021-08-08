/* Name: main.c
 * Project: UHFIndicationPro
 * Author: Wolfgang Engelhard
 *
 *  License: GPL v2
 */
#ifndef F_CPU
#error F_CPU not defined
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

#include "uhfIndication.h"
#include "adc.h"
#include "serial.h"
#include "terminal.h"
#include "spi.h"
#include "timer.h"
#include "shift.h"
#include "font.h"

extern void checkEeprom(void);

/* ------------------------------------------------------------------------- */
int main(void) {
  uint8_t i = 0;
  uint8_t isCBconnected = FALSE;
  // display voltage monitoring
  uint16_t adcValue = 0;

  status.boot = 1;

  // init IO
  initIO();
  if (!(PINB & (1 << PIN_SPI_SS))) {// if SS still high and not pulled down by control board...
    isCBconnected = 0x01;
  }

 // checkEeprom();

  // init ADC
  initAdc();
  if (!(PINB & (1 << PIN_SPI_SS))) {// if SS still high and not pulled down by control board...
    isCBconnected |= 0x02;
  }
  // dummy read first ADC value
  startAdcConversion();
  wait4Adc2Complete();
  adcValue = ADCW;
  // init SPI
  initSpi();
  // enable interrupts
  sei();
  // init UART
  initSerial();
  sendUartByte(NEWPAGE);

  if (!(PINB & (1 << PIN_SPI_SS))) {// if SS still high and not pulled down by control board...
    isCBconnected |= 0x04;
  }
  // init Timer
  initTimer();
  if (!(PINB & (1 << PIN_SPI_SS))) {// if SS still high and not pulled down by control board...
    isCBconnected |= 0x08;
  }
  setDefaults();

  if (isCBconnected > 0) {// if SS still high and not pulled down by control board...
    setLightBlank();
  } else {
    setLightTestOn();           // start display up with led test
    updateDisplay();                  /* this now loads test into shift registers */
    acceptByte();                     /* this shows shift data to outputs */
  }
  enableTimer2();                   /* this charlie plexes the digits */

  // init complete

  uint8_t *radioArray = (uint8_t*) &radio;
#if EEPROM_DATA_AVAIL > 0
  // load eeprom values to sram
  for (i = 0; i < 128; i++) {
    asciiTable[i] = eeprom_read_byte(table + i);
  }
  // write radio variable using sram data
  for (i = 0; i < sizeof(radio_t); i++) {
    radioArray[i] = asciiTable[i];
  }
#else
  for (i = 0; i < sizeof(radio_t); i++) {
    radioArray[i] = RADIO_INIT_DATA[i];
  }
#endif
  if (radio.day == TRUE) {
    OCR1A = radio.brightnessDay << 2;
  } else {
    OCR1A = radio.brightnessNight << 2;
  }
  printVersion();
  sendUartBits(radio.version);    // debug
  // wait till init phase is complete ~1 sec.
  if (isCBconnected == FALSE) {
    while (status.updateTimer != TRUE)
      asm("nop");

    setLightTestOff();          // stop display test
    sendUartByte('_');
  } else {
    sendUartByte('~');
    sendUartBits(isCBconnected);
  }
  status.boot = 0;
  status.updateDisplay = 1;
  sendUartByte('\n');
  /****************************** main event loop ****************************/
  BEGIN_INFINITE_LOOP
    if (status.updateDisplay) {
      status.updateDisplay = 0;
      if (isCBconnected > 0) {
        setStatusLedOff(); /* only turn off LED when control board is connected */
      }
      updateDisplay();
    }

    // serial terminal
    if (serialStatus.rx) {
      serialStatus.rx = FALSE;
      processUart(rxValue);
    }

    // voltage monitoring
    if (status.updateAdc) {
      status.updateAdc = FALSE;

      adcValue = currentAdcValue;
    }
  END_INFINITE_LOOP

  return 0;
}

