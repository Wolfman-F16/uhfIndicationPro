/*
 * init.c
 *
 *  Created on: 02.07.2021
 *      Author: Wolfman
 *  Information:
 *    Serial:
 *      INPUT Ports: D0
 *      OUTPUT Ports: D1
 *    Status:
 *      OUTPUT Ports: D3
 *    PWM:
 *      OUTPUT Ports B1
 *    SPI:
 *      INPUT Ports: B2, B3, B5
 *      OUTPUT Ports: B4
 *    SHIFT Register:
 *      OUTPUT Ports: C0, C1, C2, D4, D5, D6, D7
 *    Power Supply monitoring:
 *      Input Ports: C3
 *    I2C:
 *      Ports: C4, C5,
 */
#include "uhfIndication.h"
#include "spi.h"
#include <avr/io.h>

/*
 * init i/o
 *
 * pull up resistors on: set DDRn low and PORTn high
 */
void initIO()
{
  // PWM, MUX and SPI
  DDRB = _BV(PIN_MUX_ENA) | _BV(PIN_PWM) | _BV(PIN_SPI_MISO);
  // Charlieplexing (MUX) addressing; I2C not implemented atm.
  DDRC = _BV(PIN_MUX_ADDR0) | _BV(PIN_MUX_ADDR1) | _BV(PIN_MUX_ADDR2);
  // UART, Status LED, shift register
  DDRD = _BV(PIN_TX) | _BV(PIN_STATUS_LED) | _BV(PIN_SHFT_RCK) | _BV(PIN_SHFT_SCK) \
      | _BV(PIN_SHFT_CLR) | _BV(PIN_SHFT_DAT);
}

void setDefaults()
{
  // spiRxValue
  spiRxValue = 0;
  // adc
  currentAdcValue = 0;

  // NOTE> ENA must be set low for IC to be active
  setLightBlank();
  PORT_OUT_MUX_ENA &= ~_BV(PIN_MUX_ENA);

  status.currChannel = 0;
  status.currFrequency = 0;

}

