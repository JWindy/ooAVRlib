//copy header from projectTemplate.h
//see libTimer for implementation of singleton template class

#ifndef SINGLETONTEMPLATE_H
#define	SINGLETONTEMPLATE_H

#include <avr/io.h>
#include "libUtility.h"	//v0.2

template <typename T>
class LibNameSingleton;

namespace nsLibNameImpl {

    class LibNameImpl {
    public:
        Semaphore* pSemaphore;


    private:
        LibNameImpl(void);

        //allows the initialisation function to access the Ctor
        //    friend void instansiateObject(char [], uint8_t);
        friend class LibNameSingleton<nsLibNameImpl::LibNameImpl>;

        ver_t version;
        status_t singletonState;

        MemberObjectType* pMemberObject;
        //declare a pointer for any member object

    }; //class SingletonImpl

    //void instansiateObject(char buffer[], uint8_t argNumberOfUsers){
    //    LibNameImpl* tmp = reinterpret_cast<LibNameImpl*>(buffer);
    //    *tmp = LibNameImpl();
    //    tmp->singletonState = READY_STATE;
    //
    //    *tmp->pSemaphore = Semaphore(argNumberOfUsers);
    //}

}//namespace LibNameImpl

template <typename T>
class LibNameSingleton {
public:

    //Initialises the singleton object
    //Call this function before using any of its methods. 
    //Calling initialise ensures that the object exists upon usage. Otherwise
    //undevined behavious might occure, since the compiler can move the 
    //instantiation to a later point in time.

    static void initialise(uint8_t argNumberOfUsers) {
        if (refCount == 0) {
            //                nsLibNameImpl::instansiateObject(buffer, argNumberOfUsers);
            T* tmp = reinterpret_cast<T*> (buffer);
            *tmp = nsLibNameImpl::LibNameImpl();
            tmp->singletonState = READY_STATE;

            *tmp->pSemaphore = Semaphore(argNumberOfUsers);
            //instantiate any member object here
            *tmp->pMemberObject = MemberObject();
            refCount = 1;
        }
    }

    //Returns the one and only singleton instance of the class

    static T* getInstance(void) {
        return (reinterpret_cast<T*> (buffer));
    }

private:
    LibNameSingleton(void);
    static char buffer[sizeof (T)];
    static uint8_t refCount;

};//class LibNameSingleton

template<typename T>
char LibNameSingleton<T>::buffer[];

template<typename T>
uint8_t LibNameSingleton<T>::refCount = 0;

typedef LibNameSingleton<nsLibNameImpl::LibNameImpl> LibName;

#endif	/* SINGLETONTEMPLATE_H */

