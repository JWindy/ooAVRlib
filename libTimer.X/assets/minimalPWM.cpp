/*--------------------------------------------------------------------
Description:    This is a absolut minimal implementation of PWM based on timer 0
                without any functions or classes
  
Author:         Johannes Windmiller

Dependencies:   timer 0
 
Version:        no version control

History:        no version control

Supported MUC:  ATtiny85
 
References:     ATtiny 85 data sheet

Comment:        This minimal implementation was used to debug the libTimer, but
                might become usefull one day.
 
Copyright:      see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
    //set output pin
    DDRB |= (1 << DDB0); //set pin output

    //config fast PWM , Top = 0xff data sheet p 79
    TCCR0B &= ~(1 << WGM02);
    TCCR0A |= (1 << WGM01);
    TCCR0A |= (1 << WGM00);

    //prescaler = 64
    TCCR0B &= ~(1 << CS02);
    TCCR0B |= (1 << CS01);
    TCCR0B |= (1 << CS00);

    //clear on compare match, set at bottom
    TCCR0A |= (1 << COM0A1); 
    TCCR0A &= ~(1 << COM0A0);
    
    OCR0A = 1;
    _delay_ms(2000);
    OCR0A = 50;
    _delay_ms(2000);
    OCR0A = 255;
    _delay_ms(2000);
    return 0;
}
