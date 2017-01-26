/*
 * Turn on LED using a Button interrupt
 * Uses external interrupt INT0, which you can set to rising or falling edge
 * NOTE: switch bounce can affect output
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
	GIMSK |= _BV (INT0); 	// int - Enable external interrupts int0
	MCUCR = _BV (ISC01); 	// Set rising/Falling edge. See ATtiny13 data sheet table 9-2
	sei(); 					// Set Enable Global Interrupt bit
	DDRB = (1<<DDB4);
	PORTB = 0;
	for (;;){} 				//Loop forever. The interrupt will be triggered when the button is pressed.
	return 0;
}

ISR (INT0_vect) // Interrupt Service Routine, performed when the interrupt is triggered
{
	PORTB ^= 1<<PB4;  //Toggle LED ON/OFF
	_delay_ms(500);
	PORTB ^= 1<<PB4;
	_delay_ms(500);
	PORTB ^= 1<<PB4;
	_delay_ms(500);
	PORTB ^= 1<<PB4;
	_delay_ms(500);

}
