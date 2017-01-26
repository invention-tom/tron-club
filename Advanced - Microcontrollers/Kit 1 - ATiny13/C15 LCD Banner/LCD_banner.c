/*
Hitachi HD44780 LCD Screen in 8 bit mode.
Shift a string of characters across the LCD screen
Created by TronClub.com
*/

#include <avr/io.h>
#include <util/delay.h>

// display the string, then clear screen and shift position + 1.

int main(void){
LCD_init();
clear_display();

while(1){
int j=0;
	while (j<17){		//Characters shift to the right until they go off-screen. (i.e 18 shifts)
	cursor_home();
	int i;
		for (i=0;i<j;i++)
		{
		Print_space();
		}
	Print_word();
	_delay_ms(650);
	clear_display();
	j++;
	}
}
return 0;
}
