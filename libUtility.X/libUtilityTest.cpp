// testing application for libUtility
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
#include <avr/interrupt.h>
#include "libUtility.h" //copy to ./lib as well, since libTimer depends on libUtility as well
#include "libTimer.h"  //v0.1
#include "libIOHandler.h" //v0.1
#include "ioMapAttiny85DefaultDebuggingBoard.h"

volatile uint8_t compareMatchInterruptCounter = 0; //global variable for ISR

//timer0 compare A match interrupt 
ISR(TIM0_COMPA_vect) {
    compareMatchInterruptCounter++;
};

int main(void) {
    Timer0Attiny85* myTimer0 = Timer0Attiny85::getInstance();
    libIOHandler myIoHandler;

    uint8_t mySemaphorKey = 0;

    clockPrescaler_t prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue = 255; //OCR0A data sheet p80

    const uint16_t interruptCounterThreshold = 100UL; //changing this value changes the expected behaviour during the test proceedures
    const uint8_t numberLoopsPerTest = 6; //changing this value changes the expected behaviour during the test proceedures
    uint8_t loopCounter = numberLoopsPerTest;

    //setup LED
    myIoHandler.setPinOutput(LED_PIN);
    myIoHandler.setPinLow(LED_PIN);

    //setup timer    
    mySemaphorKey = myTimer0->pSemaphore.lock();
    myTimer0->configTimerCompareMatch(mySemaphorKey);
    sei();

    /*------------------------------------------------------------
     test semaphore lock and unlock
    expected behaviour:
      loopCounter
        6 led off
        5 led on for approx. 3 sec
        4 led off
        3 led on for approx. 3 sec 
        2 led off
        1 led on for approx. 0,75 sec 
        0 led off
    ------------------------------------------------------------ */
    prescaler = PRESCALER1024;
    myTimer0->setPrescaler(mySemaphorKey, prescaler);
    outputCompareMatchValue = 255;
    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);

    prescaler = PRESCALER256; //will be applied during test

    compareMatchInterruptCounter = 0;
    myTimer0->start(mySemaphorKey);

    while (loopCounter) {
        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
            cli();
            compareMatchInterruptCounter = 0;
            myIoHandler.togglePin(LED_PIN);
            loopCounter--;
            //wrong key -> change of prescaler should not be applied
            if (loopCounter == 2 && compareMatchInterruptCounter == 0) {
                myTimer0->setPrescaler(0, prescaler);
                myTimer0->start(mySemaphorKey);
            }
            //correct key -> change of prescaler should be applied
            if (loopCounter == 1 && compareMatchInterruptCounter == 0) {
                mySemaphorKey = myTimer0->pSemaphore.unlock(mySemaphorKey);
                myTimer0->setPrescaler(42, prescaler);
                myTimer0->start(mySemaphorKey);
            }
            sei();
        }
    }
    myTimer0->stop(mySemaphorKey);
    mySemaphorKey = myTimer0->pSemaphore.lock();

    
    return 0;
}//int main(void))
