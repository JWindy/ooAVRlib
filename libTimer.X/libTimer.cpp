// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libTimer.h"

//global declaration of static private members
Timer0Attiny85 Timer0Attiny85::pInstance = Timer0Attiny85();
Timer1Attiny85 Timer1Attiny85::pInstance = Timer1Attiny85();
Semaphore Timer::pSemaphore = Semaphore(1); //initialised as mutex

//------------------------------------------------------------------
// class Timer methods
//------------------------------------------------------------------
Timer::Timer(void) {
    version.major = 0;
    version.minor = 1;

    timerState = INIT_STATE;
};

//------------------------------------------------------------------
// class TimerAttiny85 methods
//------------------------------------------------------------------

TimerAttiny85::TimerAttiny85(void) : Timer() {
};

//------------------------------------------------------------------
// class Timer0Attiny85 methods
//------------------------------------------------------------------

Timer0Attiny85::Timer0Attiny85(void) : TimerAttiny85() {
    prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    outputCompareMatchValue = 255; //OCR0A data sheet p80
    dutyCycle = 100; //in %
};

Timer0Attiny85* Timer0Attiny85::getInstance(void) {
#ifndef __AVR_ATtiny85__
#error "libTimer not implemented for selected MUC."
#endif
    return &pInstance;
}

void Timer0Attiny85::setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        prescaler = argPrescaler;
        if (timerState == BUSSY_STATE) {//update register only, when allready running. Otherwise timer will be started
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

void Timer0Attiny85::configTimerCompareMatch(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        //CTC mode data sheet p 79
        TCCR0B &= ~(1 << WGM02);
        TCCR0A |= (1 << WGM01);
        TCCR0A &= ~(1 << WGM00);

        //normal port operation -> datasheet p 78
        TCCR0A &= ~(1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);
        TCCR0A &= ~(1 << COM0B1);
        TCCR0A &= ~(1 << COM0B0);

        //configure interrupt for OCR0A compare match 
        TIMSK |= (1 << OCIE0A); //sei() musst be called by the client/application
        TIMSK &= ~(1 << OCIE0B);

        start(argSemaphoreKey);
    }
}

void Timer0Attiny85::configTimerOverflow(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        //if neither PWM nor compare match timer is set, set to normal mode
        //otherwise, don't change the setting of the running mode
        if (timerState != BUSSY_STATE) {
            //normal mode data sheet p 79
            TCCR0B &= ~(1 << WGM02);
            TCCR0A &= ~(1 << WGM01);
            TCCR0A &= ~(1 << WGM00);

            //normal port operation -> datasheet p 78
            TCCR0A &= ~(1 << COM0A1);
            TCCR0A &= ~(1 << COM0A0);
            TCCR0A &= ~(1 << COM0B1);
            TCCR0A &= ~(1 << COM0B0);

            timerState = BUSSY_STATE;
        }
        //set overflow interrupt
        TIMSK |= (1 << TOIE0);

        start(argSemaphoreKey);
    }
}

void Timer0Attiny85::setDutyCycle(uint8_t argSemaphoreKey, uint8_t argPin, uint8_t argDutyCycle) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argDutyCycle > 100)
            dutyCycle = 100;
        else
            dutyCycle = argDutyCycle;
        if (argPin == PB0)
            OCR0A = (uint8_t) (255UL * (uint16_t) dutyCycle / 100UL);
        else if (argPin == PB1)
            OCR0B = (uint8_t) (255UL * (uint16_t) dutyCycle / 100UL);
    }
}

void Timer0Attiny85::configPwm(uint8_t argSemaphoreKey, uint8_t argPin) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }

        //config fast PWM , Top = 0xff data sheet p 79
        TCCR0B &= ~(1 << WGM02);
        TCCR0A |= (1 << WGM01);
        TCCR0A |= (1 << WGM00);

        //clear output pin on compare match, set at bottom -> datasheet p 78
        if (argPin == PB0) {
            TCCR0A |= (1 << COM0A1);
            TCCR0A &= ~(1 << COM0A0);
        } else if (argPin == PB1) {
            TCCR0A |= (1 << COM0B1);
            TCCR0A &= ~(1 << COM0B0);
        }

        //no compare match interrupt required
        TIMSK &= ~(1 << OCIE0A);
        TIMSK &= ~(1 << OCIE0B);

        start(argSemaphoreKey);
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
        default://any unavailable prescaler will set the timer to stop
            TCCR0B &= ~(1 << CS02);
            TCCR0B &= ~(1 << CS01);
            TCCR0B &= ~(1 << CS00);
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

        timerState = INIT_STATE;
    }
}

//------------------------------------------------------------------
// class Timer1Attiny85 methods
//------------------------------------------------------------------

Timer1Attiny85::Timer1Attiny85(void) : TimerAttiny85() {
    prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    outputCompareMatchValue = 255; //OCR1A data sheet p91
    dutyCycle = 100; //in %
    period = 255; //PWM mode, OCR1C data sheet p92
};

Timer1Attiny85* Timer1Attiny85::getInstance(void) {
#ifndef __AVR_ATtiny85__
#error "libTimer not implemented for selected MUC."
#endif
    return &pInstance;
}

void Timer1Attiny85::setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        prescaler = argPrescaler;
        if (timerState == BUSSY_STATE) {//update register only, when allready running. Otherwise timer will be started
            setPrescalerRegister();
        }
    }
}

