// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libUartTx.h"
#include <avr/interrupt.h>

#ifndef LIBUARTTX_CPP
#    define	LIBUARTTX_CPP

//timer0 compare A match interrupt
#    ifdef timer0

ISR(TIM0_COMPA_vect) {
    uint8_t sregTemp = SREG;
    uint16_t localTxShiftReg = txShiftReg;
    //output LSB of the TX shift register at the TX pin
    if (localTxShiftReg & 0x01) {
        PORTB |= (1 << txPin);
    } else {
        PORTB &= ~(1 << txPin);
    }
    //shift the TX shift register one bit to the right
    localTxShiftReg >>= 1;
    txShiftReg = localTxShiftReg;
    //if the stop bit has been sent, the shift register will be 0
    //and the transmission is completed, so we can stop & reset timer0
    if (!localTxShiftReg) {
        TCCR0B = 0; //stop timer //ToDo replace by calling timer data member, after defining ISR as friend
        TCNT0 = 0; //reset timer counter //Todo test, if required
        //        TCCR0B = 0;
        //        TCNT0 = 0;
    }
    SREG = sregTemp;
};
#    endif

ISR(TIM0_OVF_vect) { //ToDo delete
    TCNT0 = 0;
}

//timer1 compare A match interrupt
#    ifdef timer1

ISR(TIM1_COMPA_vect) {
    uint8_t sregTemp = SREG;
    uint16_t localTxShiftReg = txShiftReg;
    //output LSB of the TX shift register at the TX pin
    if (localTxShiftReg & 0x01) {
        PORTB |= (1 << txPin);
    } else {
        PORTB &= ~(1 << txPin);
    }
    //shift the TX shift register one bit to the right
    localTxShiftReg >>= 1;
    txShiftReg = localTxShiftReg;
    //if the stop bit has been sent, the shift register will be 0
    //and the transmission is completed, so we can stop & reset timer0
    if (!localTxShiftReg) { //ToDo replace by calling timer data member, after defining ISR as friend
        TCCR1 &= ~((1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10)); //stop timer
        TCNT1 = 0x00; //reset timer counter //Todo test, if required

        //        TCCR0B = 0;
        //        TCNT0 = 0;
    }
    SREG = sregTemp;
};
#    endif  

namespace nsUartTxImpl {

    nsUartTxImpl::UartTxImpl::UartTxImpl(uint8_t argNumberOfUser) {//Ctor
        version.major = 0;
        version.minor = 1;

        uartTxState = INIT_STATE;

        pIOHandler->setPinOutput(txPin);

#    ifdef timer0 //ToDo pass timer to instantiateObject and forward to Ctor. Otherwise change NumberOfUsers!
        Timer0Attiny85::initialise(argNumberOfUser);
        myTimer = Timer0Attiny85::getInstance();
#    endif
#    ifdef timer1
        Timer1Attiny85::initialise(argNumberOfUser);
        myTimer = Timer1Attiny85::getInstance();
#    endif

        timerKey = 0;
        while (!timerKey) {//loop endlessly, if timer is locked by other user
            timerKey = myTimer->pSemaphore->lock();
        }

        //set compare value to 103 to achieve a 9600 baud rate (i.e. 104µs)
        //together with the 8MHz/8=1MHz timer clock*/
        /*NOTE: since the internal 8MHz oscillator is not very accurate, this value can be tuned
          to achieve the desired baud rate, so if it doesn't work with the nominal value (103), try
          increasing or decreasing the value by 1 or 2 */
        ocrValue = 103;
        myTimer->setOutputCompareMatchValue(timerKey, OCR_A, ocrValue);
        myTimer->setPrescaler(timerKey, PRESCALER8);
        myTimer->configTimerCompareMatch(timerKey, OCR_A);
        myTimer->stop(timerKey);

        //        //set timer0 to CTC mode
        //        TCCR0A = (1 << WGM01);
        //
        //        //        enable output compare 0 A interrupt
        //        TIMSK |= (1 << OCF0A);

        uartTxState = IDLE_STATE;

        //enable interrupts
        sei();

    }

    void UartTxImpl::setOcrValue(uint8_t argOcrValue) {
        ocrValue = argOcrValue;
        myTimer->setOutputCompareMatchValue(timerKey, OCR_A, argOcrValue);
        //            OCR0A = ocrValue;
    }

    status_t UartTxImpl::getStatus() {
        sei();
        const uint8_t localTxShiftReg = txShiftReg;
        cli();

        if (uartTxState != ERROR_STATE) {
            if (localTxShiftReg)
                uartTxState = BUSSY_STATE;
            else
                uartTxState = IDLE_STATE;
        }
        return uartTxState;
    };

    void UartTxImpl::transmitByte(uint8_t argByte) {
        //wait until transmission is finished
        //this might lead to a crash in the proramm, if for some reason, 
        //the transmittion is never completed. ToDo Timeout?
        while (getStatus() == BUSSY_STATE);

        //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
        uint16_t localTxShiftReg = (argByte << 1) | (1 << 9); //stop bit (1<<9)

        cli();
        txShiftReg = localTxShiftReg;
        myTimer->start(timerKey);
        //            TCCR0B = (1 << CS01); //start timer0 with a prescaler of 8
        sei();
    };

    void UartTxImpl::printStr(const char* argString) {
        while (*argString) {
            transmitByte(*argString++);
        }
    };

    void UartTxImpl::printStrLn(const char* argString) {
        printStr(argString);
        printLn();
    };

    void UartTxImpl::printLn(void) {
        printStr("\n\r");
    };

    void UartTxImpl::printBinaryByte(uint8_t argByte) {
        /* Prints out a byte as a series of 1's and 0's */
        uint8_t bit;
        for (bit = 7; bit < 255; bit--) {
            if (bit_is_set(argByte, bit))
                transmitByte('1');
            else
                transmitByte('0');
        }
    };

}//namespace nsUartTxImpl

#endif