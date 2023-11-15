// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libUtility.h"

//required for copyLibs.py script
//version.major = 0;
//version.minor = 2;

const uint8_t SEMAPHORE_KEY = 42;

//void Semaphore::init(uint8_t argS){
//    maxS = argS;
//    s = 0;
//}

Semaphore::Semaphore(uint8_t argS){
    maxS = argS;
    s = 0;
}

Semaphore::Semaphore(void){
    maxS = 1;
    s = 0;
}


uint8_t Semaphore::lock(void){
    if (s < maxS){
        s++;
        return SEMAPHORE_KEY;
    }
    else
        return 0;
}

uint8_t Semaphore::checkKey(uint8_t argKey){
    if(argKey == SEMAPHORE_KEY)
        return 1;
    else
        return 0;
}

uint8_t Semaphore::unlock(uint8_t argKey){
    if (s && checkKey(argKey)){
        s--;
        return 0;
    }
    return argKey;
}
