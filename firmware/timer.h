/*
 * timer.h
 *
 *  Created on: 04.10.2009
 *      Author: Wolfman
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

/****************************   GLOBAL VARIABLES    **************************/

/****************************   FUNCTION DECLARATIONS ************************/
void initTimer(void);
void enableTimer2(void);

/****************************   INLINE FUNCTIONS    **************************/

/* timer 0 for ADC starter

   TCCR0: FOC0|WGM00|COM01|COM00|WGM01|CS02|CS01|CS00
   TIMSK: NA|NA|NA|NA|NA|NA|OCIE0|TOIE0
 */
static inline void initTimer0()
{
  TCCR0 = (1 << CS02 | 1 << CS00);      // divide by 1024
  TIMSK |= _BV(TOIE0);                  // enable timer interrupt
}

/* timer 1(a) for displays PWM
  1.020 kHz = 16 MHz / 8 prescaler / 0x07A8
  TCNT1 : 0xCC00, same for ICR1, used as TOP value provider
  COM1A11:0 > 0b10, COM1B11:0 > 00 fast PWM, set 1 at TOP
  FOC1A:B > 0                     Disable forced compare
  WGM13:0 > 0b0110                Use OCR1 as compare value register
  CS12:0  > 0b010                 Clock source prescaling 8
  TICIE1  > 0                     ISR on input capture flag: top value reached
  TCCR1A: COM1A1|COM1A0|COM1B1|COM1B0|FOC1A|FOC1B|WGM11|WGM10
  TCCR1B: ICNC1|ICES1|res|WGM13|WGM12|CS12|CS11|CS10
  TIMSK:  NA|NA|TICIE1|OCIE1A|OCIE1B|TOIE1|NA|NA
 */
static inline void initTimer1()
{
  TCCR1A = (1 << COM1A1 | 1 << WGM11);
  TCCR1B = (1 << WGM12 | 1 << CS11);
  // load target value
  OCR1AH = 0x01;    // 0x1EC = 492
  OCR1AL = 0xEC;

  TIMSK &= ~_BV(TOIE1);

  return;
}

/* timer 2 for charlieplexing
 * example: divide by 256 = 4ms @16 MHz
   TCCR0: FOC2|WGM20|COM21|COM20|WGM21|CS22|CS21|CS20
   TIMSK: OCIE2|TOIE2|NA|NA|NA|NA|NA|NA
 */
static inline void initTimer2()
{
  TCCR2 = _BV(CS20) | _BV(CS21);

  TIMSK |= _BV(TOIE2);
}


#endif /* TIMER_H_ */
