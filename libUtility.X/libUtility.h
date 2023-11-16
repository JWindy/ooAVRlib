/*--------------------------------------------------------------------
Description:    This module contains functions and constants, which are used by 
                by several other libraries 
  
Author:         Johannes Windmiller
 
Dependencies:   none

Version:        v0.2

History:        v0.1    initial implementation
                v0.2    semaphore implemented

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
    INIT_STATE,
    IDLE_STATE,
    BUSSY_STATE,
    ERROR_STATE
};

class Semaphore{
    //provides basic operations to lock a ressource/object to  prevent access by 
    //to many users. For argS == 1 -> mutex -> only one user can access the 
    //ressouce/object
    public:
        //ArgMaxNumberOfUser defines the number of users, which can access the protected resource/class
                        Semaphore(uint8_t argMaxNumberOfUser);
        //If the resourece is available upon request, lock() returns a key, which is 
        //required to unlock the resource -> argKey. 
        uint8_t         lock(void);
        //If the ressource can be unlocked (ressource locked and key correct), 
        //unlock returns 0, otherwise it returns argKey
        uint8_t         unlock(uint8_t argKey);
        //Any critical operation of the ressource/object can be guarded by 
        //checking the key of the user -> returns 1, if the key is correct, 
        //otherwise returns 0
        uint8_t         checkKey(uint8_t argKey);
        
    private:
        uint8_t         userCount;
        uint8_t         maxNumberOfUser;
};
#endif	/* LIBUTILITY_H */

