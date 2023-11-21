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

uint8_t TimerAttiny85::calculateDutyCycleRegisterValue(uint8_t argTop) {
    uint8_t dutyCycleResigerValue = (uint8_t) ((uint16_t) argTop * (uint16_t) dutyCycle / 100UL);
    return dutyCycleResigerValue;
}

//------------------------------------------------------------------
// class Timer0Attiny85 methods
//------------------------------------------------------------------

Timer0Attiny85::Timer0Attiny85(void) : TimerAttiny85() {
    prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    outputCompareMatchValueA = 255; //OCR0A data sheet p80
    outputCompareMatchValueB = 255; //OCR0B data sheet p80
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

void Timer0Attiny85::setOutputCompareMatchValue(uint8_t argSemaphoreKey, ocr_t argOcrSelect, uint8_t argOcrValue) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argOcrSelect == OCR_A) {
            outputCompareMatchValueA = argOcrValue;
            OCR0A = outputCompareMatchValueA;
        } else if (argOcrSelect == OCR_B) {
            outputCompareMatchValueB = argOcrValue;
            OCR0B = outputCompareMatchValueB;
        }
        activateOutputCompareMatchInterrupt(argSemaphoreKey, argOcrSelect);
    }
}

void Timer0Attiny85::activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
    //sei() musst be called by the user/application
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argOcrSelect == OCR_A) {
            TIMSK |= (1 << OCIE0A);
            TIMSK &= ~(1 << OCIE0B);
        } else if (argOcrSelect == OCR_B) {
            TIMSK |= (1 << OCIE0B);
            TIMSK &= ~(1 << OCIE0A);
        }
    }
}

void Timer0Attiny85::deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
    //        cli() musst be called by user/application
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argOcrSelect == OCR_A) {
            TIMSK &= ~(1 << OCIE0A);
        } else if (argOcrSelect == OCR_B) {
            TIMSK &= ~(1 << OCIE0B);
        }
    }
}

void Timer0Attiny85::activateOverflowInterrupt(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        TIMSK |= (1 << TOIE0);
    }
}

void Timer0Attiny85::deactivateOverflowInterrupt(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        TIMSK &= ~(1 << TOIE0);
    }
}

void Timer0Attiny85::configTimerCompareMatch(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        if (argOcrSelect == OCR_A) {
            OCR0A = outputCompareMatchValueA;
        } else if (argOcrSelect == OCR_B) {
            OCR0B = outputCompareMatchValueB;
        }

        //CTC mode data sheet p 79
        TCCR0B &= ~((1 << WGM02) | (1 << WGM00));
        TCCR0A |= (1 << WGM01);

        //normal port operation -> datasheet p 78
        TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));

        activateOutputCompareMatchInterrupt(argSemaphoreKey, argOcrSelect);
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
            TCCR0A &= ~((1 << WGM01) | (1 << WGM00));

            //normal port operation -> datasheet p 78
            TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));

            timerState = IDLE_STATE;
        }
        activateOverflowInterrupt(argSemaphoreKey);

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
            OCR0A = calculateDutyCycleRegisterValue(255);
        else if (argPin == PB1)
            OCR0B = calculateDutyCycleRegisterValue(255);
    }
}

void Timer0Attiny85::configPwm(uint8_t argSemaphoreKey, uint8_t argPin) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }

        setDutyCycle(argSemaphoreKey, argPin, dutyCycle);

        //config fast PWM , Top = 0xff data sheet p 79
        TCCR0B &= ~(1 << WGM02);
        TCCR0A |= ((1 << WGM01) | (1 << WGM00));

        //clear output pin on compare match, set at bottom -> datasheet p 78
        if (argPin == PB0) {
            TCCR0A |= (1 << COM0A1);
            TCCR0A &= ~(1 << COM0A0);
        } else if (argPin == PB1) {
            TCCR0A |= (1 << COM0B1);
            TCCR0A &= ~(1 << COM0B0);
        }

        //no compare match interrupt required
        TIMSK &= ~((1 << OCIE0A) | (1 << OCIE0B));

        start(argSemaphoreKey);
    }
}

