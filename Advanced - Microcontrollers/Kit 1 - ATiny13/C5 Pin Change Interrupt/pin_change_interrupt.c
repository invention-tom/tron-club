/*
 * Turn on LED using a Button interrupt
 * Use pin-change interrupts PCINT1 or PCINT0. Both rising and falling edges will cause the interrupt to trigger.
 * NOTE: switch bounce can affect output
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void) {
	PCMSK |= (1<<PCINT0);	// pin change mask: listen to the designated pin of port B. (Choose PCINT0,PCINT1, etc...)
	GIMSK |= (1<<PCIE);		// enable Pin-Change interrupt (PCINT)
	sei(); 					// Set Enable Global Interrupt bit
	DDRB = (1<<DDB4);
	PORTB = 0;
	for (;;){}
	return 0;
}
ISR (PCINT0_vect) // Interrupt Service Routine, performed when the interrupt is triggered. Always PCINT0_vect even if using PCINT1 or PCINT2.
{
	PORTB ^= 1<<PB4;
	_delay_ms(500);
	PORTB ^= 1<<PB4;
	_delay_ms(500);
	PORTB ^= 1<<PB4;
	_delay_ms(500);
	PORTB ^= 1<<PB4;
	_delay_ms(500);

}
