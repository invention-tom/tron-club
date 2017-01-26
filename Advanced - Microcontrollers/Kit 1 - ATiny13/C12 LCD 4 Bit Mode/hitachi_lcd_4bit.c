// Source file for Hitachi HD44780 LCD screen in 4-bit mode
// Send RS, followed by bits D7 to D4, then trigger Screen Enable
// PB0 -> Data		PB2 -> Register Clock 		PB3 -> Screen Enable
// Created by TronClub.com

#include <avr/io.h>
#include <util/delay.h>

#define DATA PB0		//This is the 0 or 1 to be sent to the shift register every time REG_CLK rising edge triggers.
#define REG_CLK PB2		//Shifts the data in the shift register (Rising edge triggered)
#define ENABLE PB3		//Screen Enable: Falling Edge triggered, causes screen to read the 4 bits D7-D4. 


void Send_zero(void){	//Switching REG_CLK from LOW to HIGH sends one bit of data to the shift register. 
						// clear DATA and REG_CLK, then set REG_CLK.
PORTB &= ~(1<<DATA | 1<<REG_CLK);
PORTB |= (1<<REG_CLK); 
}

void Send_one(void){		//set DATA and clear REG_CLK, then set REG_CLK. 
PORTB = (1<<DATA);
PORTB |= (1<<REG_CLK);		//sets DATA = 1 		then sets REG_CLK. 
}

void LCD_read(void){  		//Keep REG_SEL unchanged, Set ENABLE as HIGH, then LOW to trigger LCD screen enable.
PORTB |= (1<<ENABLE);		
_delay_ms(2);
PORTB &= ~(1<<ENABLE);   
_delay_ms(2);
}


void clear_display(void){
Send_zero();
Send_zero();
Send_zero();
Send_zero();
Send_zero();
LCD_read();		//first nibble of clear display 0000-0001

Send_zero();
Send_zero();
Send_zero();
Send_zero();
Send_one();
LCD_read();		//second nibble of clear display 0000-0001
_delay_ms(3);
}


void LCD_init(void){			//initialize 

DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2)|(1<<DDB3);
PORTB = 0;
Send_zero();
Send_zero();
Send_zero();
Send_one();
Send_one();
LCD_read();
_delay_ms(5);

Send_zero();
Send_zero();
Send_zero();
Send_one();
Send_one();
LCD_read();

_delay_ms(2);
LCD_read();


Send_zero();	//Q5 -> RS
Send_zero();  	//Q4 - >D7
Send_zero();	//Q3 -> D6
Send_one();		//Q2 -> D5
Send_zero();	//Q1 - >D4
LCD_read();		//send 0010 (RS=0) command, which sets 4 bit mode
_delay_ms(2);
LCD_read(); 	//send first nibble of 0010-1000 command; function set

Send_zero();
Send_one();
Send_zero();
Send_zero();
Send_zero();
LCD_read();		//sends second nibble of 0010-1000 command - function set.

Send_zero();
Send_zero();
Send_zero();
Send_zero();
Send_zero();
LCD_read();		//sends first nibble of 0000-1000 command - Display off, cursor off, blinking off

Send_zero();
Send_one();
Send_zero();
Send_zero();
Send_zero();
LCD_read();		//sends second nibble of 0000-1000 command - Display off, cursor off, blinking off

clear_display();

		
Send_zero();
Send_zero();
Send_zero();
Send_zero();
Send_zero();
LCD_read(); 	//send first nibble of 0000-0110 command

Send_zero();
Send_zero();
Send_one();
Send_one();
Send_zero();
LCD_read(); 	//send second nibble of 0000-0110 command	-- Entry mode

Send_zero();	
Send_zero();
Send_zero();
Send_zero();
Send_zero();
LCD_read();		//sends first nibble of 0000-1100 command --- Display ON	

Send_zero();
Send_one();
Send_one();
Send_zero();
Send_zero();
LCD_read();		//sends first nibble of 0000-1100 command --- Display ON
}

void print_j_su(void){		//prints ス 1011-1101
Send_one();
Send_one();
Send_zero();
Send_one();
Send_one();
LCD_read();

Send_one();
Send_one();
Send_one();
Send_zero();
Send_one();
LCD_read();
}

void print_A(void)		//Prints "A" 0100-0001
{
Send_one();
Send_zero();
Send_one();
Send_zero();
Send_zero();
LCD_read();

Send_one();
Send_zero();
Send_zero();
Send_zero();
Send_one();
LCD_read();
}