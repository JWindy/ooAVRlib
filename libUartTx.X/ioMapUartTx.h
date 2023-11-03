/*--------------------------------------------------------------------
 Description:   Provides the IO mapping depending on the HW selected in 
                libUartTx.h 
  
 Author:        Johannes Windmiller
 
 Dependencies:  none
 
 Version:       v0.0.1
 
 History:       v0.0.1     Initial implementation
 
 Supported MUC: ATtiny85
 
 References:    Elicia White, Making Embedded Systems, O'Reilly 2012
 
  Comment:      Not yet relevant, but in case there is several hardware, it 
                will be easier to change a define in the source file instead of 
                selecting the correct IO map in every library.
 
 Copyright:     see LICENSE_software.md in GitHub root folder
 *--------------------------------------------------------------------*/

#ifndef IOMAPUARTTX_H
#define	IOMAPUARTTX_H

#ifdef HW_ATtiny85_Default_Debugging_Board
    #include "ioMapAttiny85DefaultDebuggingBoard.h"
#else
    #error "No IO map for selected hardware available!"
#endif

#endif	/* IOMAPUARTTX_H */

