// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libUartTx.h"
#include <avr/interrupt.h>

//UartTx::UartTx(uint8_t argTxPin){
UartTx::UartTx(void){
    libIOHandler myIOHandler;
    
    myIOHandler.setPinOutput(txPin);
    
//    txPin = UART_Tx_PIN;
//    tx_shift_reg = 0; 
    
    version.major = 0;
    version.minor = 1;
    
    #if  (BAUD != 9600)
        #error "Uart Tx implemented for BAUD = 9600 only!"
    #endif
    
    //moved to IO Handler
    //set TX pin as output
    //TX_DDR |= (1 << txDdrPin);
   //TX_PORT |= (1 << txPin);
    
    //set timer0 to CTC mode
    TCCR0A = (1 << WGM01);
    
    //enable output compare 0 A interrupt
    TIMSK |= (1 << OCF0A);
    
    //set compare value to 103 to achieve a 9600 baud rate (i.e. 104µs)
    //together with the 8MHz/8=1MHz timer0 clock*/
    /*NOTE: since the internal 8MHz oscillator is not very accurate, this value can be tuned
      to achieve the desired baud rate, so if it doesn't work with the nominal value (103), try
      increasing or decreasing the value by 1 or 2 */
    OCR0A = 105;
    
    //enable interrupts
    sei();   
    
    /* original code
    //set TX pin as output
   TX_DDR |= (1<<TX_DDR_PIN);
   TX_PORT |= (1<<TX_PIN);
   //set timer0 to CTC mode
   TCCR0A = (1<<WGM01);
   //enable output compare 0 A interrupt
   TIMSK0 |= (1<<OCF0A);
   //set compare value to 103 to achieve a 9600 baud rate (i.e. 104µs)
   //together with the 8MHz/8=1MHz timer0 clock*/
   /*NOTE: since the internal 8MHz oscillator is not very accurate, this value can be tuned
     to achieve the desired baud rate, so if it doesn't work with the nominal value (103), try
     increasing or decreasing the value by 1 or 2 */
    /*
   OCR0A = 103;
   //enable interrupts
   sei();
   */
};

void UartTx::uartTxChar(char argCharacter){//replace by transmitByte
    //ToDo: disable interrupt?
   uint16_t localTxShiftReg = txShiftReg;
   
   //if sending the previous character is not yet finished, return
   //transmission is finished when tx_shift_reg == 0
   if(localTxShiftReg){return;}//ToDo: enable interrupt?
   
   //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
   localTxShiftReg = (argCharacter<<1) | (1<<9); //stop bit (1<<9)
   txShiftReg = localTxShiftReg;
   
   //start timer0 with a prescaler of 8
   TCCR0B = (1<<CS01);
   //ToDo: enable interrupt?
};

//void UartTx::uartTxStr(char* argString){ //replace by printStr
//    while( *argString ){
//        uartTxChar( *argString++ );
//        
//        //wait until transmission is finished
//        while(txShiftReg);
//    }
//};

void UartTx::transmitByte(uint8_t argByte){
    //ToDo: disable interrupt?
   uint16_t localTxShiftReg = txShiftReg;
   
   //if sending the previous character is not yet finished, return
   //transmission is finished when tx_shift_reg == 0
   if(localTxShiftReg){return;}//ToDo: enable interrupt?
   
   //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
   localTxShiftReg = (argByte<<1) | (1<<9); //stop bit (1<<9)
   txShiftReg = localTxShiftReg;
   
   //start timer0 with a prescaler of 8
   TCCR0B = (1<<CS01);
   //ToDo: enable interrupt?
};

void UartTx::printStr(const char* argString){
    while( *argString ){
        transmitByte( *argString++ );
        
        //wait until transmission is finished
        while(txShiftReg);
    }
};

void UartTx::printStrLn(const char* argString){
    printStr(argString);
    printStr("\n\r");
//    transmitByte(10);
//    transmitByte(13);
}

void UartTx::printUint8(uint8_t argUint8) {
              /* Converts a byte to a string of decimal text, sends it */
  transmitByte('0' + (argUint8 / 100));                        /* Hundreds */
  transmitByte('0' + ((argUint8 / 10) % 10));                      /* Tens */
  transmitByte('0' + (argUint8 % 10));                             /* Ones */
}

void UartTx::printUint16(uint16_t argUint16) {
  transmitByte('0' + (argUint16 / 10000));                 /* Ten-thousands */
  transmitByte('0' + ((argUint16 / 1000) % 10));               /* Thousands */
  transmitByte('0' + ((argUint16 / 100) % 10));                 /* Hundreds */
  transmitByte('0' + ((argUint16 / 10) % 10));                      /* Tens */
  transmitByte('0' + (argUint16 % 10));                             /* Ones */
}
//
//void printBinaryByte(uint8_t byte) {
//                       /* Prints out a byte as a series of 1's and 0's */
//  uint8_t bit;
//  for (bit = 7; bit < 255; bit--) {
//    if (bit_is_set(byte, bit))
//      transmitByte('1');
//    else
//      transmitByte('0');
//  }
//}


//void uartTxInt(uint8_t argInteger){
//    ToDo: implement uartTxInt
//};

//timer0 compare A match interrupt
ISR(TIM0_COMPA_vect )
{
    uint16_t localTxShiftReg = txShiftReg;
   //output LSB of the TX shift register at the TX pin
   if( localTxShiftReg & 0x01 )
   {
//      TX_PORT |= (1 << txPin);
      PORTB |= (1 << txPin);
   }
   else
   {
//      TX_PORT &=~ (1 << txPin);
       PORTB &=~ (1 << txPin);
   }
   //shift the TX shift register one bit to the right
   localTxShiftReg >>= 1;
   txShiftReg = localTxShiftReg;
   //if the stop bit has been sent, the shift register will be 0
   //and the transmission is completed, so we can stop & reset timer0
   if(!localTxShiftReg)
   {
      TCCR0B = 0;
      TCNT0 = 0;
   }
}