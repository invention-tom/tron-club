/*
 * this code uses the build-in ADC in the ATtiny13, and outputs a value on the LED screen accordingly
 * We use ADC2, which is PB4 on the ATtiny13.
 * ADC outputs an integer between 0 to 255.
 * Created by TronClub.com
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
if (adc_val<25) {LCD_data(0,0,1,1,0,0,0,0);}			//if ADC value is less than 25, then we display "0".
else if (adc_val<50) {LCD_data(0,0,1,1,0,0,0,1);}
else if (adc_val<75) {LCD_data(0,0,1,1,0,0,1,0);}
else if (adc_val<100) {LCD_data(0,0,1,1,0,0,1,1);}
else if (adc_val<125) {LCD_data(0,0,1,1,0,1,0,0);}
else if (adc_val<150) {LCD_data(0,0,1,1,0,1,0,1);}
else if (adc_val<175) {LCD_data(0,0,1,1,0,1,1,0);}
else if (adc_val<200) {LCD_data(0,0,1,1,0,1,1,1);}
else if (adc_val<220) {LCD_data(0,0,1,1,1,0,0,0);}
else {LCD_data(0,0,1,1,1,0,0,1);}						//if ADC value is greater than 220, then we display "9".
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
