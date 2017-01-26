/*
 * Initialize the hitachi HD44780 screen in 4-bit mode, then display a character. 
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){
LCD_init();
clear_display();
print_A();
return 0;
}