void Timer1Attiny85::setOutputCompareMatchValue(uint8_t argSemaphoreKey, uint8_t argOcrValue) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        outputCompareMatchValue = argOcrValue;
        OCR1A = outputCompareMatchValue; //triggers the compare match interrupt
        OCR1C = outputCompareMatchValue; //triggers the rest of the timer
    }
}

void Timer1Attiny85::configTimerCompareMatch(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        //CTC mode data sheet p 89
        TCCR1 |= (1 << CTC1);

        //normal port operation -> datasheet p 89
        TCCR1 &= ~(1 << COM1A1);
        TCCR1 &= ~(1 << COM1A0);

        //configure interrupt for OCR0A compare match 
        TIMSK |= (1 << OCIE1A); //sei() musst be called by the client/application

        start(argSemaphoreKey);
    }
}

void Timer1Attiny85::configTimerOverflow(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        //if neither PWM nor compare match timer is set, set to normal mode
        //otherwise, don't change the setting of the running mode
        if (timerState != BUSSY_STATE) {
            //CTC mode data sheet p 89
            TCCR1 |= (1 << CTC1);

            OCR1C = 255; //compar match value to reset the counter and trigger the overflow

            //normal port operation -> datasheet p 89
            TCCR1 &= ~(1 << COM1A1);
            TCCR1 &= ~(1 << COM1A0);

            timerState = BUSSY_STATE;
        }
        //set overflow interrupt
        TIMSK |= (1 << TOIE1);

        start(argSemaphoreKey);
    }
}

void Timer1Attiny85::setPeriod(uint8_t argSemaphoreKey, uint8_t argPeriod) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        period = argPeriod;
        OCR1C = period;
    }
}

void Timer1Attiny85::setDutyCycle(uint8_t argSemaphoreKey, uint8_t argPin, uint8_t argDutyCycle) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argDutyCycle > 100)
            dutyCycle = 100;
        else
            dutyCycle = argDutyCycle;
        if (argPin == PB1)
            OCR1A = (uint8_t) (255UL * (uint16_t) dutyCycle / 100UL);
        else if (argPin == PB4)
            OCR1B = (uint8_t) (255UL * (uint16_t) dutyCycle / 100UL);
    }
}

void Timer1Attiny85::configPwm(uint8_t argSemaphoreKey, uint8_t argPin) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        if (argPin == PB1) {
            //config PWM, Top = OCR1C data sheet p 89
            TCCR1 |= (1 << PWM1A);
            //clear output pin on compare match, set at bottom -> datasheet p 78
            TCCR1 |= (1 << COM1A1);
            TCCR1 &= ~(1 << COM1A0);
        } else if (argPin == PB4) {
            //config PWM, Top = OCR1C data sheet p 90
            GTCCR |= (1 << PWM1B);
            //clear output pin on compare match, set at bottom -> datasheet p 78
            GTCCR |= (1 << COM1B1);
            GTCCR &= ~(1 << COM1B0);
        }
        //no compare match interrupt required
        TIMSK &= ~(1 << OCIE0A);
        TIMSK &= ~(1 << OCIE0B);

        start(argSemaphoreKey);
    }
}

void Timer1Attiny85::setPrescalerRegister(void) {
    //data sheet p 89
    switch (prescaler) {
        case PRESCALER1:
            TCCR1 &= ~(1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER2:
            TCCR1 &= ~(1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER4:
            TCCR1 &= ~(1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER8:
            TCCR1 &= ~(1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER16:
            TCCR1 &= ~(1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER32:
            TCCR1 &= ~(1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER64:
            TCCR1 &= ~(1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER128:
            TCCR1 |= (1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER256:
            TCCR1 |= (1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER512:
            TCCR1 |= (1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER1024:
            TCCR1 |= (1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER2048:
            TCCR1 |= (1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER4096:
            TCCR1 |= (1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER8129:
            TCCR1 |= (1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER16384:
            TCCR1 |= (1 << CS13);
            TCCR1 |= (1 << CS12);
            TCCR1 |= (1 << CS11);
            TCCR1 |= (1 << CS10);
            break;
        default:
            TCCR1 &= ~(1 << CS13);
            TCCR1 &= ~(1 << CS12);
            TCCR1 &= ~(1 << CS11);
            TCCR1 &= ~(1 << CS10);
            break;
    }
}

void Timer1Attiny85::start(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        timerState = BUSSY_STATE;
        reset(argSemaphoreKey);
        setPrescalerRegister();
    }
}

void Timer1Attiny85::stop(uint8_t argSemaphoreKey) {
    //data sheet p 89
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        timerState = IDLE_STATE;
        TCCR1 &= ~(1 << CS13);
        TCCR1 &= ~(1 << CS12);
        TCCR1 &= ~(1 << CS11);
        TCCR1 &= ~(1 << CS10);
    }
}

void Timer1Attiny85::reset(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey))
        TCNT1 = 0x00; //reset counter register data sheet p 80
}

void Timer1Attiny85::cleanup(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        stop(argSemaphoreKey);
        reset(argSemaphoreKey);
        TCCR1 = 0x00; //reset timer control register data sheet p 80
        TIMSK &= ~(1 << OCIE1A); //reset interrupt mask register data sheet p 81
        TIMSK &= ~(1 << OCIE1B);
        TIMSK &= ~(1 << TOIE1);

        timerState = INIT_STATE;
    }
}

//------------------------------------------------------------------
// Stuff
//------------------------------------------------------------------

//the following line prevents a linker error
//"undefined reference to `__cxa_pure_virtual'"
extern "C" void __cxa_pure_virtual() {
    while (1);
}