/*
 * spi.c
 *
 *  Created on: 07.10.2009
 *      Author: Wolfman
 */
#include "spi.h"
#include "uhfIndication.h"

#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t spiRxValue = 0;

/*
 * initialises Serial Peripheral Interface
 * Set to master with clock rate / 4
 */
void initSpi()
{
#if _MASTER_SPI_ > 0
#if _FAST_SPI_ > 0
  SPCR = (1 << SPE | 1 << MSTR | 1 << SPR1);
#else
  SPCR = (1 << SPE | 1 << MSTR | 1 << SPR1 | 1 << SPR0);
#endif
#else
  SPCR = (1 << SPE | 1 << SPIE);
#endif
}

/*
 * sends a byte using SPI
 */
void sendSpiByte(uint8_t cData)
{
  /* Start transmission */
  SPDR = cData;
#if _MASTER_SPI_ > 0
  /* Wait for transmission complete */
  while (!(SPSR & (1 << SPIF)))
    ;
#endif
}

#if _MASTER_SPI_ > 0
/*
 * sends dummy byte to receive slave data
 */
uint8_t receiveSpiByte()
{
  SPDR = DUMMY_BYTE;       // send dummy byte
  while (!(SPSR & (1 << SPIF))) {
    ;
  }
  return SPDR;      // receive byte from slave
}

/**
 * sends string using SPI
 */
void sendSpiString(uint8_t *string, uint8_t length)
{
  while (length)
  {
    sendSpiByte(*string);
    string++;
    length--;
  }
}

#endif

/**************************** Interrupt Service Routine     ******************/
#if _SPI_ISR_ > 0
ISR (SPI_STC_vect)
{
  isrSpi();
}
#endif
