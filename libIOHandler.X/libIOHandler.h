/*--------------------------------------------------------------------
 Description:   Provides generic IO handling functionality
  
 Author:        Johannes Windmiler
 
 Dependencies:  libUtility
 
 Version:       v0.1
 
 History:       v0.1     Initial implementation
 
 Supported MUC: ATtiny85
 
 References:    Elicia White, Making Embedded Systems p83, 91, O'Reilly 2012
  
 Copyright:     see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

#ifndef LIBIOHANDLER_H
#define	LIBIOHANDLER_H

#include <avr/io.h>
#include "libUtility.h"

class libIOHandler{
    public:
                libIOHandler(void);
        
        void    setPinOutput(uint8_t argPin);
        void    setPinHigh(uint8_t argPin);
        void    setPinLow(uint8_t argPin);
        void    togglePin(uint8_t argPin);

        void    setPinInput(uint8_t argPin, uint8_t argPullUp = false);
        uint8_t readPinRaw(uint8_t argPin);
        
        ver_t   getVersion(void);

        /*ToDo
         void configureInterrupt(uint8_t argPin, uint8_t argTriggerType, 
        uint8_t argTriggerState);

        void enableInterruptOnPin(uint8_t argPin);
        void disableInterruptOnPin(uint8_t argPin);  */    

    private: 
        uint8_t getDdr(uint8_t argPin);
        ver_t   version;
};

#endif	/* LIBIOHANDLER_H */