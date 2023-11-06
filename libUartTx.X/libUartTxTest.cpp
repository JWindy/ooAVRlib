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
    
    const char      testString[]    = "Hello World!";
    const char      testNewLine[]   = "Test new line";
    const uint8_t   binaryByte      = 0b10101010;   
    const uint8_t   testUint8       = 10;
    const uint8_t   testUint8_2     = 255;
    const int8_t    testInt8        = -123;
    const int8_t    testInt8_2      = 123;
    const uint16_t  testUint16      = 3000UL;
    const int16_t   testInt16       = -300L;
    const int16_t   testInt16_2     = 30L;
    
    UartTx myUartTx;
    
    _delay_ms(3000);
    
    myUartTx.printLn();
    myUartTx.printLn();
    myUartTx.printStrLn("New test session started");
    
    while(1){
        
        myUartTx.printStrLn("Test printStr");
        myUartTx.printStr(testString);
        myUartTx.printLn();
        myUartTx.printStrLn("printStrLn");
        myUartTx.printStrLn(testNewLine);
        _delay_ms(100);

        myUartTx.printStrLn("printBinaryByte");
        myUartTx.printBinaryByte(binaryByte);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printStrLn("Test printNum(uint8_t)");
        myUartTx.printNum(testUint8);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printNum(testUint8_2);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printStrLn("Test printNum(int8_t)");
        myUartTx.printNum(testInt8);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printNum(testInt8_2);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printStrLn("Test printNum(uint16_t)");
        myUartTx.printNum(testUint16);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printStrLn("Test printNum(int16_t)");
        myUartTx.printNum(testInt16);
        myUartTx.printLn();
        _delay_ms(100);
        myUartTx.printNum(testInt16_2);
        myUartTx.printLn();
        _delay_ms(100);
        
        myUartTx.printLn();
        myUartTx.printStrLn("Test completed");
        myUartTx.printStrLn("-----------------------------------");
        myUartTx.printLn();
        
        _delay_ms(2000);    
    }
    return 0;
}