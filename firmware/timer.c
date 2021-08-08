/*
 * timer.c
 *
 *  Created on: 03.10.2009
 *      Author: Wolfman
 */
#include "timer.h"
#include "uhfIndication.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/****************************    Functions              **********************/
/*
 * Functions
 */
void initTimer()
{
  initTimer0(); // ADC starter
  initTimer1(); // PWM
  initTimer2(); // Test Timer
}

void enableTimer2()
{
  TIMSK |= (1 << TOIE2);
}

/**************************** Interrupt Service Routine **********************/
/*
 * Timer 0. calls isrAdc function.
 */
ISR (TIMER0_OVF_vect)
{
  if (status.boot) {
    isrTestTimer();
  }
  isrAdc();
}

/*
 * Timer 2.
 */
ISR (TIMER2_OVF_vect)
{
  isrCharlieplex();
}
