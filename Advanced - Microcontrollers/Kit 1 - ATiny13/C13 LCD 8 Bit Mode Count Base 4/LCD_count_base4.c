// Code that counts up and displays that on the LCD screen
// Hitachi HD 44780 used in 8-bit mode. A timer interrupt is used to time the counting, and an array of functions is used to display the required number.
// Base 4 counting (from 000 to 333)
// Uses an array of functions, where each function prints a different number on screen.
// Not a very efficient code in terms of memory, so it is limited in terms of what base it counts in and the number of digits displayed.  
// Created by TronClub.com

#include <avr/io.h>
#include <avr/interrupt.h> 


void print_0(){
	Print_0();
}

void print_1(){
	Print_1();
}

void print_2(){
	Print_2();
}

void print_3(){
	Print_3();
}


char i =0;		//variable that keeps track of 1st digit(least significant)
char j =0;		//2nd digit
char k =0;		//3rd digit	(most significant)
void (*func_ptr[4])() = {print_0, print_1, print_2, print_3};

int main(void){
	LCD_init();			//initialize the screen. This step is necessary to display anything on the screen.
	clear_display();

	TCCR0B |= (1<<CS02) | (1<<CS00) ;    //prescale timer by a factor of 1024 
	TIMSK0 |= (1<<TOIE0);    //enable timer overflow interrupt   
	sei();    //Sets global interrupt bit; Enables interrupts

	while (1);
	return 0;
}

 
ISR(TIM0_OVF_vect) {
  //overflow occurs at 1024/9600000*256=27.3ms -> thus approximately 4 counts per second.
	cursor_home();
	i = i+1;
	i = i%4;
	if (i<1){
		j = j+1;
		j = j%4;}
	(*func_ptr[k])();
	(*func_ptr[j])();
	(*func_ptr[i])();
	if (j==3 & i==3){ 
		k=k+1;}
} 
 