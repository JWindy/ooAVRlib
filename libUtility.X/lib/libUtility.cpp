// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "libUtility.h"

//required for copyLibs.py script. don't delete
//version.major = 0;
//version.minor = 2;

const uint8_t SEMAPHORE_KEY = 42;

Semaphore::Semaphore(uint8_t argMaxNumberOfUser){
    maxNumberOfUser = argMaxNumberOfUser;
    userCount = 0;
}

uint8_t Semaphore::lock(void){
    if (userCount < maxNumberOfUser){
        userCount++;
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
    if (userCount && checkKey(argKey)){
        userCount--;
        return 0;
    }
    return argKey;
}
