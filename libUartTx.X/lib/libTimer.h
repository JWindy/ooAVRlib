/*--------------------------------------------------------------------
Description:    Hardware proxy to configure, setup, poll and cleanup the timer 
                capabilites of the MUC
                
                The library supports the following modes for timer 0 and timer 1:
                    - Timer compare match mode
                        - can be linked to any pin in user application (ISR) - implemented in SW
                        - set frequency by prescaler and output compare match value
                        - can be configured for OCRxA and OCRxB. However, only one of 
                            both interrupts can be active at a time. -> activate and deactive other timer
                            Activating one compare match interrupt automatically deactivates the other
                        - can't be used in parallel with any other mode
                    - PWM mode
                        - can be linked to PB0 and/or PB1 (timer0) or PB1 and/or PB4 (timer1) - implemented in HW
                        - period for timer0 is determined by prescaler and duty cycle 
                        - period for timer1 is determined by prescaler, duty cycle and period
                        - can't be used in parallel to compare match mode
                        - the frequency of every prescaler has not been verified.
                    - PWM and overflow mode in parallel
                        - anything mentioned on PWM above applies for this mode as well
                        - overflow mode:
                            - can be linked to any pin in user application - implemented in SW
                            - frequency is determined by prescaler only    
                        - timer0: the prescaler sets the period of both modes                    
                        - timer1: prescaler and the parameter period (OCR1C) set the period of both modes
 
                The following features are not (yet) supported: external clock,
                phase corrected PWM mode, assynchronous/fast clocking mode of timer1
                
                Interrupt is enabled for compare match and overflow timer mode. 
                    sei() must be called by the user. 
                    Don't forget to implement ISR.
 
                Initial setup: initialise(), getInstance(), setValues(), configTimer/PWM()
                Change of setup: setValues()
                Change mode: cleanup(), setValues(), configTimer/PWM()
  
Author:         Johannes Windmiller

Dependencies:   either timer0 or timer1 , check #include for required libraries
                PWM is bound by hardware to PB0 and/or PB1 and/or PB4. 
                Compare match timer0 depends on OCR0A or OCR0B, 
                compare match timer1 on (OCR1A or OCR1B) and OCR1C.
 
Version:        v0.2

History:        v0.1    initial implementation
                v0.2    changed polymorphic class to template implementation

Supported MUC:  ATtiny85 @ 8 MHz
 
References:     ATtiny85 datasheet

Comment:        none
 
Copyright:      see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

#ifndef LIBTIMER_H
#define	LIBTIMER_H

#include <avr/io.h>
#include "libUtility.h"	//v0.2

//timer 1 offers many more prescalers than timer 0. 
//The available timer0 prescalers are highlighted
enum clockPrescaler_t {
    PRESCALER1, //timer0
    PRESCALER2,
    PRESCALER4,
    PRESCALER8, //timer0
    PRESCALER16,
    PRESCALER32,
    PRESCALER64, //timer0
    PRESCALER128,
    PRESCALER256, //timer0
    PRESCALER512,
    PRESCALER1024, //default value, timer0
    PRESCALER2048,
    PRESCALER4096,
    PRESCALER8129,
    PRESCALER16384
};

enum ocr_t {
    OCR_A,
    OCR_B
};

enum timer_type {
    TIMER0, //AttinyX5, AttinyX4, AttmegaXX8, AttmegaXXX4
    TIMER1//, //AttinyX5, AttinyX4, AttmegaXX8, AttmegaXXX4
    //TIMER2, //AttmegaXX8, AttmegaXXX4
    //TIMER3  //Attmega 1284 only
};

enum muc_t {
    ATTINYX5//,
    //ATTINYX4,
    //ATMEGAXX8,
    //ATMEGAXXX4
};

namespace nsTimerImpl{

template <muc_t MUC, timer_type TIMER>
class TimerImpl {
public:
    //Activates the output compare match interrupt
    //Deactivates "the other ocr_t" output compare match interrupt
    void activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect);
    //Deactivates the output compare match interrupt
    void deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect);

    //Activates the overflow interrupt
    void activateOverflowInterrupt(uint8_t argSemaphoreKey);
    //Deactivates the overflow interrupt
    void deactivateOverflowInterrupt(uint8_t argSemaphoreKey);
    
    //Change the prescaler, change will be applied immediately.
    //For timer0, only some of the prescalers of clockPrescaler_t are available. 
    //If you choose a prescaler, which is not availble, the timer will not start.
    void setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler);

    //Change the timer compare match value. This determines the period of the timer. 
    //Applies to timer only, not relevant for PWM.
    //Output compare match interrupt is activated.
    //Change will be applied immediately.
    void setOutputCompareMatchValue(uint8_t argSemaphoreKey, ocr_t argOcrSelect, uint8_t argOcrValue);

    //Changes the period [0:255] of both PWM channels. Only available for timer 1.
    //Applies to PWM only, not relevant for timer mode.
    //Change will be applied immediately.
    void setPeriod(uint8_t argSemaphoreKey, uint8_t argPeriod);
    
    //Change the duty cycle [0%:100%] for PWM mode.
    //Applies to PWM only, not relevant for timer
    //Change will be applied immediately.
    void setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle, uint8_t argPin);    
    
    //Rest the counter register of the timer and start the timer/PWM.
    void start(uint8_t argSemaphoreKey);
    
    //Stop the timer/PWM.
    void stop(uint8_t argSemaphoreKey);
    
    //Reset the counter register of the timer.
    void reset(uint8_t argSemaphoreKey);
    
    //Stop the timer and rest all registers to the default values
    //Data members remain unchanged.
    void cleanup(uint8_t argSemaphoreKey);

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes for timer mode.
    //Starts the timer.
    void configTimerCompareMatch(uint8_t argSemaphoreKey, ocr_t argOcrSelect);
    
    //Stop and reset the timer, if running.
    //The overflow mode can only be used in parallel to PWM mode. 
    //Set all parameters according to the private attributes for PWM mode.
    //Frequency of overflow timer is defined by PWM period.
    //Starts the timer.
    void configPwmAndTimerOverflow(uint8_t argSemaphoreKey, uint8_t argPin);

    //Stop and reset the timer, if running.
    //Set all parameters according to the private attributes for PWM mode.
    //Pins bound in hardware to PB0, PB1 and/or PB4 depending on timer0 oder timer1.
    //Starts the timer.
    void configPwm(uint8_t argSemaphoreKey, uint8_t argPin);

    Semaphore* pSemaphore;
    
private:
    TimerImpl(void);
    
    //sets the prescaler register based on the prescaler data member
    void setPrescalerRegister(void);
    
    //calculates the register value based on the data member dutyCycle and on argTop.
    //argTop is the timer count to reset the timer. For timer0 it is 255 by default. 
    //For timer1 it is the data member period
    uint8_t calculateDutyCycleRegisterValue(uint8_t argTop);

    //allows the initialisation function to access the Ctor
    template <muc_t initMUC, timer_type initTimer>
    friend void instansiateObject(char [], uint8_t);

    ver_t version;
    status_t timerState;
    
    clockPrescaler_t prescaler; // see ATiny85 data sheet p80
    uint8_t outputCompareMatchValueA; //OCR0A data sheet p80
    uint8_t outputCompareMatchValueB; //OCR0B data sheet p80
    uint8_t dutyCycle; //in % [0:100]
    uint8_t period; //[0:255]

}; //TimerImpl

template <muc_t initMUC, timer_type initTIMER>
void instansiateObject(char buffer[], uint8_t argNumberOfUsers){
    TimerImpl<initMUC, initTIMER>* tmp = reinterpret_cast<TimerImpl<initMUC, initTIMER>*>(buffer);
    *tmp = TimerImpl<initMUC, initTIMER>();
    tmp->timerState = READY_STATE;

    *tmp->pSemaphore = Semaphore(argNumberOfUsers);
}

}//namespace nsTimerImpl

template<muc_t MUC, timer_type TIMER>
class TimerSingleton{
    public:
        
        //Initialises the singleton object
        //Call this function before using any of its methods. 
        //Calling initialise ensures that the object exists uppon usage. Otherwise
        //undevined behavious might occure, since the compiler can move the 
        //instantiation to a later point in time.
        static void initialise(uint8_t argNumberOfUsers){
            if (refCount == 0){
                nsTimerImpl::instansiateObject<MUC, TIMER>(buffer, argNumberOfUsers);
                refCount = 1;
                }
        }
        
        //Returns the one and only singleton instance of the class
        static nsTimerImpl::TimerImpl<MUC, TIMER>* getInstance(void){
            return (reinterpret_cast<nsTimerImpl::TimerImpl<MUC, TIMER>*>(buffer));
        }

    private:
        TimerSingleton(void);
        static char buffer[sizeof(nsTimerImpl::TimerImpl<MUC, TIMER>)];
        static int refCount;

};

template<muc_t MUC, timer_type TIMER>
char TimerSingleton<MUC, TIMER>::buffer[];

template<muc_t MUC, timer_type TIMER>
int TimerSingleton<MUC, TIMER>::refCount = 0;

//alias
typedef TimerSingleton<ATTINYX5, TIMER0> Timer0Attiny85;
typedef TimerSingleton<ATTINYX5, TIMER1> Timer1Attiny85;
//typedef TimerSingleton<ATTINYX4, TIMER0> Timer0Attiny84;
//typedef TimerSingleton<ATTINYX4, TIMER1> Timer1Attiny84;

#endif	/* LIBTIMER_H */
