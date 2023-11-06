/*--------------------------------------------------------------------
 Description:   Provides a Uart transmition interface based on the 
                USI interface
  
 Author:        Johannes Windmiller
 
 Dependencies:  timer0 compare A match interrupt
 
 Version:       v0.1
 
 History:       v0.1     Initial implementation
 
 Supported MUC: ATtiny85
 
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
//  - compare bit bang implementatation to USI implementation
//  - try to implement Rx with USI as well. Deactivate Rx while sending
//  - implement for other processor speed -> fix BAUD rate?
//  - implement interrupt in ioHandler
//  - extend for Attiny 84
//  - implement return value, if transmition not possible
//  - implement tuning algorithm. store OCR0A result in eeprom?
//  - when to use const arg in function call?
//  - replace code duplicates for different variable size by template?
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
        
        void printStr(const char* argString);
        void printStrLn (const char* argString);
        void printLn(void);
                
        void printBinaryByte(uint8_t byte);
        
        void printNum(uint8_t argUint8);
        void printNum(int8_t argInt8);
        void printNum(uint16_t argUint16);
        void printNum(int16_t argInt16);       
        
    private:        
        ver_t   version;
        status_t status;
        
        void transmitByte(uint8_t argByte);
        status_t getStatus(void);
};

#endif	/* LIBUARTTX_H */

