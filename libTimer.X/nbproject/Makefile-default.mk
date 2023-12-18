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
SOURCEFILES_QUOTED_IF_SPACED=libTimer.cpp libTimerTest.cpp lib/libUtility.cpp lib/libIOHandler.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/libTimer.o ${OBJECTDIR}/libTimerTest.o ${OBJECTDIR}/lib/libUtility.o ${OBJECTDIR}/lib/libIOHandler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/libTimer.o.d ${OBJECTDIR}/libTimerTest.o.d ${OBJECTDIR}/lib/libUtility.o.d ${OBJECTDIR}/lib/libIOHandler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/libTimer.o ${OBJECTDIR}/libTimerTest.o ${OBJECTDIR}/lib/libUtility.o ${OBJECTDIR}/lib/libIOHandler.o

# Source Files
SOURCEFILES=libTimer.cpp libTimerTest.cpp lib/libUtility.cpp lib/libIOHandler.cpp

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
${OBJECTDIR}/libTimer.o: libTimer.cpp  .generated_files/flags/default/1e7dceebe8067ec1e371c0a373c7c351ab42f313 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimer.o.d 
	@${RM} ${OBJECTDIR}/libTimer.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimer.o.d" -MT "${OBJECTDIR}/libTimer.o.d" -MT ${OBJECTDIR}/libTimer.o  -o ${OBJECTDIR}/libTimer.o libTimer.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
${OBJECTDIR}/libTimerTest.o: libTimerTest.cpp  .generated_files/flags/default/24f8e0245310633828191b3593f1e345115766a4 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimerTest.o.d 
	@${RM} ${OBJECTDIR}/libTimerTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimerTest.o.d" -MT "${OBJECTDIR}/libTimerTest.o.d" -MT ${OBJECTDIR}/libTimerTest.o  -o ${OBJECTDIR}/libTimerTest.o libTimerTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
${OBJECTDIR}/lib/libUtility.o: lib/libUtility.cpp  .generated_files/flags/default/ba07a05289807bd67ba866050d7d7fb72ae96bd1 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libUtility.o.d 
	@${RM} ${OBJECTDIR}/lib/libUtility.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libUtility.o.d" -MT "${OBJECTDIR}/lib/libUtility.o.d" -MT ${OBJECTDIR}/lib/libUtility.o  -o ${OBJECTDIR}/lib/libUtility.o lib/libUtility.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
${OBJECTDIR}/lib/libIOHandler.o: lib/libIOHandler.cpp  .generated_files/flags/default/49215b60e0637f142c39d845c43fe45a465a7f2c .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o.d 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libIOHandler.o.d" -MT "${OBJECTDIR}/lib/libIOHandler.o.d" -MT ${OBJECTDIR}/lib/libIOHandler.o  -o ${OBJECTDIR}/lib/libIOHandler.o lib/libIOHandler.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
else
${OBJECTDIR}/libTimer.o: libTimer.cpp  .generated_files/flags/default/fc2121b5f547fe7bee46efddf18660b677b2f86e .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimer.o.d 
	@${RM} ${OBJECTDIR}/libTimer.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimer.o.d" -MT "${OBJECTDIR}/libTimer.o.d" -MT ${OBJECTDIR}/libTimer.o  -o ${OBJECTDIR}/libTimer.o libTimer.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
${OBJECTDIR}/libTimerTest.o: libTimerTest.cpp  .generated_files/flags/default/cbf7f2f835794bfe75f524446d1a8c06ec9a3407 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/libTimerTest.o.d 
	@${RM} ${OBJECTDIR}/libTimerTest.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/libTimerTest.o.d" -MT "${OBJECTDIR}/libTimerTest.o.d" -MT ${OBJECTDIR}/libTimerTest.o  -o ${OBJECTDIR}/libTimerTest.o libTimerTest.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
${OBJECTDIR}/lib/libUtility.o: lib/libUtility.cpp  .generated_files/flags/default/d5333025a715e37106a0fcf47d9c79a26258d9f .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libUtility.o.d 
	@${RM} ${OBJECTDIR}/lib/libUtility.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libUtility.o.d" -MT "${OBJECTDIR}/lib/libUtility.o.d" -MT ${OBJECTDIR}/lib/libUtility.o  -o ${OBJECTDIR}/lib/libUtility.o lib/libUtility.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
${OBJECTDIR}/lib/libIOHandler.o: lib/libIOHandler.cpp  .generated_files/flags/default/d9610713e655e6b2e45b748b89a62e7e074635a7 .generated_files/flags/default/fe4041e053f0de6728714b4d2a84c3b830905bb7
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o.d 
	@${RM} ${OBJECTDIR}/lib/libIOHandler.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=attiny85 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -I"lib" -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DBAUD=9600 -DF_CPU=8000000 -Wall -MD -MP -MF "${OBJECTDIR}/lib/libIOHandler.o.d" -MT "${OBJECTDIR}/lib/libIOHandler.o.d" -MT ${OBJECTDIR}/lib/libIOHandler.o  -o ${OBJECTDIR}/lib/libIOHandler.o lib/libIOHandler.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++14
	
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
