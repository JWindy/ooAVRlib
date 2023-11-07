/*--------------------------------------------------------------------
 Description:   Provides a Uart transmition interface implemented in SW only
                supports 8bit binary, int8, uint8, int16, uint16, string
                any kind of floating point and 32-bit numbers are not supported
                Any digital pin can be selected as Tx pin
 
 Author:        Johannes Windmiller
 
 Dependencies:  timer0 compare A match interrupt
 
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
// ToDo: 
//  - implement Singelton
//  - store OCRA in eeprom?
//      - define adress
//      - if value is 0 run the tuning algorithm and use value from source code
//      - if there is a plausible value, use the value and skipp the tuning algorithm
//  - when to use const arg in function call?
//  - implement interrupt in ioHandler
//  - implement for Timer0 and Timer1? -> libTimer
//  - implement libUSI?
//  - compare bit bang implementatation (hackaday) to USI implementation (make)

//  Backlog:
//      - implement for other processor speed -> fix BAUD rate?
//      - extend for Attiny 84
//      - implement return value, if transmition not possible
//  Rx
//      - try to implement Tx with USI as well. Deactivate Rx while sending
//--------------------------------------------------------------------

#ifndef LIBUARTTX_H
#define	LIBUARTTX_H

#define HW_ATtiny85_Default_Debugging_Board

#include <avr/io.h>
#include "ioMapUartTx.h"
#include "libUtility.h"     //v0.1
#include "libIOHandler.h"   //v0.1

#ifndef __AVR_ATtiny85__
    #error "Library supports ATtiny 85 only, which is not set in project setup."
#endif

//--------------------------------------------------------------------
//global variables required by ISR
const uint8_t txPin = UART_Tx_PIN;
static volatile uint16_t txShiftReg = 0; 

//--------------------------------------------------------------------
class UartTx{
    public:
             UartTx(void);
             
        uint8_t getOcr0aValue(void);
        void setOcr0aValue(uint8_t argOcr0aValue);
        
        void printStr(const char* argString);
        void printStrLn (const char* argString);
        void printLn(void);
                
        void printBinaryByte(uint8_t byte);
        
        //must be implemented in header. Otherwise linker error...
        template <typename T> void printNum(T argNum){
            T i = 0;
            T initValue = 1;
            T temp = 0;
            T unsignedValue = argNum;
            uint8_t shiftValueSign = 0;
            uint8_t startTransmission = 0;
            
            switch(sizeof(argNum)){
                case 1://1 byte
                    initValue = 100;
                    if(argNum < 0)
                        shiftValueSign = 7;
                    break;
                case 2://2 byte
                    initValue = (T)10000L;
                    if(argNum < 0)
                        shiftValueSign = 15;
                    break;
        //        default:
                    //how to handel errors?
                    //32-bit integer, float, any other complex data type
                    //break;
            }

            //convert unsigned to signed
            if(shiftValueSign){//shiftValueSign == 0 if unsigned
                if ((unsignedValue & 1 << shiftValueSign) != 0 ){//check if sign is negative
                    transmitByte('-'); 
                    //wrong for -128 and -32768 -> exception handeled below
                    unsignedValue = -unsignedValue;
                }
            }
            if(argNum != -128L && argNum != -32768L)
                for (i = initValue; i >= 1; i/=10){
                    temp = (unsignedValue / i) % 10;
                    if(startTransmission == 0 && temp > 0)//get rid of leading zeros
                        startTransmission = 1;
                    if(startTransmission)
                        transmitByte('0' + temp); 
                }     
            else if(argNum == -128L){//'-' is send futher up the code
                transmitByte('1');
                transmitByte('2');
                transmitByte('8');
            }
            else{
                transmitByte('3');
                transmitByte('2');
                transmitByte('7');
                transmitByte('6');
                transmitByte('8');
            }
        };
        
    private:        
        ver_t   version;
        status_t status;
        uint8_t ocr0aValue;
        
        void transmitByte(uint8_t argByte);
        status_t getStatus(void);
};

#endif	/* LIBUARTTX_H */

