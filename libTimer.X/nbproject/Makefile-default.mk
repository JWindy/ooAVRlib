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
FINAL_IMAGE=${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=libTimer.cpp libTimerTest.cpp lib/libUtility.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/libTimer.o ${OBJECTDIR}/libTimerTest.o ${OBJECTDIR}/lib/libUtility.o
POSSIBLE_DEPFILES=${OBJECTDIR}/libTimer.o.d ${OBJECTDIR}/libTimerTest.o.d ${OBJECTDIR}/lib/libUtility.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/libTimer.o ${OBJECTDIR}/libTimerTest.o ${OBJECTDIR}/lib/libUtility.o

# Source Files
SOURCEFILES=libTimer.cpp libTimerTest.cpp lib/libUtility.cpp

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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/libTimer.o: libTimer.cpp  .generated_files/flags/default/7cbcb1fd4ec76b35ef0b96d7f610515016ba1b21 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimer.o.d 
	@${RM} ${OBJECTDIR}/libTimer.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimer.o.d" -MT "${OBJECTDIR}/libTimer.o.d" -MT ${OBJECTDIR}/libTimer.o  -o ${OBJECTDIR}/libTimer.o libTimer.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/libTimerTest.o: libTimerTest.cpp  .generated_files/flags/default/313b86fb2fdb5eee605a33fad9ba2e0890820594 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimerTest.o.d 
	@${RM} ${OBJECTDIR}/libTimerTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimerTest.o.d" -MT "${OBJECTDIR}/libTimerTest.o.d" -MT ${OBJECTDIR}/libTimerTest.o  -o ${OBJECTDIR}/libTimerTest.o libTimerTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/libUtility.o: lib/libUtility.cpp  .generated_files/flags/default/b14083eec30693810ecffb446fbf3e6f26895111 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libUtility.o.d 
	@${RM} ${OBJECTDIR}/lib/libUtility.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libUtility.o.d" -MT "${OBJECTDIR}/lib/libUtility.o.d" -MT ${OBJECTDIR}/lib/libUtility.o  -o ${OBJECTDIR}/lib/libUtility.o lib/libUtility.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/libTimer.o: libTimer.cpp  .generated_files/flags/default/300a85b6671adb9a35d1d53da2764a2ca1b9e16b .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimer.o.d 
	@${RM} ${OBJECTDIR}/libTimer.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimer.o.d" -MT "${OBJECTDIR}/libTimer.o.d" -MT ${OBJECTDIR}/libTimer.o  -o ${OBJECTDIR}/libTimer.o libTimer.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/libTimerTest.o: libTimerTest.cpp  .generated_files/flags/default/e8ee48e5ad8f5c6bc54ea33f1d607a8a3fb2d46 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimerTest.o.d 
	@${RM} ${OBJECTDIR}/libTimerTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimerTest.o.d" -MT "${OBJECTDIR}/libTimerTest.o.d" -MT ${OBJECTDIR}/libTimerTest.o  -o ${OBJECTDIR}/libTimerTest.o libTimerTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/libUtility.o: lib/libUtility.cpp  .generated_files/flags/default/900e6df18a5ba8810be3ab94b48d718f5acaf75c .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libUtility.o.d 
	@${RM} ${OBJECTDIR}/lib/libUtility.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libUtility.o.d" -MT "${OBJECTDIR}/lib/libUtility.o.d" -MT ${OBJECTDIR}/lib/libUtility.o  -o ${OBJECTDIR}/lib/libUtility.o lib/libUtility.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -mmcu=attiny85 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/libTimer.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -mmcu=attiny85 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/libTimer.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/libTimer.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/libTimer.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
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
