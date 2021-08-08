/*
 * adc.c
 *
 *  Created on: 01.01.2010
 *      Author: Wolfman
 */

#include "uhfIndication.h"
#include "adc.h"

#include <avr/interrupt.h>

/*
 * init ADC
 */
void initAdc()
{
  ADMUX = _BV(ADLAR) | _BV(REFS0);         // left align results; AVCC as reference
 /*
  * Enable ADC, enable interrupt on complete conversion
  * set conversion rate to clock / 128 (ADPS2:0 > 111)
  * set ADEN low if you want to save power
  */
  ADCSRA = (1 << ADEN | 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0);
#if _ADC_ISR_EN_ > 0
  ADCSRA |= (1 << ADIE);
#endif

  // Note: Multiplexer set to ADC0 pin
  ADMUX |= 0x03;
  // Note: you need to read one sample result before starting
}

/*********************************** ISR *************************************/
#if _ADC_ISR_EN_ > 0
ISR(ADC_vect)
{
  currentAdcValue = ADCH;

  // notify update
  status.updateAdc = TRUE;
}
#endif

