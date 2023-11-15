/*--------------------------------------------------------------------
Description:    Hardware proxy to configure, setup, poll and close the timer 
                capabilites of the MUC
                The following features are not (yet) supported: external clock, 
                normal mode, phase corrected PWM mode, compare match output mode,
                any OCR0B features, timer overflow interrupt
                Interrupt is enabled for timer and PWM mode. sei() must be 
                    called by the user
  
Author:         Johannes Windmiller

Dependencies:   either timer0 or timer1 , check #include for required libraries
 
Version:        v0.1

History:        v0.1     initial implementation

Supported MUC:  ATtiny85 @ 8 MHz
 
References:     

Comment:        
 
Copyright:      see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

/*ToDo:
 - implement test for timer
 - implement test for pwm
 - implement comment for every function
 - implement destuctor and delete function -> return 0-pointer?
 - implement automated calculation of OCR0A and prescaler depending on given frequency?
 - decide, if timer can be configured more simple -> timerMode? two classes? PWM and timer? accessing the same HW???
    //how many parameters are required for setup?
    //can the parameters be used for both PWM and timer
    //mode = 0 -> PWM, mode = 1 -> timer
    //frequ -> for both
    //duty cycle -> for PWM only
 
 */

#ifndef LIBTIMER_H
#define	LIBTIMER_H

#include <avr/io.h>
#include "libUtility.h"	//v0.2

//enum timerMode_t{
//    TIMER_MODE,
//    PWM_MODE
//};

enum clockPrescaler_t {
    PRESCALER1, //default value
    PRESCALER8,
    PRESCALER64,
    PRESCALER256,
    PRESCALER1024
};

class Timer {//abstract class
public:
    virtual void cleanup(uint8_t argSemaphoreKey) = 0;

    virtual void configTimer(uint8_t argSemaphoreKey) = 0;
    virtual void configPwm(uint8_t argSemaphoreKey) = 0;

    virtual void start(uint8_t argSemaphoreKey) = 0;
    virtual void stop(uint8_t argSemaphoreKey) = 0;
    virtual void reset(uint8_t argSemaphoreKey) = 0;

    Semaphore* pSemaphore; //{1};//extended initializer lists only available with -std=c++11 or -std=gnu++11

protected:
    ver_t version;
    status_t timerState;

    Timer(void);
}; //Timer

class TimerAttiny85 : public Timer {//abstract class
public:
    virtual void setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler) = 0;
    virtual void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue) = 0;
    virtual void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle) = 0;

protected:
    clockPrescaler_t prescaler; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValue; //OCR0A data sheet p80
    uint8_t dutyCycle; //in %

    TimerAttiny85(void);
    virtual void setPrescalerRegister(void) = 0;
}; //TimerAttiny85

//inherit from abstrac clas

class Timer0Attiny85 : public TimerAttiny85 {
public:
    static Timer0Attiny85* getInstance(void);

    void cleanup(uint8_t argSemaphoreKey);

    void configTimer(uint8_t argSemaphoreKey);
    void configPwm(uint8_t argSemaphoreKey);

    void start(uint8_t argSemaphoreKey);
    void stop(uint8_t argSemaphoreKey);
    void reset(uint8_t argSemaphoreKey);

    void setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler);
    void setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue);
    void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle);

protected:
    Timer0Attiny85(void);
    void setPrescalerRegister(void);

private:
    //        void activateSynchronisationMode(void);
    //        void deactivateSynchronisationMode(void);
    static Timer0Attiny85 pInstance;


}; //Timer0Attiny85

class Timer1Attiny85 : public TimerAttiny85 {
public:
    static Timer1Attiny85* getInstance(void);

protected:
    Timer1Attiny85(void);

private:

}; //Timer1Attiny85

/*
                                timer0          timer1
 modes
 normal - no clear on match     1
 clear on compare match (CTC)   1
 
 
 fct                            
 timer                          1
 clear timer on compare match   1
 PWM                            1
 register interrupt             1
 adjust duty cycle (PWM)        1
 
 performance:
 #output compare register       2
 #interrupt sources ?           3
 */


#endif	/* LIBTIMER_H */

