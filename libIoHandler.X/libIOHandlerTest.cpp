// testing application for libIOHandler
// copyright applies according to LICENSE_software.md in GitHub root folder

#define BAUD 9600

#ifndef F_CPU
    #define F_CPU 8000000
#endif

#ifndef __AVR_ATtiny85__
    #define __AVR_ATtiny85__
#endif

#define HW_ATtiny85_Default_Debugging_Board

#include "ioMapAttiny85DefaultDebuggingBoard.h"
#include "libIOHandler.h"

#include <util/delay.h> 

const uint16_t delayLong = 1000;
const uint16_t delayShort = 500;

//Test output
setPinOutput(LED_PIN);

// blinking twice with long delay to test  setPinHigh and setPinLow
setPinHigh(LED_PIN);
_delay_ms(delayLong);
setPinLow(LED_PIN);
_delay_ms(delayLong);
setPinHigh(LED_PIN);
_delay_ms(delayLong);    
setPinLow(LED_PIN);
_delay_ms(delayLong);

// blinking three times with short delay to test togglePin
togglePin(LED_PIN);
_delay_ms(delayShort);   
togglePin(LED_PIN);
_delay_ms(delayShort);   
togglePin(LED_PIN);
_delay_ms(delayShort);   
togglePin(LED_PIN);
_delay_ms(delayShort);   
togglePin(LED_PIN);
_delay_ms(delayShort);   
togglePin(LED_PIN);
_delay_ms(delayShort);  

//Test input
setPinLow(LED_PIN);
const uint8_t pullUp = true;
//setPinInput(BUTTON_PIN, pullUp);
uint8_t buttonState = false;
while (true){
    buttonState = readPin(BUTTON_PIN);
    if(buttonState){
        setPinHigh(LED_PIN);
    }
    setPinLow(LED_PIN);
}//while(true)

//ToDo: test interrupt