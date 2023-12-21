// see header for description and other information
// copyright applies according to LICENSE_software.md in GitHub root folder

#include "singletonTempalte.h"

#ifndef SINGLETONTEMPLATE_CPP
#define	SINGLETONTEMPLATE_CPP

namespace nsLibNameSingletonImpl {

    nsLibNameSingletonImpl::LibNameSingletonImpl::LibNameSingletonImpl(void) {//Ctor
        version.major = 0;
        version.minor = 1;

        singletonState = INIT_STATE;

        //init all member variables

    }//LibNameSingletonImpl()

}//namespace nsLibNameSingletonImpl

#endif SINGLETONTEMPLATE_CPP