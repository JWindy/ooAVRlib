#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lib/libUtility.cpp libUartTx.cpp libUartTxTest.cpp lib/libTimer.cpp lib/libIOHandler.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib/libUtility.o ${OBJECTDIR}/libUartTx.o ${OBJECTDIR}/libUartTxTest.o ${OBJECTDIR}/lib/libTimer.o ${OBJECTDIR}/lib/libIOHandler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lib/libUtility.o.d ${OBJECTDIR}/libUartTx.o.d ${OBJECTDIR}/libUartTxTest.o.d ${OBJECTDIR}/lib/libTimer.o.d ${OBJECTDIR}/lib/libIOHandler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib/libUtility.o ${OBJECTDIR}/libUartTx.o ${OBJECTDIR}/libUartTxTest.o ${OBJECTDIR}/lib/libTimer.o ${OBJECTDIR}/lib/libIOHandler.o

# Source Files
SOURCEFILES=lib/libUtility.cpp libUartTx.cpp libUartTxTest.cpp lib/libTimer.cpp lib/libIOHandler.cpp

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/attiny85"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATtiny85
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib/libUtility.o: lib/libUtility.cpp  .generated_files/flags/default/4c05b3f0e16a3606f33752bb8b0a6c19e2618260 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libUtility.o.d 
	@${RM} ${OBJECTDIR}/lib/libUtility.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libUtility.o.d" -MT "${OBJECTDIR}/lib/libUtility.o.d" -MT ${OBJECTDIR}/lib/libUtility.o  -o ${OBJECTDIR}/lib/libUtility.o lib/libUtility.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/libUartTx.o: libUartTx.cpp  .generated_files/flags/default/b3b78fa674baff34d588a600720ba0ef27c26c11 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTx.o.d 
	@${RM} ${OBJECTDIR}/libUartTx.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libUartTx.o.d" -MT "${OBJECTDIR}/libUartTx.o.d" -MT ${OBJECTDIR}/libUartTx.o  -o ${OBJECTDIR}/libUartTx.o libUartTx.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/libUartTxTest.o: libUartTxTest.cpp  .generated_files/flags/default/4efc193e3d5a1fbe3ac1f376bfafa7bc68dc9bd6 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTxTest.o.d 
	@${RM} ${OBJECTDIR}/libUartTxTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libUartTxTest.o.d" -MT "${OBJECTDIR}/libUartTxTest.o.d" -MT ${OBJECTDIR}/libUartTxTest.o  -o ${OBJECTDIR}/libUartTxTest.o libUartTxTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/lib/libTimer.o: lib/libTimer.cpp  .generated_files/flags/default/cf9a075e82bcf8bc6d36a7af3085358c94d67e5a .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libTimer.o.d 
	@${RM} ${OBJECTDIR}/lib/libTimer.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libTimer.o.d" -MT "${OBJECTDIR}/lib/libTimer.o.d" -MT ${OBJECTDIR}/lib/libTimer.o  -o ${OBJECTDIR}/lib/libTimer.o lib/libTimer.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/lib/libIOHandler.o: lib/libIOHandler.cpp  .generated_files/flags/default/ceb84d47110716e97ca5eaa5790fed28c2141b1 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o.d 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libIOHandler.o.d" -MT "${OBJECTDIR}/lib/libIOHandler.o.d" -MT ${OBJECTDIR}/lib/libIOHandler.o  -o ${OBJECTDIR}/lib/libIOHandler.o lib/libIOHandler.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
else
${OBJECTDIR}/lib/libUtility.o: lib/libUtility.cpp  .generated_files/flags/default/352d84e2b66a5bfe88b043581b645e0e250f685 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libUtility.o.d 
	@${RM} ${OBJECTDIR}/lib/libUtility.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libUtility.o.d" -MT "${OBJECTDIR}/lib/libUtility.o.d" -MT ${OBJECTDIR}/lib/libUtility.o  -o ${OBJECTDIR}/lib/libUtility.o lib/libUtility.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/libUartTx.o: libUartTx.cpp  .generated_files/flags/default/d2ece325c740035ea36f3d2925312ff003800663 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTx.o.d 
	@${RM} ${OBJECTDIR}/libUartTx.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libUartTx.o.d" -MT "${OBJECTDIR}/libUartTx.o.d" -MT ${OBJECTDIR}/libUartTx.o  -o ${OBJECTDIR}/libUartTx.o libUartTx.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/libUartTxTest.o: libUartTxTest.cpp  .generated_files/flags/default/27c61c3d9f0b28afd898aa044e79da2ba2f30743 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTxTest.o.d 
	@${RM} ${OBJECTDIR}/libUartTxTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libUartTxTest.o.d" -MT "${OBJECTDIR}/libUartTxTest.o.d" -MT ${OBJECTDIR}/libUartTxTest.o  -o ${OBJECTDIR}/libUartTxTest.o libUartTxTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/lib/libTimer.o: lib/libTimer.cpp  .generated_files/flags/default/c7c02b73679d7401c0a2210de72dce8d31fbaee7 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libTimer.o.d 
	@${RM} ${OBJECTDIR}/lib/libTimer.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libTimer.o.d" -MT "${OBJECTDIR}/lib/libTimer.o.d" -MT ${OBJECTDIR}/lib/libTimer.o  -o ${OBJECTDIR}/lib/libTimer.o lib/libTimer.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
${OBJECTDIR}/lib/libIOHandler.o: lib/libIOHandler.cpp  .generated_files/flags/default/87b4dd6a9b998a98f930ed24c34ad6244152dc21 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o.d 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libIOHandler.o.d" -MT "${OBJECTDIR}/lib/libIOHandler.o.d" -MT ${OBJECTDIR}/lib/libIOHandler.o  -o ${OBJECTDIR}/lib/libIOHandler.o lib/libIOHandler.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -std=c++14
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -mmcu=attiny85 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -mmcu=attiny85 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/libUartTx.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
