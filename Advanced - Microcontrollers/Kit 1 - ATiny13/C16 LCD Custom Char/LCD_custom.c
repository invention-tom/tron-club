/* Display a custom character, Example: 日
 * Hitachi HD 44780 used in 8-bit mode
 * Set memory to CGRAM then send 8 bytes to make an 8x5 bitmap.
 * Set memory back to DDRAM, then send 0000-0000 to print the custom character.
 * Created by TronClub.com
*/

#include <avr/io.h>

int main(void){
LCD_init();
clear_display();

LCD_CGRAM();		//Sets memory to CGRAM instead of DDRAM.
save_bitmap();		//Writes the bitmap of the character to CCGRAM
clear_display();	//Sets DDRAM address to 0. it is necessary to set DDRAM address before anything can be displayed on the screen.
Print_CGRAM();		//Sends 0000-0000, which prints the first character in CGRAM.

return 0;
}
