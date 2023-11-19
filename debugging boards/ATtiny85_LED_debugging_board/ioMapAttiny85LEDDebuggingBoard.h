/*--------------------------------------------------------------------
 Description:   Provides the IO mapping for the ATtiny 85 LED debugging
                board
  
 Author:        Johannes Windmiller
 
 Dependencies:  none
 
 Version:       v0.1
 
 History:       v0.1     Initial implementation
 
 Supported MUC: ATtiny85
 
 References:
    - Elicia White, Making Embedded Systems, O'Reilly 2012
 
 Copyright:     see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

#ifndef IOMAPATTINY85LEDDEBUGGINGBOARD_H
#define	IOMAPATTINY85LEDDEBUGGINGBOARD_H

#ifndef __AVR_ATtiny85__
    #define __AVR_ATtiny85__
#endif

#include <avr/io.h>

const uint8_t LED_PIN0 = PB0; //don't change. PWM hard wired
const uint8_t LED_PIN1 = PB1; //don't change. PWM hard wired
const uint8_t LED_PIN4 = PB4;

//PB5 reserved for debug wire -> Atmel ICE debugging interface

#endif	/* IOMAPATTINY85LEDDEBUGGINGBOARD_H */

