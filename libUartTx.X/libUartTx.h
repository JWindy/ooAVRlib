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
//  - delete this section before final commit
//  - implement Uart Tx for integers
//      - check functions of AVR programming book
//  - try to implement Rx with USI as well. Deactivate Rx while sending
//  - implement for other processor speed -> fix BAUD rate?
//  - implement interrupt in ioHandler
//  - extend for Attiny 84
//  - implement state: bussy, idle, error?
//  - implement return value, if transmition not possible
//  - implement tuning algorithm. store OCR0A result in eeprom?
//  - when to use const arg in function call?
//--------------------------------------------------------------------

#ifndef LIBUARTTX_H
#define	LIBUARTTX_H

#define HW_ATtiny85_Default_Debugging_Board

#include <avr/io.h>
#include "ioMapUartTx.h"
#include "libUtility.h"     //v0.1
#include "libIOHandler.h"   //v0.1

//ToDo: implement libs , USI, Timer? and refer here

#ifndef __AVR_ATtiny85__
//    #define TX_PORT PORTB
//    #define TX_DDR  DDRB
    //#define TX_DDR_PIN DDB0
//#else
    #error "Library supports ATtiny 85 only, which is not set in project setup."
#endif

//--------------------------------------------------------------------
//global variables required by ISR
const uint8_t txPin = UART_Tx_PIN;
static volatile uint16_t txShiftReg = 0; 

//--------------------------------------------------------------------
class UartTx{
    public:
//             UartTx(uint8_t argTxPin);
             UartTx(void);
        
//        void uartTxStr(char* argString); //replace by printStr
        //Description:  transmit a string
        
        void printStr(const char* argString);
        void printStrLn (const char* argString);
        
        void printUint8(uint8_t argUint8);
        void printInt8(int8_t argInt8);
        void printUint16(uint16_t argUint16);
        void printInt16(int16_t argInt16);
        
        //ToDo: implement template to transmit any type of number
        //any type of number = [int8, uint8, int16, uint16, int32, uint32]
//        void uartTxInt(uint8_t argInteger);
        //Description:  transmit a 8 bit integer
        
        //ToDo: implement transmition of float as string???
        
    private:        
//        static uint8_t txPin;
//        uint8_t txDdrPin        = 0;
        ver_t   version;
//        static uint8_t txPin;
//        volatile uint16_t tx_shift_reg; 
        
        void uartTxChar(char argCharacter); //replace by transmitByte
        void transmitByte(uint8_t argByte);
        //Description:  transmit one byte
};

#endif	/* LIBUARTTX_H */

