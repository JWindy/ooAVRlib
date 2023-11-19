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
#include "ioMapAttiny85LEDDebuggingBoard.h"

volatile uint8_t compareMatchInterruptCounter = 0; //global variable for ISR
volatile uint16_t overflowInterruptCounter = 0; //global variable for ISR

//timer0 compare A match interrupt 
ISR(TIM0_COMPA_vect) {
    compareMatchInterruptCounter++;
};

//timer0 overflow interrupt
ISR(TIM0_OVF_vect) {
    overflowInterruptCounter++;
};

//timer1 compare A match interrupt 
ISR(TIM1_COMPA_vect){
    compareMatchInterruptCounter++;
}

//timer1 overflow interrupt
ISR(TIM1_OVF_vect) {
    overflowInterruptCounter++;
};


int main(void) {
    //------------------------------------------------------------------
    // Timer0Attiny85 test cases
    //------------------------------------------------------------------
    Timer0Attiny85* myTimer0 = Timer0Attiny85::getInstance();
    libIOHandler myIoHandler;

    uint8_t mySemaphorKey = 0;

    clockPrescaler_t prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue = 255; //OCR0A data sheet p80

    const uint16_t interruptCounterThreshold = 100UL; //changing this value changes the expected behaviour during the test proceedures
    const uint16_t overflowInterruptCounterThreshold = 1000UL;

    const uint8_t numberLoopsPerTest = 4; //changing this value changes the expected behaviour during the test proceedures
    uint8_t loopCounter = numberLoopsPerTest;

    //setup LED
    myIoHandler.setPinOutput(LED_PIN0);
    myIoHandler.setPinOutput(LED_PIN1);
    myIoHandler.setPinOutput(LED_PIN4);
    myIoHandler.setPinLow(LED_PIN0);
    myIoHandler.setPinLow(LED_PIN1);
    myIoHandler.setPinLow(LED_PIN4);

    //setup timer    
    mySemaphorKey = myTimer0->pSemaphore.lock();
    myTimer0->configTimerCompareMatch(mySemaphorKey);
    sei();

//    /*------------------------------------------------------------
//    1. timer test LED_PIN0 -> PB0
//    expected behaviour: 
//      led off
//      led blinks twice, period approx. 3 sec
//      led off
//    ------------------------------------------------------------ */
//    prescaler = PRESCALER1024;
//    compareMatchInterruptCounter = 0;
//    myTimer0->setPrescaler(mySemaphorKey, prescaler);
//    outputCompareMatchValue = 255;
//    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//    myTimer0->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            sei();
//        }
//    }
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    2. timer test - change OCR value LED_PIN0 -> PB0
//    expected behaviour: 
//      led off
//      led blinks twice, period approx. 2 sec
//      led off
//    ------------------------------------------------------------ */
//    outputCompareMatchValue = 160;
//    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//
//    compareMatchInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer0->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            sei();
//        }
//    }
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    3. timer test - change prescaler LED_PIN0 -> PB0
//    expected behaviour: 
//      led off
//      led blinks twice, period approx. 0,75 sec
//      led off
//    ------------------------------------------------------------ */
//
//    outputCompareMatchValue = 255;
//    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//    prescaler = PRESCALER256;
//    myTimer0->setPrescaler(mySemaphorKey, prescaler);
//
//    compareMatchInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer0->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            sei();
//        }
//    }
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    4. timer test - start and stop method LED_PIN0 -> PB0
//    expected behaviour: 
//        led off
//        led on for approx. 2 sec
//        led off
//        led on for approx. 3 sec
//        led off
//    ------------------------------------------------------------ */
//
//    outputCompareMatchValue = 160;
//    myTimer0->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//    prescaler = PRESCALER1024;
//    myTimer0->setPrescaler(mySemaphorKey, prescaler);
//
//    compareMatchInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer0->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            if (loopCounter == 1 && compareMatchInterruptCounter == 0) {
//                myTimer0->stop(mySemaphorKey);
//                _delay_ms(1000UL);
//                myTimer0->start(mySemaphorKey);
//            }
//            sei();
//        }
//
//    }
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    5. PWM test - test changing duty cycle
//    expected behaviour: 
//     LED_PIN0       LED_PIN1
//     off            off
//     not so bright  very bright
//     med. bright    med. bright
//     very bright    not so bright
//     off            off
//    ------------------------------------------------------------ */
//    cli();
//
//    prescaler = PRESCALER64;
//    myTimer0->setPrescaler(mySemaphorKey, prescaler);
//
//    myTimer0->configPwm(mySemaphorKey, LED_PIN0);
//    myTimer0->configPwm(mySemaphorKey, LED_PIN1);
//
//    myTimer0->start(mySemaphorKey);
//
//    myIoHandler.setPinLow(LED_PIN0);
//    myIoHandler.setPinLow(LED_PIN1);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN0, 1);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN1, 100);
//    _delay_ms(2000);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN0, 50);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN1, 50);
//    _delay_ms(2000);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN0, 100);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN1, 1);
//    _delay_ms(2000);
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    myIoHandler.setPinLow(LED_PIN1);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    6. overflow interrupt test 
//    expected behaviour: 
//     LED off
//     LED blinks twice period approx. 2 sec
//     LED off  
//    ------------------------------------------------------------ */
//    myTimer0->stop(mySemaphorKey);
//    prescaler = PRESCALER64;
//    myTimer0->setPrescaler(mySemaphorKey, prescaler);
//
//    myTimer0->configTimerOverflow(mySemaphorKey);
//
//    myIoHandler.setPinLow(LED_PIN4);
//    sei();
//
//    overflowInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer0->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
//            cli();
//            overflowInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN4);
//            loopCounter--;
//            sei();
//        }
//    }
//
//    cli();
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN4);
//    _delay_ms(1000UL);
//
//
//    /*------------------------------------------------------------
//    7. PWM and overflow interrupt test 
//    expected behaviour: 
//        LED_PIN0 and LED_PIN1 dimmed to 50% for the entire test
//        LED_PIN4 blinks twice, period approx 2 sec
//        all three LEDs off
//    ------------------------------------------------------------ */
//
//    prescaler = PRESCALER64;
//
//    myTimer0->setPrescaler(mySemaphorKey, prescaler);
//
//    myTimer0->configTimerOverflow(mySemaphorKey);
//
//    myTimer0->configPwm(mySemaphorKey, LED_PIN0);
//    myTimer0->configPwm(mySemaphorKey, LED_PIN1);
//
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN0, 50);
//    myTimer0->setDutyCycle(mySemaphorKey, LED_PIN1, 50);
//
//    myIoHandler.setPinHigh(LED_PIN4);
//    sei();
//
//    overflowInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer0->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
//            cli();
//            overflowInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN4);
//            loopCounter--;
//            sei();
//        }
//    }
//
//    cli();
//    myTimer0->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    myIoHandler.setPinLow(LED_PIN1);
//    myIoHandler.setPinLow(LED_PIN4);

    //cleaning up
    myTimer0->cleanup(mySemaphorKey);
    mySemaphorKey = myTimer0->pSemaphore.unlock(mySemaphorKey);
    //------------------------------------------------------------------
    // Timer1Attiny85 test cases
    //------------------------------------------------------------------
    Timer1Attiny85* myTimer1 = Timer1Attiny85::getInstance();

    //setup timer    
    mySemaphorKey = myTimer1->pSemaphore.lock();
    myTimer1->configTimerCompareMatch(mySemaphorKey);
    sei();

    /*------------------------------------------------------------
    1. timer test LED_PIN0 -> PB0
    expected behaviour: 
      led off
      led blinks twice, period approx. 3 sec
      led off
    ------------------------------------------------------------ */
