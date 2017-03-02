/*
 * Holding button holds state of LED.
 * The purpose of this code is to deal with the bounce of metal contacts.
 * A button press will only have an effect when the metal contacts have stabilized and stopped bouncing.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int counter = 0;
ISR(TIM0_OVF_vect)
{
counter++;
}

int main(void) {
	PCMSK |= (1<<PCINT0);
	GIMSK |= (1<<PCIE);
	sei();
	DDRB = (1<<DDB3);
	PORTB = 0;
	TIMSK0 |= (1<<TOIE0); //enable timer overflow interrupt
	for (;;)
	{
		_delay_ms(10);
			if (counter<50)   //An if statement which stops the counter is necessary to prevent overflow of the counter variable.
			{
				TCCR0B |= (1<<CS00); //enable timer overflow interrupt by setting its prescale
			} else {
				TCCR0B &= 0B11111000; //if counter is over 50 the timer is no longer needed. the next button change will be counted.
			}
	}
	return 0;
}

ISR (PCINT0_vect)
{
	TCCR0B &= 0B11111000; //Disable timer interrupts. The button has been pressed.
	if (counter < 15)
	{
		counter = 0;   // We haven't reached 15 counts, so what caused the trigger is just a bounce. No change to LED.
	} else {
		counter = 0;  //if counter is greater than 15, the trigger is an actual button press so change LED output.
		PORTB ^= 1<<PB3;
	}
}
