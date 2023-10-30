

#include "ioMapUartTx.h"
#include "libUartTx.h"

#define BAUD 9600

#ifndef F_CPU
    #define F_CPU 8000000
#endif

#ifndef __AVR_ATtiny85__
    #define __AVR_ATtiny85__
#endif

#define HW_ATtiny85_Default_Debugging_Board

int main(void){
    
    char testString[]   = "Hello World!";
    uint8_t testUint8   = 100;
    int8_t testInt8     = -100;
    
    //intantiate object
    UartTx myUartTx;
    
    //send string
    myUartTx.uartTxStr(testString);
    _delay_ms(100);
    
    //send integer
    myUartTx.uartTx(testUint8);
    _delay_ms(100);
    
    myUartTx.uartTx(testInt8);
    _delay_ms(100);
    return 0;
}