//    prescaler = PRESCALER1024;
//    myTimer1->setPrescaler(mySemaphorKey, prescaler);
//    outputCompareMatchValue = 255;
//    compareMatchInterruptCounter = 0;
//    myTimer1->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//    myTimer1->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            sei();
//        }
//    }
//    myTimer1->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    2. timer test - change OCR value LED_PIN0 -> PB0
//    expected behaviour: 
//      led off
//      led blinks twice, period approx. 2 sec
//      led off
//    ------------------------------------------------------------ */
//    outputCompareMatchValue = 160;
//    myTimer1->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//
//    compareMatchInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer1->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            sei();
//        }
//    }
//    myTimer1->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    3. timer test - change prescaler LED_PIN0 -> PB0
//    expected behaviour: 
//      led off
//      led blinks twice, period approx. 0,75 sec
//      led off
//    ------------------------------------------------------------ */
//
//    outputCompareMatchValue = 255;
//    myTimer1->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//    prescaler = PRESCALER256;
//    myTimer1->setPrescaler(mySemaphorKey, prescaler);
//
//    compareMatchInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer1->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            sei();
//        }
//    }
//    myTimer1->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);
//
//    /*------------------------------------------------------------
//    4. timer test - start and stop method LED_PIN0 -> PB0
//    expected behaviour: 
//        led off
//        led on for approx. 2 sec
//        led off
//        led on for approx. 3 sec
//        led off
//    ------------------------------------------------------------ */
//
//    outputCompareMatchValue = 160;
//    myTimer1->setOutputCompareMatchValue(mySemaphorKey, outputCompareMatchValue);
//    prescaler = PRESCALER1024;
//    myTimer1->setPrescaler(mySemaphorKey, prescaler);
//
//    compareMatchInterruptCounter = 0;
//    loopCounter = numberLoopsPerTest;
//    myTimer1->start(mySemaphorKey);
//
//    while (loopCounter) {
//        if (compareMatchInterruptCounter >= interruptCounterThreshold) {
//            cli();
//            compareMatchInterruptCounter = 0;
//            myIoHandler.togglePin(LED_PIN0);
//            loopCounter--;
//            if (loopCounter == 1 && compareMatchInterruptCounter == 0) {
//                myTimer1->stop(mySemaphorKey);
//                _delay_ms(1000UL);
//                myTimer1->start(mySemaphorKey);
//            }
//            sei();
//        }
//
//    }
//    myTimer1->stop(mySemaphorKey);
//    myIoHandler.setPinLow(LED_PIN0);
//    _delay_ms(1000UL);

    /*------------------------------------------------------------
    5. PWM test - test changing duty cycle
    expected behaviour: 
     LED_PIN4       LED_PIN1
     off            off
     not so bright  very bright
     med. bright    med. bright
     very bright    not so bright
     off            off
    ------------------------------------------------------------ */
    cli();

    prescaler = PRESCALER64;
    myTimer1->setPrescaler(mySemaphorKey, prescaler);

    myTimer1->configPwm(mySemaphorKey, LED_PIN4);
    myTimer1->configPwm(mySemaphorKey, LED_PIN1);

    myTimer1->start(mySemaphorKey);

    myIoHandler.setPinLow(LED_PIN4);
    myIoHandler.setPinLow(LED_PIN1);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN4, 1);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN1, 100);
    _delay_ms(2000);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN4, 50);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN1, 50);
    _delay_ms(2000);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN4, 100);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN1, 1);
    _delay_ms(2000);
    myTimer1->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN4);
    myIoHandler.setPinLow(LED_PIN1);
    _delay_ms(1000UL);

    /*------------------------------------------------------------
    6. overflow interrupt test 
    expected behaviour: 
     LED off
     LED blinks twice period approx. 2 sec
     LED off  
    ------------------------------------------------------------ */
    myTimer1->stop(mySemaphorKey);
    prescaler = PRESCALER64;
    myTimer1->setPrescaler(mySemaphorKey, prescaler);

    myTimer1->configTimerOverflow(mySemaphorKey);

    myIoHandler.setPinLow(LED_PIN0);
    sei();

    overflowInterruptCounter = 0;
    loopCounter = numberLoopsPerTest;
    myTimer1->start(mySemaphorKey);

    while (loopCounter) {
        if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
            cli();
            overflowInterruptCounter = 0;
            myIoHandler.togglePin(LED_PIN0);
            loopCounter--;
            sei();
        }
    }

    cli();
    myTimer1->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN0);
    _delay_ms(1000UL);

    /*------------------------------------------------------------
    7. PWM and overflow interrupt test 
    expected behaviour: 
        LED_PIN4 and LED_PIN1 dimmed to 50% for the entire test
        LED_PIN0 blinks twice, period approx 2 sec
        all three LEDs off
    ------------------------------------------------------------ */
    prescaler = PRESCALER64;

    myTimer1->setPrescaler(mySemaphorKey, prescaler);

    myTimer1->configTimerOverflow(mySemaphorKey);

    myTimer1->configPwm(mySemaphorKey, LED_PIN4);
    myTimer1->configPwm(mySemaphorKey, LED_PIN1);

    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN4, 50);
    myTimer1->setDutyCycle(mySemaphorKey, LED_PIN1, 50);

    myIoHandler.setPinHigh(LED_PIN0);
    sei();

    overflowInterruptCounter = 0;
    loopCounter = numberLoopsPerTest;
    myTimer1->start(mySemaphorKey);

    while (loopCounter) {
        if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
            cli();
            overflowInterruptCounter = 0;
            myIoHandler.togglePin(LED_PIN0);
            loopCounter--;
            sei();
        }
    }

    cli();
    myTimer1->stop(mySemaphorKey);
    myIoHandler.setPinLow(LED_PIN0);
    myIoHandler.setPinLow(LED_PIN1);
    myIoHandler.setPinLow(LED_PIN4);

    //cleaning up
    myTimer1->cleanup(mySemaphorKey);
    mySemaphorKey = myTimer1->pSemaphore.unlock(mySemaphorKey);
    
    return 0;
}//int main(void))