void Timer0Attiny85::setPrescalerRegister(void) {
    //data sheet p 80
    switch (prescaler) {
        case PRESCALER1:
            TCCR0B &= ~((1 << CS02) | (1 << CS01));
            TCCR0B |= (1 << CS00);
            break;
        case PRESCALER8:
            TCCR0B &= ~((1 << CS02) | (1 << CS00));
            TCCR0B |= (1 << CS01);
            break;
        case PRESCALER64:
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= ((1 << CS01) | (1 << CS00));
            break;
        case PRESCALER256:
            TCCR0B |= (1 << CS02);
            TCCR0B &= ~((1 << CS01) | (1 << CS00));
            break;
        case PRESCALER1024:
            TCCR0B |= ((1 << CS02) | (1 << CS00));
            TCCR0B &= ~(1 << CS01);
            break;
        default://any unavailable prescaler will set the timer to stop
            TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
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
        TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
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
        //reset interrupt mask register data sheet p 81
        TIMSK &= ~((1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0));
        timerState = INIT_STATE;
    }
}

//------------------------------------------------------------------
// class Timer1Attiny85 methods
//------------------------------------------------------------------

Timer1Attiny85::Timer1Attiny85(void) : TimerAttiny85() {
    prescaler = PRESCALER1024; // see ATiny85 data sheet p80
    outputCompareMatchValueA = 255; //OCR1A data sheet p91
    outputCompareMatchValueB = 255; //OCR1B data sheet p91
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

void Timer1Attiny85::setOutputCompareMatchValue(uint8_t argSemaphoreKey, ocr_t argOcrSelect, uint8_t argOcrValue) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argOcrSelect == OCR_A) {
            outputCompareMatchValueA = argOcrValue;
            OCR1A = outputCompareMatchValueA;
            OCR1C = outputCompareMatchValueA;
        } else if (argOcrSelect == OCR_B) {
            outputCompareMatchValueB = argOcrValue;
            OCR1B = outputCompareMatchValueB;
            OCR1C = outputCompareMatchValueB;
        }
        activateOutputCompareMatchInterrupt(argSemaphoreKey, argOcrSelect);
    }
}

void Timer1Attiny85::activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
    //sei() musst be called by the user/application    
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argOcrSelect == OCR_A) {
            TIMSK |= (1 << OCIE1A);
            TIMSK &= ~(1 << OCIE1B);
        } else if (argOcrSelect == OCR_B) {
            TIMSK |= (1 << OCIE1B);
            TIMSK &= ~(1 << OCIE1A);
        }
    }
}

void Timer1Attiny85::deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
    //cli() musst be called by the user/application    
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (argOcrSelect == OCR_A) {
            TIMSK &= ~(1 << OCIE1A);
        } else if (argOcrSelect == OCR_B) {
            TIMSK &= ~(1 << OCIE1B);
        }
    }
}

void Timer1Attiny85::activateOverflowInterrupt(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        TIMSK |= (1 << TOIE1);
    }
}

void Timer1Attiny85::deactivateOverflowInterrupt(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        TIMSK &= ~(1 << TOIE1);
    }
}

void Timer1Attiny85::configTimerCompareMatch(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }
        if (argOcrSelect == OCR_A) {
            OCR1C = outputCompareMatchValueA;
            OCR1A = outputCompareMatchValueA;
        } else if (argOcrSelect == OCR_A) {
            OCR1C = outputCompareMatchValueB;
            OCR1B = outputCompareMatchValueB;
        }

        //CTC mode data sheet p 89
        TCCR1 |= (1 << CTC1);

        //normal port operation -> datasheet p 89
        TCCR1 &= ~((1 << COM1A1) | (1 << COM1A0));
        GTCCR &= ~((1 << COM1B1) | (1 << COM1B0));

        activateOutputCompareMatchInterrupt(argSemaphoreKey, argOcrSelect);
        start(argSemaphoreKey);
    }
}

