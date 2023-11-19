/*--------------------------------------------------------------------
Description:    Hardware proxy to configure, setup, poll and close the timer 
                capabilites of the MUC
                
                The library supports the following mutually excluding modes 
                for timer 0:
                    - Timer compare match mode
                        - can be linked to any pin in user application - implemented in SW
                        - set frequency by prescaler and output compare match value
                        - can't be used in parallel with any other mode
                    - Overflow mode
                        - can be linked to any pin in user application - implemented in SW
                        - set frequency by prescaler only
                        - I don't see, why this mode would be used instead of timer compare match 
                        - Settings of pwm or compare match timer overrule overflow mode settings
                        - If PWM mode is not active, when calling configOverflowTimer
                          the timer is set to normal mode.  
                        - this mode can be used parallel to PWM mode
                        - can't be used in parallel to timer compare match mode
                    - PWM mode
                        - can be linked to PB0 and/or PB1 - implemented in HW
                        - period is determined by prescaler, duty cycle by the corresponding parameter
                        - can be used in parallel to overflow mode
                    - PWM and overflow mode in parallel
                        - PWM mode and overflow mode can be used simulatenously
                        - the prescaler sets the period of both modes                    
 
                The following features are not (yet) supported: external clock, 
                normal mode, phase corrected PWM mode
                
                Interrupt is enabled for timer mode. sei() must be 
                    called by the user. Don't forget to implement ISR.
 
                Initial setup: getInstance(), setValues(), configTimer/PWM()
                Change of setup: setValues()
                Change mode: stop(), setValues(), configTimer/PWM()
  
Author:         Johannes Windmiller

Dependencies:   either timer0 or timer1 , check #include for required libraries
                PWM is hard coded to toggle PB0 and/or PB1. Timer mode depends 
                on OCA0A.
 
Version:        v0.1

History:        v0.1     initial implementation

Supported MUC:  ATtiny85 @ 8 MHz
 
References:     ATtiny85 datasheet

Comment:        
 
Copyright:      see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

/*ToDo:
 - implement toggle of output in libIOHandler with binary logic XOR???
 - move semaphore test to libUtilityTest
 - design led board and include ioMap.h -> LED on PB0, PB1 & PB3 - breadboard only?
 - implement timer1 
    - additional functions?
    - implement tests
    - implement automated calculation of OCR0A and prescaler depending on given frequency?
   - move semaphore test to libUtility
   - use timer in libUartTx
 */

#ifndef LIBTIMER_H
#define	LIBTIMER_H

#include <avr/io.h>
#include "libUtility.h"	//v0.2

enum clockPrescaler_t {
    PRESCALER1, //default value
    PRESCALER8,
    PRESCALER64,
    PRESCALER256,
    PRESCALER1024
};

class Timer {//abstract class
public:
    //Stop the timer and rest all registers to the default values
    virtual void cleanup(uint8_t argSemaphoreKey) = 0;

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes in timer mode.
    //Starts the timer.
    virtual void configTimerCompareMatch(uint8_t argSemaphoreKey) = 0;

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes in PWM mode.
    //Starts the timer.
    virtual void configPwm(uint8_t argSemaphoreKey, uint8_t argPin) = 0;

    //Rest the counter register of the timer and start the timer/PWM.
    virtual void start(uint8_t argSemaphoreKey) = 0;

    //Stop the timer/PWM.
    virtual void stop(uint8_t argSemaphoreKey) = 0;

    //Reset the counter register of the timer.
    virtual void reset(uint8_t argSemaphoreKey) = 0;

    //The semaphore protects the parallel access to the timer by more then one user.
    static Semaphore pSemaphore;

protected:
    ver_t version;
    status_t timerState;

    Timer(void); //class implemented as singleton -> constructor not accessible by user
}; //Timer

class TimerAttiny85 : public Timer {//abstract class
public:
    //Change the prescaler, change will be applied immediately.
    virtual void setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler) = 0;

    //Change the timer compare match value. This determines the period of the timer. 
    //Change will be applied immediately.
    virtual void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue) = 0;

    //Change the duty cycle for PWM mode.
    //Change will be applied immediately.
    virtual void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle, uint8_t argPin) = 0;

protected:
    clockPrescaler_t prescaler; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue; //OCR0A data sheet p80
    uint8_t dutyCycle; //in %

    TimerAttiny85(void);
    //Changes the register according to the member attribute
    virtual void setPrescalerRegister(void) = 0;
}; //TimerAttiny85

class Timer0Attiny85 : public TimerAttiny85 {
public:
    //returns the one and only singleton instance
    //gives access to all other public methods
    static Timer0Attiny85* getInstance(void);

    //Stop the timer and rest all registers to the default values
    void cleanup(uint8_t argSemaphoreKey);

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes in timer mode.
    //Starts the timer.
    void configTimerCompareMatch(uint8_t argSemaphoreKey);

    //The overflow mode is intended to be used in parallel to the PWM mode. 
    //If used independently, compare match timer gives more options for configuration
    //If used in parallel to PWM, calling configTimerOverflow only sets the 
    //overflow interrupt. If used independently, parameters are set acoording to 
    //private attributes, timer is set to normal mode
    //Starts the timer.
    void configTimerOverflow(uint8_t argSemaphoreKey);

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes in PWM mode.
    //Starts the timer.
    void configPwm(uint8_t argSemaphoreKey, uint8_t argPin);

    //Rest the counter register of the timer and start the timer/PWM.
    void start(uint8_t argSemaphoreKey);
    //Stop the timer/PWM.
    void stop(uint8_t argSemaphoreKey);
    //Reset the counter register of the timer.
    void reset(uint8_t argSemaphoreKey);

    //Change the prescaler, change will be applied immediately.
    void setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler);

    //Change the timer compare math value. This determines the period of the timer. 
    //Applies to timer only, not relevant for PWM
    //Change will be applied immediately.
    void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue);

    //Change the duty cycle for PWM mode.
    //Applies to PWM only, not relevant for timer
    //Change will be applied immediately.
    void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle, uint8_t argPin);

protected:
    Timer0Attiny85(void);
    void setPrescalerRegister(void);

private:
    static Timer0Attiny85 pInstance;
}; //Timer0Attiny85

class Timer1Attiny85 : public TimerAttiny85 {
public:
    static Timer1Attiny85* getInstance(void);

protected:
    Timer1Attiny85(void);

private:

}; //Timer1Attiny85

#endif	/* LIBTIMER_H */

