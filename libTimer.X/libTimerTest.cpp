// testing application for <project name>
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

#define HW_rev

#include <util/delay.h>
#include "libTimer.h"
#include "ioMapAttiny85DefaultDebuggingBoard.h"

int main(void){
    Timer0Attiny85* myTimer0 = Timer0Attiny85::getInstance(); 
    
    uint8_t mySemaphorKey = 0;
    
    clockPrescaler_t prescaler      = PRESCALER1; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue = 255; //OCR0A data sheet p80
    uint8_t dutyCycle               = 100; //in %
    
    //test timer    
    mySemaphorKey = myTimer0->pSemaphore->lock();
    
    myTimer0->setPrescaler(mySemaphorKey, prescaler);
    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
    myTimer0->setDutyCycle(mySemaphorKey, dutyCycle);
    
    myTimer0->configTimer(mySemaphorKey);
    
    //link to output pin in ISR
    
    myTimer0->start(mySemaphorKey);
    _delay_ms(1000);
    myTimer0->stop(mySemaphorKey);
//    
    //change Prescaler
    
    //change OCR value
            
    //test semaphor locking

            
            
    //start timer, set interrupt to output pin and toggle led
    


    
    //start PWM, set interrupt to output pin and toggle led
    
    
    return 0;
}//int main(void))