void Timer1Attiny85::configTimerOverflow(uint8_t argSemaphoreKey) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        //if neither PWM nor compare match timer is set, set to normal mode
        //otherwise, don't change the setting of the running mode
        if (timerState != BUSSY_STATE) {

            //normal mode data sheet p 89
            TCCR1 &= ~((1 << CTC1) | (1 << PWM1A));

            period = 255;
            OCR1C = period; //compar match value to reset the counter and trigger the overflow

            //normal port operation -> datasheet p 89
            TCCR1 &= ~((1 << COM1A1) | (1 << COM1A0));
            GTCCR &= ~((1 << COM1B1) | (1 << COM1B0));

            timerState = IDLE_STATE;
        }
        activateOverflowInterrupt(argSemaphoreKey);
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
            OCR1A = calculateDutyCycleRegisterValue(period);
        else if (argPin == PB4)
            OCR1B = calculateDutyCycleRegisterValue(period);
    }
}

void Timer1Attiny85::configPwm(uint8_t argSemaphoreKey, uint8_t argPin) {
    if (pSemaphore.checkKey(argSemaphoreKey)) {
        if (timerState == BUSSY_STATE) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
        }

        setDutyCycle(argSemaphoreKey, argPin, dutyCycle);

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
        TIMSK &= ~((1 << OCIE0A) | (1 << OCIE0B));

        start(argSemaphoreKey);
    }
}

void Timer1Attiny85::setPrescalerRegister(void) {
    //data sheet p 89
    switch (prescaler) {
        case PRESCALER1:
            TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS11));
            TCCR1 |= (1 << CS10);
            break;
        case PRESCALER2:
            TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS10));
            TCCR1 |= (1 << CS11);
            break;
        case PRESCALER4:
            TCCR1 &= ~((1 << CS13) | (1 << CS12));
            TCCR1 |= ((1 << CS11) | (1 << CS10));
            break;
        case PRESCALER8:
            TCCR1 &= ~((1 << CS13) | (1 << CS11) | (1 << CS10));
            TCCR1 |= (1 << CS12);
            break;
        case PRESCALER16:
            TCCR1 &= ~((1 << CS13) | (1 << CS11));
            TCCR1 |= ((1 << CS12) | (1 << CS10));
            break;
        case PRESCALER32:
            TCCR1 &= ~((1 << CS13) | (1 << CS10));
            TCCR1 |= ((1 << CS12) | (1 << CS11));
            break;
        case PRESCALER64:
            TCCR1 &= ~(1 << CS13);
            TCCR1 |= ((1 << CS12) | (1 << CS11) | (1 << CS10));
            break;
        case PRESCALER128:
            TCCR1 |= (1 << CS13);
            TCCR1 &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
            break;
        case PRESCALER256:
            TCCR1 |= ((1 << CS13) | (1 << CS10));
            TCCR1 &= ~((1 << CS12) | (1 << CS11));
            break;
        case PRESCALER512:
            TCCR1 |= ((1 << CS13) | (1 << CS11));
            TCCR1 &= ~((1 << CS12) | (1 << CS10));
            break;
        case PRESCALER1024:
            TCCR1 |= ((1 << CS13) | (1 << CS11) | (1 << CS10));
            TCCR1 &= ~(1 << CS12);
            break;
        case PRESCALER2048:
            TCCR1 |= ((1 << CS13) | (1 << CS12));
            TCCR1 &= ~((1 << CS11) | (1 << CS10));
            break;
        case PRESCALER4096:
            TCCR1 |= ((1 << CS13) | (1 << CS12) | (1 << CS10));
            TCCR1 &= ~(1 << CS11);
            break;
        case PRESCALER8129:
            TCCR1 |= ((1 << CS13) | (1 << CS12) | (1 << CS11));
            TCCR1 &= ~(1 << CS10);
            break;
        case PRESCALER16384:
            TCCR1 |= ((1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10));
            break;
        default://timer stopped
            TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10));
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
        TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10));
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
        //reset interrupt mask register data sheet p 81
        TIMSK &= ~((1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1));
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