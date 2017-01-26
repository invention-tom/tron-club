/*
 * this code uses the build-in ADC in the ATtiny13, and outputs a value on the LED screen accordingly
 * We use ADC2, which is PB4 on the ATtiny13.
 * ADC outputs an integer between 0 to 255.
 * TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void) {
		// Set the ADC input to PB4/ADC2, left adjust result. See page 92 of ATtiny13 Datasheet
	LCD_init();
	clear_display();
	int adc_val;
	ADMUX |= (1 << MUX1);
	ADMUX |= (1 << ADLAR);

	// Set clock prescaler (/8)
	// (1<<ADEN) must be set to 1 to allow ADC.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
	while (1){
		adc_val = adc_read();
		adc_val = (adc_val/4)-8;
		int dig1 = adc_val/100;
		int dig2= (adc_val/10) - (10*dig1);
		int dig3 = adc_val - 10*dig2 - 100*dig1;
		Disp_num(dig1);
		Disp_num(dig2);
		Disp_num(dig3);
		LCD_data(1,1,0,1,1,1,1,1); // display "°"
		LCD_data(0,1,0,0,0,0,1,1); // display "C"
			_delay_ms(100);
			clear_display();}
			return 0;
}

int adc_read (void)
{
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for it to finish
    while (ADCSRA & (1 << ADSC));
    return ADCH;
}

void Disp_num(int num)
{
	int remainder;
	int index = 0 ;
	int digit[4]={0,0,0,0};
	while(num != 0){
	   remainder = (num%2);
	   num = (num/2);
	   digit[index] = remainder;
	   index++;
		}
	LCD_data(0,0,1,1,digit[3],digit[2],digit[1],digit[0]);
}
