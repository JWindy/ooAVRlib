// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

//ToDo
// Inline declaration in header?

#include <avr/io.h>
#include "libIOHandler.h"


//void init(void){
    #ifndef __AVR_ATtiny85__
        #error "libIOHandler not implemented for selected MUC."
    #endif
//}

inline void setPinOutput(uint8_t argPin){
    uint8_t ddrPin = getDdr(argPin);   
    DDRB |= (1 << ddrPin);
    setPinLow(argPin);
}
        
inline void setPinHigh(uint8_t argPin){
    PORTB |= (1 << argPin); 
}

inline void setPinLow(uint8_t argPin){
    PORTB &= ~(1 << argPin); 
}

inline void togglePin(uint8_t argPin){
    if(readPin(argPin)){
        setPinLow(argPin);
    }
    else{
        setPinHigh(argPin);
    }
}

inline void setPinInput(uint8_t argPin, uint8_t argPullUp = false){
    uint8_t ddrPin = getDdr(argPin);
    
    DDRB &= ~(1 << ddrPin);
    
    if(argPullUp){
        PORTB |= (1 << argPin);
    }
    else{
        PORTB &= ~(1 << argPin);
    }
}

uint8_t readPin(uint8_t argPin){
    uint8_t pinState = PINB & (1 << argPin);
    return pinState;
}

/*
void configureInterrupt(uint8_t argPin, uint8_t argTriggerType, 
uint8_t argTriggerState){
    
    
    
}

void enableInterruptOnPin(uint8_t argPin){
    
    
    
}
void disableInterruptOnPin(uint8_t argPin){
    
    
    
} */

uint8_t getDdr(uint8_t argPin){
    uint8_t ddrPin = 0;
    
    #ifdef __AVR_ATtiny85__
        switch (argPin){
            case PB0:
                ddrPin    = DDB0;
                break;
            case PB1:
                ddrPin    = DDB1;
                break;
            case PB2:
                ddrPin    = DDB2;            
                break;
            case PB3:
                ddrPin    = DDB3;             
                break;
            case PB4:
                ddrPin    = DDB4; 
                break;
        }    
    #elif
        #error "libIOHandler not implemented for selected MUC."
    #endif

    return ddrPin;
}