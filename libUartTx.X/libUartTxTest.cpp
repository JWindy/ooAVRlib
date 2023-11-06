// testing application for libUartTx
// copyright applies according to LICENSE_software.md in GitHub root folder

#include <util/delay.h>
#include "libUartTx.h"


#ifndef BAUD
    #define BAUD 9600
#endif

#ifndef F_CPU
    #define F_CPU 8000000
#endif

#ifndef __AVR_ATtiny85__
    #define __AVR_ATtiny85__
#endif

int main(void){
    
    char testString[]   = "Hello World!";
    char testNewLine[]  = "new line";
    uint8_t testUint8   = 100;
//    int8_t testInt8     = -100;
//    uint16_t testUint16 = 300;
    
    //intantiate object
//    UartTx myUartTx(UART_Tx_PIN);
    UartTx myUartTx;
    
    _delay_ms(3000);
    
    while(1){
        //send string
//        myUartTx.uartTxStr(testString);
//        _delay_ms(100);
        
        myUartTx.printStr(testString);
        myUartTx.printStrLn(testNewLine);
        _delay_ms(100);
                
        //send uint8
        myUartTx.printUint8(testUint8);
        _delay_ms(100);

        //send uint16
//        myUartTx.printUint16(testUint16);
//        _delay_ms(100);

    //    myUartTx.uartTxChar(testInt8);
    //    _delay_ms(100);
        _delay_ms(2000);    
    }
    return 0;
}