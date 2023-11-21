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
//volatile uint8_t compareMatchInterruptCounter = 0; //global variable for ISR
volatile uint16_t overflowInterruptCounter = 0; //global variable for ISR

//timer0 compare A match interrupt 

ISR(TIM0_COMPA_vect) {
    compareMatchInterruptCounter++;
};

//timer0 compare B match interrupt 

ISR(TIM0_COMPB_vect) {
    compareMatchInterruptCounter++;
    TCNT0 = 0;
}

//timer0 overflow interrupt

ISR(TIM0_OVF_vect) {
    overflowInterruptCounter++;
};



//timer1 compare A match interrupt 

ISR(TIM1_COMPA_vect) {
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
    Timer1Attiny85* myTimer1 = Timer1Attiny85::getInstance();
    libIOHandler myIoHandler;

    //this is cheating, but if the semaphore is locked and unlocked, the 
    //program size exceeds the available program memmory
    uint8_t mySemaphoreKey = 42;

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

    /*List of test cases
    timer0
        compare match 
                1. blink LED_PIN0 - setup and start
                2. timer change OCR value LED_PIN0
                3. timer change prescaler LED_PIN0
                4. timer start and stop method LED_PIN0
        overflow
                10. overflow interrupt test 
        PWM
                20. change duty cycle
                21. PWM and overflow interrupt in parallel
                22. test all prescalers
            
    timer1
        compare match 
                30. blink LED_PIN0 - setup and start
                31. timer change OCR value LED_PIN0
                32. timer change prescaler LED_PIN0
                33. timer start and stop method LED_PIN0
        overflow
                40. overflow interrupt test 
        PWM
                50. change duty cycle
                51. PWM and overflow interrupt in parallel
                52. Change OCR1C/top
                53. test all prescalers
     */

    //select test cases

    //all test cases
        uint8_t testCaseArray[] = {1, 2, 3, 4, //timer0 compare match
            10, //timer0 overflow
            20, 21, 22, //timer0 PWM
            30, 31, 32, 33, 34, //timer1 compare match
            40, //timer1 overflow
            50, 51, 52, 53}; //timer1 PWM
//    uint8_t testCaseArray[] = {53}; 

    uint8_t numberOfTestCases = sizeof (testCaseArray) / sizeof (uint8_t);
    uint8_t testCaseCounter = 0;

    while (testCaseCounter < numberOfTestCases) {
        switch (testCaseArray[testCaseCounter]) {
            case 1:
            {
                /*------------------------------------------------------------
                1. timer test blink LED_PIN0 -> PB0
                expected behaviour: 
                  led off
                  led blinks twice, period approx. 3 sec
                  led off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                compareMatchInterruptCounter = 0;
                prescaler = PRESCALER1024;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);
                outputCompareMatchValue = 255;
                myTimer0->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);
                myTimer0->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 2:
            {
                /*------------------------------------------------------------
                2. timer test - change OCRA value LED_PIN0 -> PB0
                expected behaviour: 
                  led off
                  led blinks twice, period approx. 2 sec
                  led off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                outputCompareMatchValue = 160;
                myTimer0->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);
                prescaler = PRESCALER1024;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);

                myTimer0->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 3:
            {
                /*------------------------------------------------------------
                3. timer test - change prescaler LED_PIN0 -> PB0
                expected behaviour: 
                  led off
                  led blinks twice, period approx. 0,75 sec
                  led off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                outputCompareMatchValue = 255;
                myTimer0->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);
                prescaler = PRESCALER256;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);


                myTimer0->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 4:
            {
                /*------------------------------------------------------------
                4. timer test - start and stop method LED_PIN0 -> PB0
                expected behaviour: 
                    led off
                    led on for approx. 2 sec
                    led off
                    led on for approx. 3 sec
                    led off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                outputCompareMatchValue = 160;
                myTimer0->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);
                prescaler = PRESCALER1024;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);

                myTimer0->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        if (loopCounter == 1 && compareMatchInterruptCounter == 0) {
                            myTimer0->stop(mySemaphoreKey);
                            _delay_ms(1000UL);
                            myTimer0->start(mySemaphoreKey);
                        }
                        sei();
                    }

                }
                //cleaning up
                cli();
                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 10:
            {
                /*------------------------------------------------------------
                10. overflow interrupt test 
                expected behaviour: 
                 LED off
                 LED blinks twice period approx. 2 sec
                 LED off  
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                overflowInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                prescaler = PRESCALER64;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);

                myTimer0->configTimerOverflow(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN4);
                sei();

                while (loopCounter) {
                    if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
                        cli();
                        overflowInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN4);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN4);

                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 20:
            {
                /*------------------------------------------------------------
                20. PWM test - test changing duty cycle
                expected behaviour: 
                 LED_PIN0       LED_PIN1
                 off            off
                 not so bright  very bright
                 med. bright    med. bright
                 very bright    not so bright
                 off            off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                prescaler = PRESCALER64;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);

                myTimer0->configPwm(mySemaphoreKey, LED_PIN0);
                myTimer0->configPwm(mySemaphoreKey, LED_PIN1);


                myIoHandler.setPinLow(LED_PIN0);
                myIoHandler.setPinLow(LED_PIN1);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN0, 1);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN1, 100);
                _delay_ms(2000);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN0, 50);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN1, 50);
                _delay_ms(2000);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN0, 100);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN1, 1);
                _delay_ms(2000);
                //cleaning up
                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myIoHandler.setPinLow(LED_PIN1);
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 21:
            {
                /*------------------------------------------------------------
                21. PWM and overflow interrupt test 
                expected behaviour: 
                    LED_PIN0 and LED_PIN1 dimmed to 50% for the entire test
                    LED_PIN4 blinks twice, period approx 2 sec
                    all three LEDs off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                overflowInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                prescaler = PRESCALER64;
                myTimer0->setPrescaler(mySemaphoreKey, prescaler);

                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN0, 50);
                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN1, 50);

                myTimer0->configPwm(mySemaphoreKey, LED_PIN0);
                myTimer0->configPwm(mySemaphoreKey, LED_PIN1);
                myTimer0->configTimerOverflow(mySemaphoreKey);

                myIoHandler.setPinHigh(LED_PIN4);
                sei();

                while (loopCounter) {
                    if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
                        cli();
                        overflowInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN4);
                        loopCounter--;
                        sei();
                    }
                }

                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myIoHandler.setPinLow(LED_PIN1);
                myIoHandler.setPinLow(LED_PIN4);

                //cleaning up
                cli();
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 22:
            {
                /*------------------------------------------------------------
                22. PWM test all prescalers
                expected behaviour: 
                 LED_PIN0 off
                 LED_PIN0 dimmed for approx. 5x2 sec. LED may not turn off for 2 sec
                 LED_PIN0 off
                ------------------------------------------------------------ */
                //mySemaphoreKey = myTimer0->pSemaphore.lock();

                clockPrescaler_t prescalerArray[] = {PRESCALER1,
                    PRESCALER8,
                    PRESCALER64,
                    PRESCALER256,
                    PRESCALER1024};

                loopCounter = sizeof (prescalerArray) / sizeof (uint8_t);

                myTimer0->setDutyCycle(mySemaphoreKey, LED_PIN0, 50);
                myTimer0->configPwm(mySemaphoreKey, LED_PIN0);

                while (loopCounter) {
                    myTimer0->setPrescaler(mySemaphoreKey, prescalerArray[loopCounter]);
                    _delay_ms(2000);
                    loopCounter--;
                }

                myTimer0->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);

                //cleaning up
                cli();
                myTimer0->cleanup(mySemaphoreKey);
                //mySemaphoreKey = myTimer0->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 30:
            {
                //------------------------------------------------------------------
                // Timer1Attiny85 test cases
                //------------------------------------------------------------------


                /*------------------------------------------------------------
                30. timer test LED_PIN0 -> PB0
                expected behaviour: 
                  led off
                  led blinks twice, period approx. 3 sec
                  led off
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                prescaler = PRESCALER1024;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);
                outputCompareMatchValue = 255;

                myTimer1->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);
                myTimer1->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 31:
            {

                /*------------------------------------------------------------
                31. timer test - change OCR value LED_PIN0 -> PB0
                expected behaviour: 
                  led off
                  led blinks twice, period approx. 2 sec
                  led off
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                prescaler = PRESCALER1024;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);
                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                outputCompareMatchValue = 160;
                myTimer1->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);

                myTimer1->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 32:
            {

                /*------------------------------------------------------------
                32. timer test - change prescaler LED_PIN0 -> PB0
                expected behaviour: 
                  led off
                  led blinks twice, period approx. 0,75 sec
                  led off
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();
                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;
                prescaler = PRESCALER256;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);
                outputCompareMatchValue = 255;
                myTimer1->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);

                myTimer1->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 33:
            {
                /*------------------------------------------------------------
                33. timer test - start and stop method LED_PIN0 -> PB0
                expected behaviour: 
                    led off
                    led on for approx. 2 sec
                    led off
                    led on for approx. 3 sec
                    led off
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                compareMatchInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                prescaler = PRESCALER1024;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);
                outputCompareMatchValue = 160;
                myTimer1->setOutputCompareMatchValue(mySemaphoreKey, outputCompareMatchValue);

                myTimer1->configTimerCompareMatch(mySemaphoreKey);
                sei();

                while (loopCounter) {
                    if (compareMatchInterruptCounter >= interruptCounterThreshold) {
                        cli();
                        compareMatchInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        if (loopCounter == 1 && compareMatchInterruptCounter == 0) {
                            myTimer1->stop(mySemaphoreKey);
                            _delay_ms(1000UL);
                            myTimer1->start(mySemaphoreKey);
                        }
                        sei();
                    }

                }
                //cleaning up
                cli();
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 40:
            {
                /*------------------------------------------------------------
                40. overflow interrupt test 
                expected behaviour: 
                 LED off
                 LED blinks twice period approx. 2 sec
                 LED off  
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                overflowInterruptCounter = 0;

                loopCounter = numberLoopsPerTest;

                prescaler = PRESCALER64;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);

                myTimer1->configTimerOverflow(mySemaphoreKey);

                myIoHandler.setPinLow(LED_PIN0);
                sei();

                while (loopCounter) {
                    if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
                        cli();
                        overflowInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }
                //cleaning up
                cli();
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 50:
            {
                /*------------------------------------------------------------
                50. PWM test - test changing duty cycle
                expected behaviour: 
                 LED_PIN4       LED_PIN1
                 off            off
                 not so bright  very bright
                 med. bright    med. bright
                 very bright    not so bright
                 off            off
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                prescaler = PRESCALER64;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);

                myTimer1->configPwm(mySemaphoreKey, LED_PIN4);
                myTimer1->configPwm(mySemaphoreKey, LED_PIN1);


                myIoHandler.setPinLow(LED_PIN4);
                myIoHandler.setPinLow(LED_PIN1);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN4, 1);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN1, 100);
                _delay_ms(2000);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN4, 50);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN1, 50);
                _delay_ms(2000);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN4, 100);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN1, 1);
                _delay_ms(2000);
                //cleaning up
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN4);
                myIoHandler.setPinLow(LED_PIN1);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 51:
            {
                /*------------------------------------------------------------
                51. PWM and overflow interrupt test 
                expected behaviour: 
                    LED_PIN4 and LED_PIN1 dimmed to 50% for the entire test
                    LED_PIN0 blinks twice, period approx 2 sec
                    all three LEDs off
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                overflowInterruptCounter = 0;
                loopCounter = numberLoopsPerTest;

                prescaler = PRESCALER64;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);

                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN4, 50);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN1, 50);

                myTimer1->configTimerOverflow(mySemaphoreKey);
                myTimer1->configPwm(mySemaphoreKey, LED_PIN4);
                myTimer1->configPwm(mySemaphoreKey, LED_PIN1);

                myIoHandler.setPinHigh(LED_PIN0);
                sei();

                while (loopCounter) {
                    if (overflowInterruptCounter >= overflowInterruptCounterThreshold) {
                        cli();
                        overflowInterruptCounter = 0;
                        myIoHandler.togglePin(LED_PIN0);
                        loopCounter--;
                        sei();
                    }
                }

                //cleaning up
                cli();
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN0);
                myIoHandler.setPinLow(LED_PIN1);
                myIoHandler.setPinLow(LED_PIN4);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 52:
            {
                /*------------------------------------------------------------
                52. Change OCR1C/top
                expected behaviour: 
                LED_PIN4
                 blinks slow period approx. 2 sec
                 blinks fast
                 blinks even faster
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                loopCounter = numberLoopsPerTest;

                myIoHandler.setPinLow(LED_PIN4);

                prescaler = PRESCALER8129;
                myTimer1->setPrescaler(mySemaphoreKey, prescaler);
                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN4, 10);

                myTimer1->configPwm(mySemaphoreKey, LED_PIN4);

                uint8_t period = 255;
                myTimer1->setPeriod(mySemaphoreKey, period);
                _delay_ms(2000);
                period = 170;
                myTimer1->setPeriod(mySemaphoreKey, period);
                _delay_ms(2000);
                period = 85;
                myTimer1->setPeriod(mySemaphoreKey, period);
                _delay_ms(2000);

                //cleaning up
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinLow(LED_PIN4);
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }
            case 53:
            {
                /*------------------------------------------------------------
                53. PWM test all prescalers
                expected behaviour: 
                 LED_PIN4 off
                 LED_PIN4 dimmed for approx. 2x15 sec. LED may not turn off
                 LED_PIN4 off
                 
                 the led will flicker for higher prescaler
                 if something goes wrong, the led will turn off for 2 seconds
                 
                 this test is not testing, if the prescalers are implemented correctly
                 it only shows, that a presacler is found in the switch case. 
                ------------------------------------------------------------ */
                mySemaphoreKey = myTimer1->pSemaphore.lock();

                clockPrescaler_t prescalerArray[] = {PRESCALER1,
                    PRESCALER2,
                    PRESCALER4,
                    PRESCALER8,
                    PRESCALER16,
                    PRESCALER32,
                    PRESCALER64,
                    PRESCALER128,
                    PRESCALER256,
                    PRESCALER512,
                    PRESCALER1024,
                    PRESCALER2048,
                    PRESCALER4096,
                    PRESCALER8129,
                    PRESCALER16384};

                loopCounter = sizeof (prescalerArray) / sizeof (uint8_t);

                myTimer1->setDutyCycle(mySemaphoreKey, LED_PIN4, 50);
                myTimer1->configPwm(mySemaphoreKey, LED_PIN4);

                while (loopCounter) {
                    myTimer1->setPrescaler(mySemaphoreKey, prescalerArray[loopCounter]);
                    _delay_ms(2000);
                    loopCounter--;
                }
                myTimer1->stop(mySemaphoreKey);
                myIoHandler.setPinHigh(LED_PIN4);//to ensure to see a failure of the last prescaler
                _delay_ms(1000);
                myIoHandler.setPinLow(LED_PIN4);

                //cleaning up
                cli();
                myTimer1->cleanup(mySemaphoreKey);
                mySemaphoreKey = myTimer1->pSemaphore.unlock(mySemaphoreKey);
                break;
            }

        }//switch(testCaseArray[testCaseCounter)
        testCaseCounter++;
        _delay_ms(1000UL);
    }//while(testCaseCounter < numberOfTestCases)

    return 0;
}//int main(void))