/*
 * Source file for Hitachi HD44780 LCD screen in 8 bit mode
 * The ATTiny13 sends one bit at a time to a shift register, and after sending 8 bits, the Screen's Enable is set from high to low to read the 8 bits.
 * Send_zero and Send_one commands can change value of REG_SEL, so make sure to set or clear REG_SEL as desired directly before using LCD_read.
 * Created by TronClub.com
*/

#include <avr/io.h>
#include <util/delay.h>

#define DATA PB0		//This is the 0 or 1 to be sent to the shift register every time REG_CLK rising edge triggers.
#define REG_CLK PB1
#define ENABLE PB2		//Screen reads the 8 bits at falling edge
#define REG_SEL PB3		//Tells screen whether what it's reading is an instruction or a character.

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

void cursor_home(void){			//0000 0010	Command -- Return Cursor Home
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_zero();
  PORTB &= ~(1<<REG_SEL);
  LCD_read();
}

void clear_display(void){		//0000 0001 RS=LOW		Clears display, 1.5ms execution time
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  PORTB &= ~(1<<REG_SEL);
  LCD_read();
}

void LCD_init(void){			//initialize in 8 bit mode

  DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3);
  PORTB = 0;

  Send_zero();			// send   0 0 1 1 - 1 0 0 0 command: Function set, 8 bit, 2 lines
  Send_zero();
  Send_one();
  Send_one();
  Send_one();
  Send_zero();
  Send_zero();
  Send_zero();
  PORTB &= ~(1<<REG_SEL);		//clear Register Select (REG_SEL)
  LCD_read();	//0011-1000

  Send_zero();			//Send 0 0 0 0 - 1 1 1 1 command: Display ON, Cursor ON, blinking
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_one();
  Send_one();
  Send_zero();
  PORTB &= ~(1<<REG_SEL);
  LCD_read();	//0000-1111

  Send_zero();			//send 0 0 0 0 - 0 1 1 0 command: Entry mode, increment Cursor position, No display shift
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_one();
  Send_zero();
  PORTB &= ~(1<<REG_SEL);
  LCD_read();
}

void Print_CGRAM(void){		//0000-0000 Prints the first character in CCGRAM.
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  PORTB |= (1<<REG_SEL);
  LCD_read();
}

void save_bitmap(void){
  //a bitmap of: 日. Note that it is an 8x5 image, so 8 bytes will be sent, and only 5 bits from each byte count. (i.e first 3 bits don't matter so they're set to 0)
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();

  Send_zero();
  Send_zero();
  Send_zero();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  Send_one();
  PORTB |= (1<<PB3);
  LCD_read();
}

void LCD_CGRAM(void){		//0100-0000 Set CGRAM address
  Send_zero();
  Send_one();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  Send_zero();
  PORTB &= ~(1<<PB3);
  LCD_read();
}
