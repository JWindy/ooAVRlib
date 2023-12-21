/*--------------------------------------------------------------------
 Description:   Provides a Uart transmition interface implemented in SW only
                Implemented as singelton -> there can only be one instance of 
                    the class. If created again, the adress of the existing 
                    object is returned.
                Supports 8bit binary, int8, uint8, int16, uint16, string
                Any kind of floating point and 32-bit numbers are not supported
                Any digital pin can be selected as Tx pin
                While sending data, the library blocks the CPU. Keep strings short!
 
 Author:        Johannes Windmiller
 
 Dependencies:  timer0 compare A match interrupt, UART to USB adapter
 
 Version:       v0.1
 
 History:       v0.1     Initial implementation
 
 Supported MUC: ATtiny85 @ 8 MHz, 9600 BAUD rate
 
 References:    http://www.technoblogy.com/show?RPY -> Rx? 
                accessed on 25.10.2023
                https://hackaday.com/2019/03/13/attiny-gets-a-tiny-software-uart/ 
                accessed on 25.10.2023
                Elliot Williams, Make: AVR Programming p81ff, Make Media 2014    
 
 Comment:       I'm well aware, that there is a T in UART for transmit;), but 
                I need to destinguish between the Tx and the TxRx library 
                somehow. Calling one UAT and the other UART would be ambigous.
 
 Copyright:     see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

//--------------------------------------------------------------------
/* ToDo: 
  - replace switch case in template to constexp
  - pass timer as argument to Ctor?
  - replace stop and reset timer in ISR by class function -> declare ISR as friend of the class
  - store OCRA in eeprom?
      - define adress
      - if value is 0 run the tuning algorithm and use value from source code
      - if there is a plausible value, use the value and skip the tuning algorithm

//--------------------------------------------------------------------*/

#ifndef LIBUARTTX_H
#define	LIBUARTTX_H

#define HW_ATtiny85_Default_Debugging_Board

#include <avr/io.h>
#include "ioMapUartTx.h"
#include "libUtility.h"     //v0.2
#include "libIOHandler.h"   //v0.1
#include "libTimer.h"       //v0.2

#define timer0 //comment to select timer1

#ifndef timer0
#define timer1
#endif

#ifndef __AVR_ATtiny85__
#error "Library supports ATtiny 85 only, which is not set in project setup."
#endif

//--------------------------------------------------------------------
//global variables required by ISR -> ToDo try to define ISR as friend to class and get rid of global variable
const uint8_t txPin = UART_Tx_PIN;
static volatile uint16_t txShiftReg = 0;

//--------------------------------------------------------------------

template <typename T>
class UartTxSingleton;

namespace nsUartTxImpl {

    class UartTxImpl {
    public:
        void setOcrValue(uint8_t argOcrValue);

        void printStr(const char* argString);
        void printStrLn(const char* argString);
        void printLn(void);

        void printBinaryByte(uint8_t argByte);

        //must be defined in header. Otherwise linker error...

        template <typename T> void printNum(T argNum) {
            T i = 0;
            T initValue = 1;
            T temp = 0;
            T unsignedValue = argNum;
            uint8_t shiftValueSign = 0;
            uint8_t startTransmission = 0;

            switch (sizeof (argNum)) {
                case 1://1 byte
                    initValue = 100;
                    if (argNum < 0)
                        shiftValueSign = 7;
                    break;
                case 2://2 byte
                    initValue = (T) 10000L;
                    if (argNum < 0)
                        shiftValueSign = 15;
                    break;
                    //        default:
                    //how to handel errors?
                    //32-bit integer, float, any other complex data type
                    //break;
            }

            //convert unsigned to signed
            if (shiftValueSign) {//shiftValueSign == 0 if unsigned
                if ((unsignedValue & 1 << shiftValueSign) != 0) {//check if sign is negative
                    transmitByte('-');
                    //wrong for -128 and -32768 -> exception handeled below
                    unsignedValue = -unsignedValue;
                }
            }
            if (argNum != -128L && argNum != -32768L)
                for (i = initValue; i >= 1; i /= 10) {
                    temp = (unsignedValue / i) % 10;
                    if (startTransmission == 0 && temp > 0)//get rid of leading zeros
                        startTransmission = 1;
                    if (startTransmission)
                        transmitByte('0' + temp);
                } else if (argNum == -128L) {//'-' is send futher up the code
                transmitByte('1');
                transmitByte('2');
                transmitByte('8');
            } else {
                transmitByte('3');
                transmitByte('2');
                transmitByte('7');
                transmitByte('6');
                transmitByte('8');
            }
        };

        Semaphore* pSemaphore;

        IOHandler* pIOHandler;

    private:
        UartTxImpl(uint8_t argNumberOfUser);

        //allows the initialisation function to access the Ctor
        friend class UartTxSingleton<nsUartTxImpl::UartTxImpl>;

        ver_t version;
        status_t uartTxState;

        uint8_t ocrValue;

        void transmitByte(uint8_t argByte);
        status_t getStatus(void);
        uint8_t timerKey;

#ifdef timer0 //ToDo pass timer to instantiateObject and forward to Ctor
        nsTimerImpl::TimerImpl<ATTINYX5, TIMER0>* myTimer;
#endif
#ifdef timer1
        nsTimerImpl::TimerImpl<ATTINYX5, TIMER1>* myTimer;
#endif

    }; //UartTxImpl

}//namespace UartTxImpl

template <typename T>
class UartTxSingleton {
public:

    //Initialises the singleton object
    //Call this function before using any of its methods. 
    //Calling initialise ensures that the object exists upon usage. Otherwise
    //undevined behavious might occure, since the compiler can move the 
    //instantiation to a later point in time.

    static void initialiseUartTx(uint8_t argNumberOfUsers) {
        if (refCount == 0) {
            T* tmp = reinterpret_cast<T*> (buffer);
            *tmp = nsUartTxImpl::UartTxImpl(argNumberOfUsers);
            tmp->uartTxState = READY_STATE;

            *tmp->pSemaphore = Semaphore(argNumberOfUsers);
            *tmp->pIOHandler = IOHandler();
            refCount = 1;
        }
    }

    //Returns the one and only singleton instance of the class

    static T* getInstance(void) {
        return (reinterpret_cast<T*> (buffer));
    }

private:
    UartTxSingleton(void);
    static char buffer[sizeof (T)];
    static uint8_t refCount;
};

template<typename T>
char UartTxSingleton<T>::buffer[];

template<typename T>
uint8_t UartTxSingleton<T>::refCount = 0;

typedef UartTxSingleton<nsUartTxImpl::UartTxImpl> UartTx;

#endif	/* LIBUARTTX_H */