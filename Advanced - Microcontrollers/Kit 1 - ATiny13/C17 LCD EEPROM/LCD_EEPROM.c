// Code that displays a custom character
// The bitmap for the custom character will be saved in EEPROM.
// Created by TronClub.com


#include <avr/io.h>
#include <avr/eeprom.h>

int main(void)
{
LCD_init();
clear_display();
LCD_CGRAM();

eeprom_write_byte(0,0b11111);
eeprom_write_byte(1,0b11111);
eeprom_write_byte(2,0b00100);
eeprom_write_byte(3,0b00100);
eeprom_write_byte(4,0b00100);
eeprom_write_byte(5,0b00100);
eeprom_write_byte(6,0b00100);
eeprom_write_byte(7,0b00100);

char j;
for (j=0;j<8;j++){
	int printme = eeprom_read_byte(j);
	Disp_num(printme);
	}

clear_display();
Print_CGRAM();

return 0;
}

void Disp_num(int num)
{
int remainder;
char index = 0 ;
char digit[5]={0,0,0,0,0};
while(num != 0){
   remainder = (num%2);
   num = (num/2);
   digit[index] = remainder;
   index++;
	}
LCD_data(0,0,0,digit[4],digit[3],digit[2],digit[1],digit[0]);
}
