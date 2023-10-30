/*--------------------------------------------------------------------
 Description:   Provides the IO mapping for the ATtiny 85 default debugging
                board
  
 Author:        Johannes Windmiler
 
 Dependencies:  none
 
 Version:       v0.0.1
 
 History:       v0.0.1     Initial implementation
 
 Supported MUC: ATtiny85
 
 References:
    - Elicia White, Making Embedded Systems, O'Reilly 2012
 
 Copyright:     see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

#ifndef IOMAPATTINY85DEFAULTDEBUGGINGBOARD_H
#define	IOMAPATTINY85DEFAULTDEBUGGINGBOARD_H

#ifndef __AVR_ATtiny85__
    #define __AVR_ATtiny85__
#endif

#include <avr/io.h>

const uint8_t LED_PIN         = PB1;

const uint8_t BUTTON_PIN      = PB3;

const uint8_t ADC_PIN         = PB4;

const uint8_t UART_Tx_PIN     = PB0;

const uint8_t UART_Rx_PIN     = PB2;

//PB5 reserved for debug wire -> Atmel ICE debugging interface

#endif	/* IOMAPATTINY85DEFAULTDEBUGGINGBOARD_H */

