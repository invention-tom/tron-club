/*
 * MCU: ATtiny13
 * Code to turn on an LED connected to PB4.
 * Created by TronClub.com 
 */

#include <avr/io.h>

int main(void) {
	/* Turn on the LED connected to PB4
	DDRB = (1<<DDB4); // Set PB4 as output.
	PORTB = (1<<PB4); // Set output of PB4 as HIGH. Turns on LED.
	*/
	
	/* Turn off the LED connected to PB4
	DDRB = (1<<DDB4); // Set PB4 as output.
	PORTB = (0<<PB4); // Set output of PB4 as LOW. Turns off LED.
	*/
	
	// Turn on the LED connected to PB3
	DDRB = (1<<DDB3); // Set PB3 as output.
	PORTB = (1<<PB3); // Set output of PB3 as HIGH. Turns on LED.
	
	return 0;
}
