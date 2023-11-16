// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libTimer.h"
//#include <avr/interrupt.h>
//#include <stdlib.h> //for malloc()

//global declaration of static private members
Timer0Attiny85 Timer0Attiny85::pInstance = Timer0Attiny85();
Semaphore Timer::pSemaphore = Semaphore(1); //initialised as mutex

//void Timer::init(void){
//    #ifndef __AVR_ATtiny85__
//        #error "libIOHandler not implemented for selected MUC."
//    #endif
//
//    version.major = 0;
//    version.minor = 1;
//    
//}

//------------------------------------------------------------------
// class Timer operations
//------------------------------------------------------------------
//Timer* Timer::getInstance(void){
//   if (pInstance == 0){
//       pInstance = (Timer*)malloc(sizeof(Timer));
//       pInstance->init();
//   }
//   return pInstance;
//}
//Timer::Timer(void): Semaphore(1){

Timer::Timer(void) {
    version.major = 0;
    version.minor = 1;

    timerState = INIT_STATE;

    //    *pSemaphore = Semaphore(1); //initialised as mutex

};
//------------------------------------------------------------------
// class TimerAttiny85 operations
//------------------------------------------------------------------

TimerAttiny85::TimerAttiny85(void) : Timer() {
};
//------------------------------------------------------------------
// class Timer0Attiny85 operations
//------------------------------------------------------------------

Timer0Attiny85::Timer0Attiny85(void) : TimerAttiny85() {
    prescaler = PRESCALER1; // see ATiny85 data sheet p80
    outputCompareMatchValue = 255; //OCR0A data sheet p80
    dutyCycle = 100; //in %
};

Timer0Attiny85* Timer0Attiny85::getInstance(void) {
#ifndef __AVR_ATtiny85__
#error "libIOHandler not implemented for selected MUC."
#endif
    return &pInstance;
}

void Timer0Attiny85::setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        prescaler = argPrescaler;
        if(timerState == BUSSY_STATE){//update register only, when allready running. Otherwise timer will be started
            setPrescalerRegister();
        }
    }
}

void Timer0Attiny85::setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        outputCompareMatchValue = argOcrValue;
        OCR0A = outputCompareMatchValue;
    }
}

void Timer0Attiny85::setDutyCycle(uint8_t argSemaphoreKey, uint8_t argDutyCycle) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argDutyCycle > 100)
            dutyCycle = 100;
        else
            dutyCycle = argDutyCycle;
    }
    //ToDo: update duty cycle in register
}

void Timer0Attiny85::configTimer(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        //CTC mode data sheet p 79
        TCCR0A &= ~(1 << WGM02);
        TCCR0A |= (1 << WGM01);
        TCCR0B &= ~(1 << WGM00);

        //normal port operation -> datasheet p 78
        TCCR0A &= ~(1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);

        OCR0A = outputCompareMatchValue;

        //configure interrupt
        TIMSK |= (1 << OCIE0A); //sei() musst be called by the client/application
        TIMSK &= ~(1 << OCIE0B);
        TIMSK &= ~(1 << TOIE0);
    }
}

void Timer0Attiny85::configPwm(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        //config fast PWM , Top = OCR0A data sheet p 79
        TCCR0A |= (1 << WGM02);
        TCCR0A |= (1 << WGM01);
        TCCR0B |= (1 << WGM00);

        //clear output pin on compare match, set at bottom -> datasheet p 78
        TCCR0A |= (1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);

        OCR0A = (uint8_t) (255UL * (uint16_t) dutyCycle / 100UL);

        //configure interrupt
        TIMSK |= (1 << OCIE0A); //sei() musst be called by the client/application
        TIMSK &= ~(1 << OCIE0B);
        TIMSK |= (1 << TOIE0);
    }
}

void Timer0Attiny85::setPrescalerRegister(void) {
    //data sheet p 80
    switch (prescaler) {
        case PRESCALER1:
            TCCR0B &= ~(1 << CS02);
            TCCR0B &= ~(1 << CS01);
            TCCR0B |= (1 << CS00);
            break;
        case PRESCALER8:
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= (1 << CS01);
            TCCR0B &= ~(1 << CS00);
            break;
        case PRESCALER64:
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= (1 << CS01);
            TCCR0B |= (1 << CS00);
            break;
        case PRESCALER256:
            TCCR0B |= (1 << CS02);
            TCCR0B &= ~(1 << CS01);
            TCCR0B &= ~(1 << CS00);
            break;
        case PRESCALER1024:
            TCCR0B |= (1 << CS02);
            TCCR0B &= ~(1 << CS01);
            TCCR0B |= (1 << CS00);
            break;
    }
}

void Timer0Attiny85::start(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        timerState = BUSSY_STATE;
        reset(argSemaphoreKey);
        setPrescalerRegister();
    }
}

void Timer0Attiny85::stop(uint8_t argSemaphoreKey) {
    //data sheet p 80
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        timerState = IDLE_STATE;
        TCCR0B &= ~(1 << CS02);
        TCCR0B &= ~(1 << CS01);
        TCCR0B &= ~(1 << CS00);
    }
}

void Timer0Attiny85::reset(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey))
        TCNT0 = 0x00; //reset counter register data sheet p 80
}

void Timer0Attiny85::cleanup(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        stop(argSemaphoreKey);
        reset(argSemaphoreKey);
        TCCR0A = 0x00; //reset timer control register data sheet p 80
        TCCR0B = 0x00;
        TIMSK &= ~(1 << OCIE1A); //reset interrupt mask register data sheet p 81
        TIMSK &= ~(1 << OCIE1B);
        TIMSK &= ~(1 << TOIE0);
    }
}


//void Timer0Attiny85::activateSynchronisationMode(void){
//    //see datasheet p 77
//    GTCCR |= (1 << TSM);
//}
//void Timer0Attiny85::deactivateSynchronisationMode(void){
//    GTCCR &= ~(1 << TSM);
//}

//------------------------------------------------------------------
// class Timer1Attiny85 operations
//------------------------------------------------------------------

//void Timer1Attiny85::init(void) {
//#ifndef __AVR_ATtiny85__
//#error "libIOHandler not implemented for selected MUC."
//#endif
//
//    version.major = 0;
//    version.minor = 1;
//
//}

//the following line prevents a linker error
//"undefined reference to `__cxa_pure_virtual'"

extern "C" void __cxa_pure_virtual() {
    while (1);
}