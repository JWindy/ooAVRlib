// testing application for libTimer
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
#include "libTimer.h"
#include "libIOHandler.h" //v0.1
#include "ioMapAttiny85DefaultDebuggingBoard.h"

volatile uint8_t interruptCounter = 0;//global variable for ISR

int main(void) {
    Timer0Attiny85* myTimer0 = Timer0Attiny85::getInstance();
    libIOHandler myIoHandler;

    uint8_t mySemaphorKey = 0;

    clockPrescaler_t prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue = 255; //OCR0A data sheet p80

    const uint8_t interruptCounterThreshold = 100;//changing this value changes the expected behaviour during the test proceedures
    const uint8_t numberLoopsPerTest = 4; //changing this value changes the expected behaviour during the test proceedures
    uint8_t loopCounter = numberLoopsPerTest;

    //setup timer    
    mySemaphorKey = myTimer0->pSemaphore.lock();
    myTimer0->configTimer(mySemaphorKey);
    sei();

    //setup LED
    myIoHandler.setPinOutput(LED_PIN);
    myIoHandler.setPinLow(LED_PIN);

    /*------------------------------------------------------------
    1. timer test
    expected behaviour: 
      led off
      led blinks twice, period approx. 3 sec
      led off
    ------------------------------------------------------------ */
    prescaler = PRESCALER1024;
    myTimer0->setPrescaler(mySemaphorKey, prescaler);
    outputCompareMatchValue = 255;
    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
    myTimer0->start(mySemaphorKey);
    
    while (loopCounter) {
        if (interruptCounter >= interruptCounterThreshold) {
            cli();
            interruptCounter = 0;
            myIoHandler.togglePin(LED_PIN);
            loopCounter--;
            sei();
        }
    }
    myTimer0->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN);
    _delay_ms(1000UL);

    /*------------------------------------------------------------
    2. timer test - change OCR value
    expected behaviour: 
      led off
      led blinks twice, period approx. 2 sec
      led off
    ------------------------------------------------------------ */
    outputCompareMatchValue = 160;
    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);

    interruptCounter = 0;
    loopCounter = numberLoopsPerTest;
    myTimer0->start(mySemaphorKey);

    while (loopCounter) {
        if (interruptCounter >= interruptCounterThreshold) {
            cli();
            interruptCounter = 0;
            myIoHandler.togglePin(LED_PIN);
            loopCounter--;
            sei();
        }
    }
    myTimer0->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN);
    _delay_ms(1000UL);
    
    /*------------------------------------------------------------
    3. timer test - change prescaler
    expected behaviour: 
      led off
      led blinks twice, period approx. 0,75 sec
      led off
    ------------------------------------------------------------ */

    outputCompareMatchValue = 255;
    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
    prescaler = PRESCALER256;
    myTimer0->setPrescaler(mySemaphorKey, prescaler);

    interruptCounter = 0;
    loopCounter = numberLoopsPerTest;
    myTimer0->start(mySemaphorKey);

    while (loopCounter) {
        if (interruptCounter >= interruptCounterThreshold) {
            cli();
            interruptCounter = 0;
            myIoHandler.togglePin(LED_PIN);
            loopCounter--;
            sei();
        }
    }
    myTimer0->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN);
    _delay_ms(1000UL);
    
    /*------------------------------------------------------------
    4. timer test - start and stop method
    expected behaviour: 
        led off
        led on for approx. 2 sec
        led off
        led on for approx. 3 sec
        led off
    ------------------------------------------------------------ */
    
    outputCompareMatchValue = 160;
    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
    prescaler = PRESCALER1024;
    myTimer0->setPrescaler(mySemaphorKey, prescaler);

    interruptCounter = 0;
    loopCounter = numberLoopsPerTest;
    myTimer0->start(mySemaphorKey);

    while (loopCounter) {
        if (interruptCounter >= interruptCounterThreshold) {
            cli();
            interruptCounter = 0;
            myIoHandler.togglePin(LED_PIN);
            loopCounter--;
            if (loopCounter == 1 && interruptCounter == 0) {
                myTimer0->stop(mySemaphorKey);
                _delay_ms(1000UL);
                myTimer0->start(mySemaphorKey);
            }
            sei();
        }

    }
    myTimer0->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN);
    _delay_ms(1000UL);
    
    
    //ToDo: move to libUtilitTest
    /*------------------------------------------------------------
     test semaphore lock and unlock
    expected behaviour:
      loop
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
    
    prescaler = PRESCALER256;//will be applied during test

    interruptCounter = 0;
    loopCounter = 6;
    myTimer0->start(mySemaphorKey);

    while (loopCounter) {
        if (interruptCounter >= interruptCounterThreshold) {
            cli();
            interruptCounter = 0;
            myIoHandler.togglePin(LED_PIN);
            loopCounter--;
            //wrong key -> change of prescaler should not be applied
            if (loopCounter == 2 && interruptCounter == 0) {
                myTimer0->setPrescaler(0, prescaler);
                myTimer0->start(mySemaphorKey);
            }
            //correct key -> change of prescaler should be applied
            if (loopCounter == 1 && interruptCounter == 0) {
                mySemaphorKey = myTimer0->pSemaphore.unlock(mySemaphorKey);
                myTimer0->setPrescaler(42, prescaler);
                myTimer0->start(mySemaphorKey);
            }
            sei();
        }
    }
    myTimer0->stop(mySemaphorKey);
    mySemaphorKey = myTimer0->pSemaphore.lock();

    //start PWM, set interrupt to output pin and toggle led
    uint8_t dutyCycle = 100; //in %
    myTimer0->setDutyCycle(mySemaphorKey, dutyCycle);

    
    cli();
    myTimer0->cleanup(mySemaphorKey);
    mySemaphorKey = myTimer0->pSemaphore.unlock(mySemaphorKey);
    return 0;
}//int main(void))

//timer0 compare A match interrupt

ISR(TIM0_COMPA_vect) {
    interruptCounter++;
};