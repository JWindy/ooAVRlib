// testing application for libIOHandler
// copyright applies according to LICENSE_software.md in GitHub root folder

#ifndef BAUD
    #define BAUD 9600
#endif

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

int main(void){
    
    IOHandler myIoHandler;
    
    const uint16_t delayLong = 1000;
    const uint16_t delayShort = 500;

    //Test output
    myIoHandler.setPinOutput(LED_PIN);

    // blinking twice with long delay to test  setPinHigh and setPinLow
    myIoHandler.setPinHigh(LED_PIN);
    _delay_ms(delayLong);
    myIoHandler.setPinLow(LED_PIN);
    _delay_ms(delayLong);
    myIoHandler.setPinHigh(LED_PIN);
    _delay_ms(delayLong);    
    myIoHandler.setPinLow(LED_PIN);
    _delay_ms(delayLong);

    // blinking three times with short delay to test togglePin
    myIoHandler.togglePin(LED_PIN);
    _delay_ms(delayShort);   
    myIoHandler.togglePin(LED_PIN);
    _delay_ms(delayShort);   
    myIoHandler.togglePin(LED_PIN);
    _delay_ms(delayShort);   
    myIoHandler.togglePin(LED_PIN);
    _delay_ms(delayShort);   
    myIoHandler.togglePin(LED_PIN);
    _delay_ms(delayShort);   
    myIoHandler.togglePin(LED_PIN);
    _delay_ms(delayShort);  
    
    //Test input
    myIoHandler.setPinLow(LED_PIN);
    const uint8_t pullUp = true;
    myIoHandler.setPinInput(BUTTON_PIN, pullUp);
    uint8_t buttonState = false;
    while (true){
        buttonState = myIoHandler.readPinRaw(BUTTON_PIN);
        if(buttonState){
            myIoHandler.setPinHigh(LED_PIN);
        }
        myIoHandler.setPinLow(LED_PIN);
    }//while(true)

    //ToDo: test interrupt
    return 0;
}//int main(void))