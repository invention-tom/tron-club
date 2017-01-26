/*
 * Sequentially send eight 0s or 1s to the shift register.
 * Let PB0 be data and PB4 be the shift register's clock. Clock is rising edge triggered.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define DATA PB0
#define REG_CLK PB4


int main(void) {
DDRB |= (1<<DDB0)|(1<<DDB4);
PORTB = 0;

int data[] = {1,0,1,1,0,0,0,1};		//An array representing the 8 bits to be sent to the shift register. 
									//Note that last bit is sent first, so data[0] is the 8th bit, and data[1] is the 7th bit, etc...

int i;
	for (i=0;i<8;i++)
	{
	if (data[i]==0) {PORTB = 0;}
	else 			{PORTB = (1<<DATA);}

	PORTB |= (1<<REG_CLK);				//Trigger clock of shift register (rising edge)
	}
return 0;
}
