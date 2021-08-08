/*
 * serial.c
 *
 *  Created on: 04.10.2009
 *      Author: Wolfman
 */
#ifndef F_CPU
#error F_CPU not defined
#endif

#define UART_BAUD_RATE   38400

#include "uhfIndication.h"
#include "serial.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdint.h>

/****************************   GLOBAL VARIABLES    **************************/
volatile uint8_t rxValue = 0;
volatile serialStatus_t serialStatus;

/*
 * Functions
 */
void initSerial()
{
  UINT16_T baud;
  baud.i16 = F_CPU / (UART_BAUD_RATE * 16L) -1;
  UBRRH = baud.i8h;
  UBRRL = baud.i8l;

  UCSRC = (1 << URSEL | 1 << UCSZ1 | 1 << UCSZ0);
  UCSRB = (1 << TXEN | 1 << RXEN | 1 << RXCIE);
}

/**
 * sends byte
 * \param[in] byte byte to send
 */
void sendUartByte(uint8_t byte)
{
  UDR = byte;
  while( !(UCSRA & (1<< UDRE)) );       // wait till byte is out of buffer
}

/*
 * sends string
 * \param[in] string string to send
 */
void sendUartString_P(uint8_t *string)
{
  uint8_t character;

	while ((character = pgm_read_byte(string))) {
		sendUartByte(character);
		string++;
	}
}

/*
 * sends string with specific length
 * \param[in] string string to send
 * \param[in] string length
 */
void sendUartString_n(uint8_t *string, uint8_t length)
{
  int i = 0;

  for(i = 0; i < length; i++) {
    sendUartByte(*(string +i));
  }
}

void sendUartBits(uint8_t byte)
{
  if(byte & 0x80)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x40)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x20)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x10)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x08)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x04)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x02)
    sendUartByte('1');
  else
    sendUartByte('0');
  if(byte & 0x01)
    sendUartByte('1');
  else
    sendUartByte('0');

  sendUartNewline();
}

/*
 * sends carriage return and line feed
 */
void sendUartNewline()
{
  UDR = '\r';
  while( !(UCSRA & (1<< UDRE)) );       // wait till byte is out of buffer
  UDR = '\n';
  while( !(UCSRA & (1<< UDRE)) );       // wait till byte is out of buffer
}

/*
 * checks baud rate error
 * \retVal 0  baud rate error acceptable
 * \retVal 1  baud rate error above 2 percent
 */
int checkBaudError()
{
  int16_t UBRR_VAL = ((F_CPU + UART_BAUD_RATE * 8) / (UART_BAUD_RATE * 16) - 1);
  int16_t BAUD_REAL = (F_CPU / (16 * (UBRR_VAL +1)));
  int16_t BAUD_ERROR = ((BAUD_REAL * 1000) / UART_BAUD_RATE - 1000);
  // max. +/-10 per mill error
  if ((BAUD_ERROR>10) || (BAUD_ERROR<-10))
  {
    return -1;  // error magic number
  }

  return 0;
}

/**************************** Interrupt Service Routine     ******************/
ISR (USART_RXC_vect)
{
  rxValue = UDR;
  serialStatus.rx = TRUE;
  // pings back received value
  sendUartByte(rxValue);

}
