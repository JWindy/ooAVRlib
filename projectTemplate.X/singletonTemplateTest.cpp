// testing application for <project name>
// copyright applies according to LICENSE_software.md in GitHub root folder

#ifndef BAUD
#    define BAUD 9600
#endif

#ifndef F_CPU
#    define F_CPU 8000000
#endif

#ifndef __AVR_ATtiny85__
#    define __AVR_ATtiny85__
#endif

#define HW_rev

//#include <util/delay.h>
//#include <avr/interrupt.h>
#include "singletonTemplate.h"

#include "ioMapXY.h"

int main(void) {

    const uint8_t numberOfUser = 1;

    LibName::initialise(numberOfUser);

    auto mySingleton = LibNameSingleton::getInstance();

    return 0;
}//int main(void))