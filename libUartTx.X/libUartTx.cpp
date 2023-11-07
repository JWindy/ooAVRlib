// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libUartTx.h"
#include <avr/interrupt.h>

UartTx::UartTx(void){
    status = ERROR_STATE;
    libIOHandler myIOHandler;
    
    myIOHandler.setPinOutput(txPin);
    
    version.major = 0;
    version.minor = 1;
    
    #if  (BAUD != 9600)
        #error "Uart Tx implemented for BAUD = 9600 only!"
    #endif
    
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
    
    status = IDLE_STATE;
    
    //enable interrupts
    sei();   
};

status_t UartTx::getStatus(){
    sei();
    const uint8_t localTxShiftReg = txShiftReg;
    cli();
    
    if(status != ERROR_STATE){
        if(localTxShiftReg)
            status = BUSSY_STATE;
        else
            status = IDLE_STATE;
    }
    return status;
};

void UartTx::transmitByte(uint8_t argByte){
    //wait until transmission is finished
    //this might lead to a crash in the proramm, if for some reason, 
    //the transmittion is never completed. ToDo Timeout?
    while(getStatus() == BUSSY_STATE);

    //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
    uint16_t localTxShiftReg = (argByte<<1) | (1<<9); //stop bit (1<<9)

    cli();
    txShiftReg = localTxShiftReg;
    TCCR0B = (1<<CS01);//start timer0 with a prescaler of 8
    sei();
};

void UartTx::printStr(const char* argString){
    while( *argString ){
        transmitByte( *argString++ );
    }
};

void UartTx::printStrLn(const char* argString){
    printStr(argString);
    printLn();
};

void UartTx::printLn(void){
    printStr("\n\r");
};

void UartTx::printBinaryByte(uint8_t byte) {
 /* Prints out a byte as a series of 1's and 0's */
  uint8_t bit;
  for (bit = 7; bit < 255; bit--) {
    if (bit_is_set(byte, bit))
      transmitByte('1');
    else
      transmitByte('0');
  }
};

//timer0 compare A match interrupt
ISR(TIM0_COMPA_vect )
{
    uint16_t localTxShiftReg = txShiftReg;
   //output LSB of the TX shift register at the TX pin
   if( localTxShiftReg & 0x01 )
   {
      PORTB |= (1 << txPin);
   }
   else
   {
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
};