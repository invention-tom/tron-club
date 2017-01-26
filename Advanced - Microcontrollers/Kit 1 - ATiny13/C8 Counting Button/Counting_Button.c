/*
 * A button which counts up every time you press it, and then another button that lets the light flash as many times as the first button was pressed
 * use PCINT0 as the counting button, and INT0 as the "display the counts" button
 * To keep the counts accurate, debounce must be taken into account.
 * Which LED flashes can be decided at the #define statement.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define FLASHING PB4
#define COUNTING PB3

int counter = 0; 	//This variable is used to deal with switch debounce.
int flash_num =0;	//This variable keeps track of how many times the "count" button was pressed.

ISR(TIM0_OVF_vect)	//timer module used for debounce
{
counter++;
}


int main(void) {
	PCMSK |= (1<<PCINT0);
	GIMSK |= (1<<PCIE);
	GIMSK |= _BV (INT0);
	MCUCR = _BV (ISC01) | _BV(ISC00); 		//Set rising/Falling edge. See ATtiny13 data sheet table 9-2
	sei();
	DDRB = (1<<DDB4)|(1<<DDB3);
	PORTB = 0;
	TIMSK0 |= (1<<TOIE0);
	for (;;)
	{
	_delay_ms(10);
	if (counter<50) 						//Stop counting to prevent overflow.
	{TCCR0B |= (1<<CS00);}					//enable timer overflow interrupt by setting its prescale
	else { TCCR0B &= 0B11111000;}			//if counter is over 50 the timer is no longer needed. the next button change will be counted.
	}
	return 0;
}

ISR (PCINT0_vect) 			// ISR when "Count" Button is pressed.
{
	TCCR0B &= 0B11111000;;				//Disable timer interrupts. The button has been pressed.
	if (counter < 20)
	{counter = 0;						// We haven't reached 15 counts, so what caused the trigger is just a bounce. No change to LED.
	}
	else{counter = 0;					//if counter is greater than 15, the trigger is an actual button press so change LED output.
	PORTB ^= 1<<COUNTING;
	flash_num++;
	}
}


	ISR (INT0_vect)		 	//ISR when "Display" button is pressed
{
	int i=0;
	flash_num = flash_num/2 ;
	for (i=1;i<=flash_num;i++)
	{PORTB = (1<<FLASHING);
	_delay_ms(500);
	PORTB=0;
	_delay_ms(100);}
	flash_num =0;
}
