/*--------------------------------------------------------------------
Description:    Hardware proxy to configure, setup, poll and close the timer 
                capabilites of the MUC
                
                The library supports the following modes 
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
                        - can be linked to PB0 and/or PB1 and/or PB4 - implemented in HW
                        - period is determined by prescaler, duty cycle by the corresponding parameter
                        - can be used in parallel to overflow mode
                        - the frequency for every prescaler has not been verified. 
                            Verify, if important
                    - PWM and overflow mode in parallel
                        - PWM mode and overflow mode can be used simulatenously
                        - the prescaler sets the period of both modes                    
 
                The following features are not (yet) supported: external clock,
                phase corrected PWM mode, assynchronous/fast clocking mode of timer1
                
                Interrupt is enabled for compare match and overflow timer mode. 
                    sei() must be called by the user. 
                    Don't forget to implement ISR.
 
                Initial setup: getInstance(), setValues(), configTimer/PWM()
                Change of setup: setValues()
                Change mode: cleanup(), setValues(), configTimer/PWM()
  
Author:         Johannes Windmiller

Dependencies:   either timer0 or timer1 , check #include for required libraries
                PWM is hard coded to toggle PB0 and/or PB1 and/or PB4. 
                Compare match timer0 depends on OCR0A, 
                compare match timer1 on OCR1A and OCR1C.
 
Version:        v0.1

History:        v0.1     initial implementation

Supported MUC:  ATtiny85 @ 8 MHz
 
References:     ATtiny85 datasheet

Comment:        
 
Copyright:      see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

//ToDo 
//  add OCR0B again and reset TCNT=0 in ISR
//  apply to libUartTx

#ifndef LIBTIMER_H
#define	LIBTIMER_H

#include <avr/io.h>
#include "libUtility.h"	//v0.2

//timer 1 offers many more prescalers than timer 0. 
//The available timer0 prescalers are highlighted

enum clockPrescaler_t {
    PRESCALER1, //default value, timer0
    PRESCALER2,
    PRESCALER4,
    PRESCALER8, //timer0
    PRESCALER16,
    PRESCALER32,
    PRESCALER64, //timer0
    PRESCALER128,
    PRESCALER256, //timer0
    PRESCALER512,
    PRESCALER1024, //timer0
    PRESCALER2048,
    PRESCALER4096,
    PRESCALER8129,
    PRESCALER16384
};

//enum ocr_t {
//    OCR_A,
//    OCR_B
//};

class Timer {//abstract class
public:
    //Stop the timer and rest all registers to the default values
    virtual void cleanup(uint8_t argSemaphoreKey) = 0;

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes in timer mode.
    //Starts the timer.
    virtual void configTimerCompareMatch(uint8_t argSemaphoreKey) = 0;

    //The overflow mode is intended to be used in parallel to the PWM mode. 
    //If used independently, compare match timer gives more options for configuration
    //If used in parallel to PWM, calling configTimerOverflow only sets the 
    //overflow interrupt. If used independently, parameters are set acoording to 
    //private attributes, timer is set to normal mode
    //Starts the timer.
    virtual void configTimerOverflow(uint8_t argSemaphoreKey) = 0;

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes in PWM mode.
    //Pins bound in hardware to PB0 and PB1
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
    //Applies to timer only, not relevant for PWM
    //Output compare match interrupt is activated.
    //Change will be applied immediately.
    virtual void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue) = 0;

//    //Activates the output compare match interrupt
//    //Deactivates the output compare match of "the other"  output compare match interrupt
//    virtual void activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) = 0;
//    //Deactivates the output compare match interrupt
//    virtual void deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) = 0;

//     //Activates the overflow interrupt
//    virtual void activateOverflowInterrupt(uint8_t argSemaphoreKey) = 0;
//    //Deactivates the overflow interrupt
//    virtual void deactivateOverflowInterrupt(uint8_t argSemaphoreKey) = 0;
    
    //Change the duty cycle for PWM mode.
    //Change will be applied immediately.
    virtual void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle, uint8_t argPin) = 0;

protected:
    clockPrescaler_t prescaler; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue; //OCR0A data sheet p80
//    uint8_t outputCompareMatchValueB; //OCR0B data sheet p80
    uint8_t dutyCycle; //in %

    TimerAttiny85(void);
    //Changes the register according to the member attribute
    virtual void setPrescalerRegister(void) = 0;
    uint8_t calculateDutyCycleRegisterValue(uint8_t argTop);
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
    //Pins bound in hardware to PB1 and PB4
    //Starts the timer.
    void configPwm(uint8_t argSemaphoreKey, uint8_t argPin);

    //Rest the counter register of the timer and start the timer/PWM.
    void start(uint8_t argSemaphoreKey);
    //Stop the timer/PWM.
    void stop(uint8_t argSemaphoreKey);
    //Reset the counter register of the timer.
    void reset(uint8_t argSemaphoreKey);

    //Change the prescaler, change will be applied immediately.
    //For timer0, only some of the prescalers of clockPrescaler_t are available. 
    //If you choose a prescaler, which is not availble, the timer will not start.
    void setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler);

    //Change the timer compare match value. This determines the period of the timer. 
    //Applies to timer only, not relevant for PWM
    //Output compare match interrupt is activated.
    //Change will be applied immediately.
    void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue);
//
//    //Activates the output compare match interrupt
//    //Deactivates the output compare match of "the other"  output compare match interrupt
//    void activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect);
//    //Deactivates the output compare match interrupt
//    void deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect);
//
//    //Activates the overflow interrupt
//    void activateOverflowInterrupt(uint8_t argSemaphoreKey);
//    //Deactivates the overflow interrupt
//    void deactivateOverflowInterrupt(uint8_t argSemaphoreKey);
//    
    //Change the duty cycle [%] for PWM mode.
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
    //returns the one and only singleton instance
    //gives access to all other public methods
    static Timer1Attiny85* getInstance(void);

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

    //Change the timer compare match value. This determines the period of the timer. 
    //Applies to timer only, not relevant for PWM
    //Output compare match interrupt is activated.
    //Change will be applied immediately..
    void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue);
//
//    //Activates the output compare match interrupt
//    //Deactivates the output compare match of "the other"  output compare match interrupt
//    void activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect);
//    //Deactivates the output compare match interrupt
//    void deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect);
//
//    //Activates the overflow interrupt
//    void activateOverflowInterrupt(uint8_t argSemaphoreKey);
//    //Deactivates the overflow interrupt
//    void deactivateOverflowInterrupt(uint8_t argSemaphoreKey);
    
    //Changes the duty cycle [0:255] of both PWM channels.
    //Applies to PWM only, not relevant for timer
    //Change will be applied immediately.
    void setPeriod(uint8_t argSemaphoreKey, uint8_t argPeriod);

    //Change the duty cycle for PWM mode.
    //Applies to PWM only, not relevant for timer
    //Change will be applied immediately.
    void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle, uint8_t argPin);

protected:
    Timer1Attiny85(void);
    void setPrescalerRegister(void);

private:
    static Timer1Attiny85 pInstance;
    uint8_t period;

}; //Timer1Attiny85

#endif	/* LIBTIMER_H */

