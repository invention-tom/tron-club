/*
 * MCU: ATtiny13
 * Keep one LED turned on while the other flashes using delays
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h> // Allows the use of delays

int main(void) {
	DDRB = (1<<DDB4) | (1<<DDB3); // Set PB3 and PB4 as output
	
	for (;;) { //loop forever
		PORTB = (1<<PB4) | (0<<PB3); //Set output of PB3 and PB4 as HIGH.
		//_delay_ms(500); // Slower blinking
		_delay_ms(100); // Faster blinking
		
		PORTB = (0<<PB4) | (1<<PB3); //Set only PB4 as high, PB3 is low
		//PORTB = (1<<PB4); //Set only PB4 as high, PB3 is low
		
		//_delay_ms(500); // Slower blinking
		_delay_ms(100); // Faster blinking
	}
	
	return 0;
}
