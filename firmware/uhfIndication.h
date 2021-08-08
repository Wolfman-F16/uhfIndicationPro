/*
 * UHFIndication.h
 *
 *  Created on: 30.01.2010
 *      Author: Wolfman
 */

#ifndef UHFINDICATION_H_
#define UHFINDICATION_H_

#include "adc.h"
#include "spi.h"

#include <avr/io.h>
#include <stdint.h>

#define _DEBUG_ 0

#ifndef EEMEM
#define EEMEM  __attribute__ ((section (".eeprom")))
#endif

#define BEGIN_INFINITE_LOOP for(;;) {
#define END_INFINITE_LOOP   }

#define TRUE            1
#define FALSE           0

/*----------------------------------------------------------------------------*/
// I/O
/*----------------------------------------------------------------------------*/
#define PORT_OUT_SHFT   PORTD

#define PIN_SHFT_RCK    PORTD4
#define PIN_SHFT_DAT    PORTD7
#define PIN_SHFT_SCK    PORTD5
#define PIN_SHFT_CLR    PORTD6

#define PORT_OUT_MUX_ENA    PORTB
#define PIN_MUX_ENA         PORTB0

#define PORT_OUT_MUX    PORTC
#define PIN_MUX_ADDR0   PORTC0
#define PIN_MUX_ADDR1   PORTC1
#define PIN_MUX_ADDR2   PORTC2
#define PORT_MUX_MASK   0x07


#define PORT_LED        PORTD
#define PIN_STATUS_LED  PORTD3

#define PORT_OUT_PWM    PORTB
#define PIN_PWM         PORTB1

#define PIN_TRIGGER     PORTD2

#define PIN_SPI_CLK     PORTB5
#define PIN_SPI_MISO    PORTB4
#define PIN_SPI_MOSI    PORTB3
#define PIN_SPI_SS      PORTB2
#define PIN_RX          PORTD0
#define PIN_TX          PORTD1

/*----------------------------------------------------------------------------*/
// UHF
/*----------------------------------------------------------------------------*/
// reserve mem for partial ASCII table
#define MAX_BYTE        0x5A
#define CHANNEL_LENGTH  2
#define FREQ_LENGTH     6
#define BYTE_LENGTH     8

#define CHANNEL_OFFSET  7
/* 7 seg displays*/
#define BLANK_DIGIT     0xFF
#define TEST_DIGIT      ~0x7F
#define DECIMAL_POINT   0x80
/* 14 seg displays */
#define BLANK16_DIGIT   0xFFFF
#define TEST16_DIGIT    0x0040
#define DECIMAL16_POINT 0x0040

/*----------------------------------------------------------------------------*/
// UART
/*----------------------------------------------------------------------------*/
// parser
#define NEWLINE         '\r'
#define NEWPAGE         0x0C
#define BACKSPACE       0x7F
#define TERMINATOR      0x00

#define MAX_BUFFER_SIZE 20
#define MAX_MSG_LENGTH  25
#define MAX_MESSAGES    9
#define MAX_COMMANDS    5
// error codes for TTYFlag (number specifies bit)
#define ERROR_OK        0
#define ERROR_BUFFER    1
#define ERROR_CMD       2
#define ERROR_PARAM     3
// commands
#define CMD_B           1
#define CMD_C           2
#define CMD_D           3
#define CMD_F           4
#define CMD_INFO        5

/*----------------------------------------------------------------------------*/
// SPI
/*----------------------------------------------------------------------------*/
//indicates start of frame
#define MSG_TYPE        0x1A
// for channel & frequency for starters.
#define MAX_SPI_BUFFER  8

/*----------------------------------------------------------------------------*/
// SW Timer
/*----------------------------------------------------------------------------*/
#define SWT_ADC_ISR     0
#define SWT_TEST_ISR    1
#define SWT_CHARLIE_ISR 2

/****************************   Structures      *******************************/
typedef struct {
  uint8_t channelString[CHANNEL_LENGTH];
  uint8_t frequencyString[FREQ_LENGTH];
  uint8_t brightnessDay;
  uint8_t brightnessNight;
  uint8_t day;
  uint8_t version;
} radio_t;


typedef struct {
  unsigned boot:1;
  unsigned updateAdc:1;
  unsigned updateTimer:1;
  unsigned updateDisplay:1;
  unsigned currFrequency:3;
  unsigned currChannel:1;
} status_t;

/****************************   Variables       *******************************/
volatile radio_t radio;
volatile status_t status;
volatile uint8_t currentAdcValue;

extern uint8_t asciiTable[128];
extern uint8_t table[] EEMEM;

extern volatile uint8_t swTimer[3];

/****************************   FUNCTION DECLARATIONS ************************/
void initIO(void);
void setDefaults(void);

void updateDisplay(void);

void setLightTestOn(void);
void setLightTestOff(void);
void setLightBlank(void);

/****************************   INLINE FUNCTIONS    **************************/
/*
 * sets status led off
 */
static inline void setStatusLedOff()
{
  PORT_LED |= _BV(PIN_STATUS_LED);
}

/*
 * sets status led on
 */
static inline void setStatusLedOn()
{
  PORT_LED &= ~_BV(PIN_STATUS_LED);
}

/*
 * set charlie plexing address
 */
static inline void charlieplex(uint8_t index)
{
  PORTC &= ~PORT_MUX_MASK;
  PORTC |= index & PORT_MUX_MASK;
}

/**************************** Interrupt Service Routine     ******************/
/**
 * interrupt service routine
 *
 * Display test
 */
static inline void isrTestTimer()
{
  static uint8_t timer0Ext = 0x2F;

  if(timer0Ext > 0) {
    timer0Ext--;
  } else {
    // notify main loop
    status.updateTimer = TRUE;
  }
}

/**
 * interrupt service routine
 *
 * ADC conversion
 */
static inline void isrAdc()
{
  startAdcConversion();
}

/**
 * interrupt service routine
 *
 * charlie plexing
 */
static inline void isrCharlieplex()
{
  if (swTimer[SWT_CHARLIE_ISR] == 0) {
    swTimer[SWT_CHARLIE_ISR] = 8;
    charlieplex(CHANNEL_OFFSET - status.currChannel);
    status.currChannel++;
    if (status.currChannel >= CHANNEL_LENGTH) {
      status.currChannel = 0;
    }
  } else {
    swTimer[SWT_CHARLIE_ISR]--;
    charlieplex(status.currFrequency);
    status.currFrequency++;
    if (status.currFrequency >= FREQ_LENGTH) {
      status.currFrequency = 0;
    }
  }
  status.updateDisplay = 1;
}



/**/
/**
 * interrupt service routine
 *
 * SPI communication
 */
static inline void isrSpi(void)
{
  static uint8_t radioIndex = 0;
  uint8_t *radioArray = (uint8_t*)& radio;

  spiRxValue = SPDR;
  /* debug */
  UDR = spiRxValue;
  /* debug */
  if(spiRxValue == SPI_SOF) {
    radioIndex = 0;
    setStatusLedOn();
    return;
  }
  if(radioIndex < (CHANNEL_LENGTH + FREQ_LENGTH)) {
    if(spiRxValue == ' ') {
      spiRxValue = 'X';  // whitespace conversion
    }
    radioArray[radioIndex++] = spiRxValue;
  }
}
#endif /* UHFINDICATION_H_ */
