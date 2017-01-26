/*
 * Display "LOW" When button is unpressed, and "HIGH" when button is pressed.
 * Continuously poll PB4 to know if the button is pressed or not.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
LCD_init();
clear_display();

DDRB &= ~(1<<DDB4);		//PB4 is an input

for (;;)				//Loop forever. The interrupt will be triggered when the button is pressed.
	{
	if ( ( PINB & (1<<PB4) ) == (1<<PB4))	//if PB4 is high, print "HIGH". Else Print "LOW"
		{Print_high();
		}
		else {Print_low();}
	_delay_ms(100);
	clear_display();
}
return 0;		}


void Print_high(void){		//Prints the word "HIGH"
	LCD_data(0,1,0,0,1,0,0,0);
	LCD_data(0,1,0,0,1,0,0,1);
	LCD_data(0,1,0,0,0,1,1,1);
	LCD_data(0,1,0,0,1,0,0,0);
}

void Print_low(void){		//Prints the word "LOW"
	LCD_data(0,1,0,0,1,1,0,0);
	LCD_data(0,1,0,0,1,1,1,1);
	LCD_data(0,1,0,1,0,1,1,1);
}
