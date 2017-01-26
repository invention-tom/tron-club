// Code that counts up and displays it on the LCD screen
// Hitachi HD 44780 used in 8-bit mode. A timer interrupt is used to time the counting
// LCD_data is a function that takes in 8 bits and displays a character on screen.
// LCD_data(0,0,1,1,A,B,C,D) can display the digits 0 to 9. ABCD=0001 displays "1", ABCD =0010 displays "2", etc...
// Choose what base you count in when the LCD_base function is called.
// Created by TronClub.com

#include <avr/io.h>
#include <avr/interrupt.h> 	//Allows the use of interrupts

int count=0;

int main(void){
LCD_init();
clear_display();

TCCR0B |= (1<<CS02) | (1<<CS00) ;    //prescale timer by a factor of 1024
TIMSK0 |= (1<<TOIE0);    //enable timer overflow interrupt
sei();    				//Sets global interrupt bit; Enables interrupts

for(;;){
}
return 0;
}

 ISR(TIM0_OVF_vect) {
 cursor_right();
 count++;
 base_convert(count,10); //Choose a base from 2 to 10
}


//base_convert changes the input integer to an array of numbers in the desired base, and then displays each element of that array

void base_convert(int num, int base){
char remainder;
char index = 0 ;
char digit[4];
while(num != 0){
   remainder = (num%base);
   num = (num/base);
   digit[index] = remainder;
   Disp_num(digit[index]);
   index++;
   shift_cursor();
   shift_cursor();
   }
}

void Disp_num(int num)			//Takes in a number from 0 to 9 and displays it on screen.
{
char remainder;
char index = 0 ;
char digit[4]={0,0,0,0};
while(num != 0){
   remainder = (num%2);
   num = (num/2);
   digit[index] = remainder;
   index++;
	}
LCD_data(0,0,1,1,digit[3],digit[2],digit[1],digit[0]);
}
