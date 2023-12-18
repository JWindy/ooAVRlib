# ooAVRlib - object oriented AVR library
I started my first embedded projects with Arduino. Due to high power consumption for battery powered projects and relatively large size for projects in confined space, I moved to ATMEL AVR microcontrollers. Mostly, I use ATtiny 85. Since I'm a fan of object oriented programming and I loved the Arduino framework with all the libraries, I started implementing libraries to make life easier. The goal of the libraries is to provide basics functions, to speed up the implementation of new projects. By breaking the functionality down in encapsulated modules, I can reduce complexity for debugging. In case an application source code should get to big, I still can copy the required lines of code together and should have much less troubble interpreting the data sheet and searching for bugs, compared to implementing everything from scratch.
With this repository, I intent to share the libraries to anyone interested and provide some material for beginners, who hopefully have an easier start with my rather simple libraries. It would also be great to find someone willing to contribute to the libraries or get some feedback from more experienced developers. I'm neither a professional software nor hardware engineer;)

# Work in progress
I'm currently working on the initial implementation of the libraries. As soon as the first libraries are tested and ready for use, I'll upload a release.

# How to use the libraries
For every library, you'll find the following folders:
- assets -> any further information like class or block diagrams, if relevant.
- hardware -> This folder contains the design of the hardware used for testing the library. For basic libraries, I'll use a debugging board solderd on a prototype board, which you can find in the folder "debugging boards".
- lib -> If other libraries are required for running the library, the corresponding files are copied here.
- libXX.cpp -> source file
- libXX.h -> header file
- libXXTest.cpp -> test file. The test file shows how to use each function, together with the information in the hardware folder, this should be sufficient documentation to get started:D

# Microcontrollers
For now, the libraries will be implemented for ATtiny 85 running at 8 MHz. I plan on supporting other clock frequencies as well as ATtiny 84 and ATmega 328 in the future.

# Toolchain
I published the project files of the schematics and layouts as well as of the IDE. If you encounter any problems, it might help, to try to open the projects as they are and search for the difference. 
- coding: MPLAB® X IDE -> https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide
- additional compiler flags: -std=c++14
- programming and debugging: ATMEL-ICE -> https://www.microchip.com/en-us/development-tool/atatmel-ice
- schematics and layouts: KiCad -> https://www.kicad.org/

# Overview over the libraries
The libraries can be grouped in hardware proxies, general purpose libraries, development tools and application level. 
In general, you find more information in the header file of each library, which I don't want to copy here;)
## Hardware Proxies/Drivers
These libraries give access to microcontroller capabilites on the lowest level. Since the ressource can only be accessed by one user, most of the libraries are implemented as singleton and protected by a semaphore.
### libIOHandler
libIOHandler provides basic functions to set a pin as output or input, to activate the internal pullup for input pins, to set a pin high or low and to read the state of a input pin.
### libTimer
This library implements the capabilities of the timer0 and timer1. The timer can be used to trigger interrputs (CTC mode) or to output a PWM signal (PWM mode). 
## General purpose libraries
### libUtility
libUtility contains general type definitions, which will be used to implement the interfaces between libraries. Furthermore, a semaphore is implemented to provide locking functionality especially to hardware proxies to avoide multiple access. This feature might be overengineered for hobby applications, but it was fun to understand, how a semaphore works;)
## Development tools
Development tools are usefull for debugging and testing of other libraries and application code. This group will cover functionality implementing the interface to the serial montior and logging and error handling. The libraries might also be usefull on application level, but so far, I always deactivated these functions, when finishing the project.
### libUartTx
This library provides functions to send strings and numbers (uint and int, 8- and 16-bit) to a serial monitor. To access the UART interface, a USB-UART-adapter is required. I use this function primarily for debugging and logging. libUartTx implements the UART protocol in SW and can be hooked up on any GPIO pin. The library is implemented as singleton, but not protected. So any user can send data. The CPU cycle is blocked until all data is send, so users can access the transmitting function in serial. 
## Application level
So far, I'm still ocupied with the basic libraries;)
