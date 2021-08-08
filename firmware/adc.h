/*
 * adc.h
 *
 *  Created on: 01.01.2010
 *      Author: Wolfman
 */

#ifndef ADC_H_
#define ADC_H_


#include <avr/io.h>

#define _ADC_ISR_EN_ 1
/****************************   FUNCTION DECLARATIONS ************************/
void    initAdc(void);

/*********************   INLINE FUNCTION DECLARATIONS ************************/
/*
 * loops until adc is complete
 */
static inline void wait4Adc2Complete()
{
  while ( ADCSRA & (1<<ADSC) ) {
   ;
  }
}

/*
 * starts ADC conversion
 */
static inline void startAdcConversion()
{
  ADCSRA |= (1 << ADSC);
}

/*
 * disables adc. used to save power
 */
static inline void disableAdc()
{
  ADCSRA &= ~(1 << ADEN);
}

/*
 * enables adc
 */
static inline void enableAdc()
{
  ADCSRA |= (1 << ADEN);
}
#endif /* ADC_H_ */
