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
SOURCEFILES_QUOTED_IF_SPACED=libUartTx.cpp libUartTxTest.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/libUartTx.o ${OBJECTDIR}/libUartTxTest.o
POSSIBLE_DEPFILES=${OBJECTDIR}/libUartTx.o.d ${OBJECTDIR}/libUartTxTest.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/libUartTx.o ${OBJECTDIR}/libUartTxTest.o

# Source Files
SOURCEFILES=libUartTx.cpp libUartTxTest.cpp

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
${OBJECTDIR}/libUartTx.o: libUartTx.cpp  .generated_files/flags/default/f32d64e83aec6f59015790a99eac60dbe5de5a61 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTx.o.d 
	@${RM} ${OBJECTDIR}/libUartTx.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/libUartTx.o.d" -MT "${OBJECTDIR}/libUartTx.o.d" -MT ${OBJECTDIR}/libUartTx.o  -o ${OBJECTDIR}/libUartTx.o libUartTx.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/libUartTxTest.o: libUartTxTest.cpp  .generated_files/flags/default/a96fce7730b20457275e1ba481012d155c6c6b09 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTxTest.o.d 
	@${RM} ${OBJECTDIR}/libUartTxTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/libUartTxTest.o.d" -MT "${OBJECTDIR}/libUartTxTest.o.d" -MT ${OBJECTDIR}/libUartTxTest.o  -o ${OBJECTDIR}/libUartTxTest.o libUartTxTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/libUartTx.o: libUartTx.cpp  .generated_files/flags/default/6a4d0687ea6706d7ef5e33611815e647bf47ed2f .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTx.o.d 
	@${RM} ${OBJECTDIR}/libUartTx.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/libUartTx.o.d" -MT "${OBJECTDIR}/libUartTx.o.d" -MT ${OBJECTDIR}/libUartTx.o  -o ${OBJECTDIR}/libUartTx.o libUartTx.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/libUartTxTest.o: libUartTxTest.cpp  .generated_files/flags/default/2601c95737d2414e63fc4f1f7d88be36e0d53ff3 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libUartTxTest.o.d 
	@${RM} ${OBJECTDIR}/libUartTxTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/libUartTxTest.o.d" -MT "${OBJECTDIR}/libUartTxTest.o.d" -MT ${OBJECTDIR}/libUartTxTest.o  -o ${OBJECTDIR}/libUartTxTest.o libUartTxTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
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
