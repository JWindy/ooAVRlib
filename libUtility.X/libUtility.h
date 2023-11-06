/*--------------------------------------------------------------------
Description:    This module contains functions and constants, which are used by 
                by several other libraries 
  
Author:         Johannes Windmiller
 
Dependencies:   none

Version:        v0.1

History:        v0.1     initial implementation

Supported MUC:  ATtiny85, ATtiny84, ATmega 168, ATmega328
 
References:     none

Comment:        I'm not yet fully convinced, that this lib is a good idea. 
                We'll see...
 
Copyright:      see LICENSE_software.md in git hub root folder
 *--------------------------------------------------------------------*/

#ifndef LIBUTILITY_H
#define	LIBUTILITY_H

#include <avr/io.h>

struct ver_t{
    uint8_t major;
    uint8_t minor;
};

enum status_t{
    idle,
    bussy,
    error
};

#endif	/* LIBUTILITY_H */

