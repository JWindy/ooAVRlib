// testing application for libUartTx
// copyright applies according to LICENSE_software.md in GitHub root folder

#include <util/delay.h>
#include "libUartTx.h"

#ifndef BAUD
#    define BAUD 9600
#endif

#ifndef F_CPU
#    define F_CPU 8000000
#endif

#ifndef __AVR_ATtiny85__
#    define __AVR_ATtiny85__
#endif

int main(void) {

    const char testString[] = "Hello World!";
    const char testNewLine[] = "Test new line";
    const uint8_t binaryByte = 0b10101010;
    const uint8_t testUint8 = 10;
    const uint8_t testUint8_2 = 255;
    const int8_t testInt8 = -128;
    const int8_t testInt8_2 = testInt8 + 1;
    const int8_t testInt8_3 = 127;
    
    const uint16_t testUint16 = 65535UL;
    const int16_t testInt16 = -32768L;
    const int16_t testInt16_2 = testInt16 + 1;
    const int16_t testInt16_3 = 32767L;

    const uint8_t ocrInitValue = 103;

    const uint8_t numberOfUser = 1;

    UartTx::initialiseUartTx(numberOfUser);

    auto myUartTx = UartTx::getInstance();

    auto myUartTx2 = UartTx::getInstance();

    myUartTx->setOcrValue(103);
    _delay_ms(3000);

    myUartTx->printLn();
    myUartTx->printLn();
    //    while (1) {
    myUartTx->printStrLn("New test session started");
    //    }
    myUartTx->printLn();

    myUartTx->printStrLn("Tune timer interrupt");
    uint8_t i = 5;
    uint8_t newOcrValue = ocrInitValue - i / 2 - 1;
    while (i--) {
        newOcrValue = newOcrValue + 1;
        myUartTx->setOcrValue(newOcrValue);
        myUartTx->printStr("This is a test string for OCR = ");
        myUartTx->printNum(newOcrValue);
        myUartTx->printLn();
        //_delay_ms(500);
    }

    myUartTx->setOcrValue(102);

    myUartTx->printLn();
    myUartTx->printStrLn("Test printStr");
    myUartTx->printStr(testString);
    myUartTx->printLn();
    myUartTx->printStrLn("printStrLn");
    myUartTx->printStrLn(testNewLine);
    //_delay_ms(100);

    myUartTx->printStrLn("printBinaryByte");
    myUartTx->printBinaryByte(binaryByte);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printStrLn("Test printNum(uint8_t)");
    myUartTx->printNum(testUint8);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printNum(testUint8_2);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printStrLn("Test printNum(int8_t)");
    myUartTx->printNum(testInt8);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printNum(testInt8_2);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printNum(testInt8_3);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printStrLn("Test printNum(uint16_t)");
    myUartTx->printNum(testUint16);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx->printStrLn("Test printNum(int16_t)");
    myUartTx->printNum(testInt16);
    myUartTx->printLn();
    //_delay_ms(100);
    myUartTx->printNum(testInt16_2);
    myUartTx->printLn();
    //_delay_ms(100);
    myUartTx->printNum(testInt16_3);
    myUartTx->printLn();
    //_delay_ms(100);

    myUartTx2->printStrLn("Send by '2nd' instance ");
    //_delay_ms(100);

    myUartTx->printLn();
    myUartTx->printStrLn("Test completed");
    myUartTx->printStrLn("-----------------------------------");
    myUartTx->printLn();

    //_delay_ms(2000);    

    return 0;
}