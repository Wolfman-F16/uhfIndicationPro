/*
 * spi.h
 *
 *  Created on: 07.10.2009
 *      Author: Wolfman
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

/****************************   DEFINITIONS         **************************/
#define _MASTER_SPI_    0
#define _FAST_SPI_      0
#define _SPI_ISR_       1
#define  DUMMY_BYTE     0x5A  // Z
#define  SPI_SOF        MSG_TYPE  // check value <- value is for PWM ID

/****************************   GLOBAL VARIABLES    **************************/
extern volatile uint8_t spiRxValue;

/****************************   FUNCTION DECLARATIONS ************************/
void initSpi(void);
void sendSpiByte(uint8_t );
#if _MASTER_SPI_ > 0
void    sendSpiString(uint8_t *, uint8_t );
uint8_t receiveSpiByte(void);

#endif

#endif /* SPI_H_ */
