// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "projectTemplate.h"

void classTemplate::init(void){
    #ifndef __AVR_ATtiny85__
        #error "libIOHandler not implemented for selected MUC."
    #endif
}