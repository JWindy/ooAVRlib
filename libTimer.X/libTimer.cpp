// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libTimer.h"

namespace nsTimerImpl {

    //--------------------------------------------------------------------------
    //common functions -> accesses no registers directly
    //--------------------------------------------------------------------------

    template <muc_t MUC, timer_type TIMER>
    nsTimerImpl::TimerImpl<MUC, TIMER>::TimerImpl(void) {//Ctor
        version.major = 0;
        version.minor = 2;

        timerState = INIT_STATE;

        prescaler = PRESCALER1024; // see ATiny85 data sheet p80
        outputCompareMatchValueA = 255; //OCR0A data sheet p80
        outputCompareMatchValueB = 255; //OCR0B data sheet p80
        dutyCycle = 100; //in %
        period = 255;
    }

    //explicit instantiation of all templates required to avoid linker error, 
    //caused by definition and declaration of template in two different files. 
    template nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::TimerImpl(void);
    template nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::TimerImpl(void);

    template <muc_t MUC, timer_type TIMER>
    void nsTimerImpl::TimerImpl<MUC, TIMER>::setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            prescaler = argPrescaler;
            if (timerState == BUSSY_STATE) {//update register only, when allready running. Otherwise timer will be started
                setPrescalerRegister();
            }
        }
    }

    template void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler);
    template void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::setPrescaler(uint8_t argSemaphoreKey, clockPrescaler_t argPrescaler);

    template <muc_t MUC, timer_type TIMER>
    void nsTimerImpl::TimerImpl<MUC, TIMER>::start(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            timerState = BUSSY_STATE;
            reset(argSemaphoreKey);
            setPrescalerRegister();
        }
    }

    template void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::start(uint8_t argSemaphoreKey);
    template void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::start(uint8_t argSemaphoreKey);

    template <muc_t MUC, timer_type TIMER>
    void nsTimerImpl::TimerImpl<MUC, TIMER>::configPwmAndTimerOverflow(uint8_t argSemaphoreKey, uint8_t argPin) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            configPwm(argSemaphoreKey, argPin);
            activateOverflowInterrupt(argSemaphoreKey);
        }
    }

    template void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::configPwmAndTimerOverflow(uint8_t argSemaphoreKey, uint8_t argPin);
    template void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::configPwmAndTimerOverflow(uint8_t argSemaphoreKey, uint8_t argPin);

    template <muc_t MUC, timer_type TIMER>
    uint8_t nsTimerImpl::TimerImpl<MUC, TIMER>::calculateDutyCycleRegisterValue(uint8_t argTop) {
        uint8_t dutyCycleResigterValue = (uint8_t) ((uint16_t) argTop * (uint16_t) dutyCycle / 100UL);
        return dutyCycleResigterValue;
    }

    template uint8_t nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::calculateDutyCycleRegisterValue(uint8_t argTop);
    template uint8_t nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::calculateDutyCycleRegisterValue(uint8_t argTop);

    //--------------------------------------------------------------------------
    //Timer0Attiny85 specific functions -> accesses some registers
    //--------------------------------------------------------------------------

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
        //sei() musst be called by the user/application
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argOcrSelect == OCR_A) {
                TIMSK |= (1 << OCIE0A);
                TIMSK &= ~(1 << OCIE0B);
            } else if (argOcrSelect == OCR_B) {
                TIMSK |= (1 << OCIE0B);
                TIMSK &= ~(1 << OCIE0A);
            } else {
                timerState = ERROR_STATE;
            }
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
        //        cli() musst be called by user/application
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argOcrSelect == OCR_A) {
                TIMSK &= ~(1 << OCIE0A);
            } else if (argOcrSelect == OCR_B) {
                TIMSK &= ~(1 << OCIE0B);
            } else {
                timerState = ERROR_STATE;
            }
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::activateOverflowInterrupt(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            TIMSK |= (1 << TOIE0);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::deactivateOverflowInterrupt(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            TIMSK &= ~(1 << TOIE0);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::setOutputCompareMatchValue(uint8_t argSemaphoreKey, ocr_t argOcrSelect, uint8_t argOcrValue) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argOcrSelect == OCR_A) {
                outputCompareMatchValueA = argOcrValue;
                OCR0A = outputCompareMatchValueA;
            } else if (argOcrSelect == OCR_B) {
                outputCompareMatchValueB = argOcrValue;
                OCR0B = outputCompareMatchValueB;
            } else {
                timerState = ERROR_STATE;
            }
            activateOutputCompareMatchInterrupt(argSemaphoreKey, argOcrSelect);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::setPeriod(uint8_t argSemaphoreKey, uint8_t argPeriod) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {//period can't be changed for timer0
            period = argPeriod;
            timerState = ERROR_STATE; //ToDo implement error handling
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::setDutyCycle(uint8_t argSemaphoreKey, uint8_t argPin, uint8_t argDutyCycle) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argDutyCycle > 100)
                dutyCycle = 100;
            else
                dutyCycle = argDutyCycle;
            if (argPin == PB0) {
                OCR0A = calculateDutyCycleRegisterValue(255);
            } else if (argPin == PB1) {
                OCR0B = calculateDutyCycleRegisterValue(255);
            } else {
                timerState = ERROR_STATE;
            }
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::stop(uint8_t argSemaphoreKey) {
        //data sheet p 80
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            timerState = IDLE_STATE;
            TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::reset(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey))
            TCNT0 = 0x00; //reset counter register data sheet p 80
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::cleanup(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
            TCCR0A = 0x00; //reset timer control register data sheet p 80
            TCCR0B = 0x00;
            //reset interrupt mask register data sheet p 81
            TIMSK &= ~((1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0));
            timerState = READY_STATE;
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::configTimerCompareMatch(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (timerState == BUSSY_STATE) {
                stop(argSemaphoreKey);
                reset(argSemaphoreKey);
            }
            if (argOcrSelect == OCR_A) {
                OCR0A = outputCompareMatchValueA;
            } else if (argOcrSelect == OCR_B) {
                OCR0B = outputCompareMatchValueB;
            } else {
                timerState = ERROR_STATE;
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

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::configPwm(uint8_t argSemaphoreKey, uint8_t argPin) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
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
            } else {
                timerState = ERROR_STATE;
            }

            //no compare match interrupt required
            TIMSK &= ~((1 << OCIE0A) | (1 << OCIE0B));

            start(argSemaphoreKey);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>::setPrescalerRegister(void) {
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
                timerState = ERROR_STATE; //ToDo implement error handling
                TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
                break;
        }
    }

    //--------------------------------------------------------------------------
    //Timer1Attiny85 specific functions -> accesses some registers
    //--------------------------------------------------------------------------

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::activateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
        //sei() musst be called by the user/application
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argOcrSelect == OCR_A) {
                TIMSK |= (1 << OCIE1A);
                TIMSK &= ~(1 << OCIE1B);
            } else if (argOcrSelect == OCR_B) {
                TIMSK |= (1 << OCIE1B);
                TIMSK &= ~(1 << OCIE1A);
            } else {
                timerState = ERROR_STATE;
            }
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::deactivateOutputCompareMatchInterrupt(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
        //        cli() musst be called by user/application
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argOcrSelect == OCR_A) {
                TIMSK &= ~(1 << OCIE1A);
            } else if (argOcrSelect == OCR_B) {
                TIMSK &= ~(1 << OCIE1B);
            } else {
                timerState = ERROR_STATE;
            }
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::activateOverflowInterrupt(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            TIMSK |= (1 << TOIE1);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::deactivateOverflowInterrupt(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            TIMSK &= ~(1 << TOIE1);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::setOutputCompareMatchValue(uint8_t argSemaphoreKey, ocr_t argOcrSelect, uint8_t argOcrValue) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argOcrSelect == OCR_A) {
                outputCompareMatchValueA = argOcrValue;
                OCR1A = outputCompareMatchValueA;
                OCR1C = outputCompareMatchValueA;
            } else if (argOcrSelect == OCR_B) {
                outputCompareMatchValueB = argOcrValue;
                OCR1B = outputCompareMatchValueB;
                OCR1C = outputCompareMatchValueB;
            } else {
                timerState = ERROR_STATE;
            }
            activateOutputCompareMatchInterrupt(argSemaphoreKey, argOcrSelect);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::setPeriod(uint8_t argSemaphoreKey, uint8_t argPeriod) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            period = argPeriod;
            OCR1C = period;
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::setDutyCycle(uint8_t argSemaphoreKey, uint8_t argPin, uint8_t argDutyCycle) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (argDutyCycle > 100)
                dutyCycle = 100;
            else
                dutyCycle = argDutyCycle;
            if (argPin == PB1) {
                OCR1A = calculateDutyCycleRegisterValue(period);
            } else if (argPin == PB4) {
                OCR1B = calculateDutyCycleRegisterValue(period);
            } else {
                timerState = ERROR_STATE;
            }
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::stop(uint8_t argSemaphoreKey) {
        //data sheet p 80
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            timerState = IDLE_STATE;
            TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10));
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::reset(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey))
            TCNT1 = 0x00; //reset counter register data sheet p 80
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::cleanup(uint8_t argSemaphoreKey) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            stop(argSemaphoreKey);
            reset(argSemaphoreKey);
            TCCR1 = 0x00; //reset timer control register data sheet p 80
            //reset interrupt mask register data sheet p 81
            TIMSK &= ~((1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1));
            timerState = READY_STATE;
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::configTimerCompareMatch(uint8_t argSemaphoreKey, ocr_t argOcrSelect) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
            if (timerState == BUSSY_STATE) {
                stop(argSemaphoreKey);
                reset(argSemaphoreKey);
            }
            if (argOcrSelect == OCR_A) {
                OCR1C = outputCompareMatchValueA;
                OCR1A = outputCompareMatchValueA;
            } else if (argOcrSelect == OCR_B) {
                OCR1C = outputCompareMatchValueB;
                OCR1B = outputCompareMatchValueB;
            } else {
                timerState = ERROR_STATE;
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

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::configPwm(uint8_t argSemaphoreKey, uint8_t argPin) {
        if (pSemaphore->checkKey(argSemaphoreKey)) {
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
            } else {
                timerState = ERROR_STATE;
            }
            //no compare match interrupt required
            TIMSK &= ~((1 << OCIE0A) | (1 << OCIE0B));
            start(argSemaphoreKey);
        }
    }

    template<>
    void nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>::setPrescalerRegister(void) {
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
                timerState = ERROR_STATE; //ToDo implement error handling
                TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10));
                break;
        }
    }

}//namespace nsTimerImpl