/*
 * MCU: ATtiny13
 * Code to turn on an LED connected to PB4.
 * Created by TronClub.com 
 */

#include <avr/io.h>

int main(void) {
	DDRB = (1<<DDB4);; // Set PB4 as output
	PORTB = (1<<PB4); // Set output of PB4 as HIGH. Turns on LED. 
	return 0;
}
