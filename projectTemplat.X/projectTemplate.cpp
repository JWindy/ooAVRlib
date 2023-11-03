// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "projectTemplate.h"

void classTemplate::classTemplate(void){
    #ifndef __AVR_ATtiny85__
        #error "libIOHandler not implemented for selected MUC."
    #endif

    version.major = 0;
    version.minor = 0;
    
}