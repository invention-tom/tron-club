/*
 * Count the number of times the button is pressed.
 * Continuously poll PB4 to know if the button is pressed or not.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char counter = 0;   //This variable is used to deal with switch debounce.
int flash_num =0;   //This variable keeps track of how many times the "count" button was pressed.

ISR(TIM0_OVF_vect)   //timer module used for debounce
{
	counter++;
}

int main(void) {
	LCD_init();
	clear_display();

	PCMSK |= (1<<PCINT4);
	GIMSK |= (1<<PCIE);
	sei();
	TIMSK0 |= (1<<TOIE0);

	for (;;)
	{
		_delay_ms(10);
		if (counter<50)   //Stop counting to prevent overflow.
		{TCCR0B |= (1<<CS00);}   //enable timer overflow interrupt by setting its prescale
		else { TCCR0B &= 0B11111000;}   //if counter is over 50 the timer is no longer needed. the next button change will be counted.
		clear_display();
		if (flash_num<=9){Disp_num(flash_num);}
		else {Disp_num(flash_num/10);
				Disp_num(flash_num- 10*(flash_num/10) );}
	}
	return 0;
}

void Disp_num(int num)
{
	int remainder;
	int index = 0 ;
	int digit[4]={0,0,0,0};
	while(num != 0){
	   remainder = (num%2);
	   num = (num/2);
	   digit[index] = remainder;
	   index++;
	}
LCD_data(0,0,1,1,digit[3],digit[2],digit[1],digit[0]);
}

ISR (PCINT0_vect)   // ISR when "Count" Button is pressed.
{
	TCCR0B &= 0B11111000;;   //Disable timer interrupts. The button has been pressed.
	if (counter < 15)
	{counter = 0;   // We haven't reached 15 counts, so what caused the trigger is just a bounce. No change to LED.
	}
	else{counter = 0;   //if counter is greater than 15, the trigger is an actual button press so change LED output.
	flash_num++;
	}
}