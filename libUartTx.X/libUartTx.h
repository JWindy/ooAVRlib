/*--------------------------------------------------------------------
 Description:   Provides a Uart transmition interface based on the 
                USI interface
  
 Author:        Johannes Windmiler
 
 Dependencies:  libIOHandler, USI, Timer? //ToDo: implement libs and refer here
 
 Version:       v0.0.1
 
 History:       v0.0.1     Initial implementation
 
 Supported MUC: ATtiny85
 
 References:    http://www.technoblogy.com/show?RPY -> Rx? 
                accessed on 25.10.2023
                https://hackaday.com/2019/03/13/attiny-gets-a-tiny-software-uart/ 
                accessed on 25.10.2023
 
 Comment:       I'm well aware, that there is a T in UART for transmit;), but 
                I need to destinguish between the Tx and the TxRx library 
                somehow. Calling one UAT and the other UART would be ambigous.
 
 Copyright:     see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

//--------------------------------------------------------------------
// ToDo: 
//  - delete this section before final commit
//  - replace TX_PIN with global variable ???
//  - implement Uart Tx für strings and integers
//      - check functions of AVR programming book
//  - try to implement Rx with USI as well. Deactivate Rx while sending
//  - extend for Attiny 84
//--------------------------------------------------------------------

#ifndef LIBUARTTX_H
#define	LIBUARTTX_H

//move to ioMappingUartTxAttiny85.h
uint8_t txPin = PB0;

#ifndef __AVR_ATtiny85__
//    #define TX_PORT PORTB
//    #define TX_DDR  DDRB
    //#define TX_DDR_PIN DDB0
//#else
    #error "Library supports ATtiny 85 only, which is not set in project setup."
#endif

//--------------------------------------------------------------------
volatile uint16_t tx_shift_reg = 0; //global to be available for ISR

//--------------------------------------------------------------------
class UartTx{
    public:
        void init(void);
        void uartTx(char argCharacter);
        //Description:  transmitt one character
        
        void uartTxStr(char* argString);
        //Description:  transmitt a string
        
        void uartTxInt(uint8 argInteger);
        //Description:  transmitt a 8 bit integer
        
    private:        
        //uint8_t txPin       = 0;
        uint8_t txDdrPin    = 0;
};

#endif	/* LIBUARTTX_H */

