/*
 * Turn on 2 LEDs using 2 Button interrupts, PCINT0 and INT0
 * ISR_NOBLOCK attribute is used to keep interrupts enabled while the ISR is carried out.
 * NOTE: switch bounce WILL affect your output.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
	PCMSK |= (1<<PCINT0);				 //Listen to the designated pin of port B
	GIMSK |= (1<<PCIE);					 //Enable Pin-Change interrupt
	GIMSK |= _BV (INT0); 			     //Enable external interrupts	
	MCUCR = _BV (ISC01) | _BV(ISC00);	 // Set rising/Falling edge. See ATtiny13 data sheet table 9-2
	sei();								 // Set Enable Global Interrupt bit
	DDRB = (1<<DDB4) | (1<<DDB3);
	PORTB = 0;
	for (;;){}
	return 0;
}
ISR (PCINT0_vect, ISR_NOBLOCK) // Interrupt Service Routine, performed when the Pin-change interrupt is triggered.
{                                       
	PORTB ^= 1<<PB3; //change LED from on to off or vice versa
}

ISR (INT0_vect, ISR_NOBLOCK) // Interrupt Service Routine, performed when the external interrupt is triggered.
{                                       
	PORTB ^= 1<<PB4; //change LED from on to off or vice versa
}