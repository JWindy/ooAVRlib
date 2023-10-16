# ooAVRlib - object oriented AVR library
I started my first embedded projects with Arduino. Due to high power consumption for battery powered projects and relatively large size for projects in confined space, I moved to ATMEL AVR microcontrollers. Mostly I use ATtiny 85. Since I'm a fan of object oriented programming and I loved the Arduino framework with all the libraries, I started implementing libraries to make life easier. The goal of the libraries is to provide basics functions, to speed up the implementation of new projects. With this repository, I intent to share the libraries to anyone interested and provide some material for beginners, who hopefully have an easier start with my rather simple libraries. It would also be great to find someone willing to contribute to the libraries or get some feedback from more experienced developers. I'm neither a professional software nor hardware engineer;)

# Work in progress
I'm currently working on the initial implementation of the libraries. As soon as the first libraries are tested and ready for use, I'll upload a release.

# How to use the repository
For every library, you'll find the folling folders:
- assets -> any further information like block diagrams or state machines.
- hardware -> This folder contains the design of the hardware used for testing the library. For basic libraries, I'll use a debugging board solderd on a prototype board, which you can find in the folder "debugging boards".
- lib -> If other libraries are required for running the library, the corresponding files are copied here.
- libXX.cpp -> source file
- libXX.h -> header file
- testLibXX.cpp -> test file

# Microcontrollers
For now, the libraries will be implemented for ATtiny 85. I plan on supporting ATtiny 84 and ATmega 328 in the future.

# Toolchain
- coding: MPLAB® X IDE -> https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide
- programming and debugging: ATMEL-ICE -> https://www.microchip.com/en-us/development-tool/atatmel-ice
- schematics and layouts: Ki CAD -> https://www.kicad.org/

