/*
 * Make an LED flash using a timer interrupt.
 * Interrupt Service Routine (ISR) is carried out every time the timer register (TCNT0) overflows. Overflows after 256 counts.
 * Default clock speed of Attiny13 is 9.6 MHz.
 * overflow occurs at 256/9600000 = 0.0266 ms. A prescaler of 1024 means overflow occurs every 0.0266*1024 = 27.2 ms.
 * Therefore, ISR is called approximately 4 times per second.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 	//Allows the use of interrupts

ISR(TIM0_OVF_vect) {

  PORTB ^= (1<<PB4);   //toggle LED ON/OFF
}

int main(void) {
  cli();	//Clears the global interrupt flag
  DDRB = (1<<DDB4);
  PORTB = 0;
  TCCR0B |= (1<<CS02) | (1<<CS00) ;    //prescale timer by a factor of 1024
  TIMSK0 |= (1<<TOIE0);    //enable timer overflow interrupt
  sei();    //Sets global interrupt bit; Enables interrupts
  while(1);	//loop forever, and let the interrupts do the work.
}
