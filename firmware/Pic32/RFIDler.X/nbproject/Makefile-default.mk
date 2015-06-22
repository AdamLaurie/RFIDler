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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/FSIO.c" "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/SD-SPI.c" "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SClib.c" "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SCpic32.c" "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/CDC Device Driver/usb_function_cdc.c" /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/usb_device.c src/indala.c src/main.c src/psk.c src/usb_descriptors.c src/util.c src/emulate.c src/ask.c src/fsk.c src/clock.c src/rwd.c src/detect.c src/hitagcrypto.c src/wiegand.c src/comms.c src/nvm.c src/mcp414x.c src/spi.c src/uart3.c src/tags.c src/unique.c src/led.c src/em.c src/hid.c src/read.c src/isr.c src/auto.c src/fdxb.c src/hitag.c src/uid.c src/login.c src/write.c src/auth.c src/q5.c src/vtag.c src/config.c src/select.c src/sdcard.c src/debug_pins.c src/awid.c src/analogue.c src/iso7816.c src/t55x7.c src/sniff.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1209914024/FSIO.o ${OBJECTDIR}/_ext/1209914024/SD-SPI.o ${OBJECTDIR}/_ext/1019771169/SClib.o ${OBJECTDIR}/_ext/1019771169/SCpic32.o ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o ${OBJECTDIR}/_ext/186742988/usb_device.o ${OBJECTDIR}/src/indala.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/psk.o ${OBJECTDIR}/src/usb_descriptors.o ${OBJECTDIR}/src/util.o ${OBJECTDIR}/src/emulate.o ${OBJECTDIR}/src/ask.o ${OBJECTDIR}/src/fsk.o ${OBJECTDIR}/src/clock.o ${OBJECTDIR}/src/rwd.o ${OBJECTDIR}/src/detect.o ${OBJECTDIR}/src/hitagcrypto.o ${OBJECTDIR}/src/wiegand.o ${OBJECTDIR}/src/comms.o ${OBJECTDIR}/src/nvm.o ${OBJECTDIR}/src/mcp414x.o ${OBJECTDIR}/src/spi.o ${OBJECTDIR}/src/uart3.o ${OBJECTDIR}/src/tags.o ${OBJECTDIR}/src/unique.o ${OBJECTDIR}/src/led.o ${OBJECTDIR}/src/em.o ${OBJECTDIR}/src/hid.o ${OBJECTDIR}/src/read.o ${OBJECTDIR}/src/isr.o ${OBJECTDIR}/src/auto.o ${OBJECTDIR}/src/fdxb.o ${OBJECTDIR}/src/hitag.o ${OBJECTDIR}/src/uid.o ${OBJECTDIR}/src/login.o ${OBJECTDIR}/src/write.o ${OBJECTDIR}/src/auth.o ${OBJECTDIR}/src/q5.o ${OBJECTDIR}/src/vtag.o ${OBJECTDIR}/src/config.o ${OBJECTDIR}/src/select.o ${OBJECTDIR}/src/sdcard.o ${OBJECTDIR}/src/debug_pins.o ${OBJECTDIR}/src/awid.o ${OBJECTDIR}/src/analogue.o ${OBJECTDIR}/src/iso7816.o ${OBJECTDIR}/src/t55x7.o ${OBJECTDIR}/src/sniff.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1209914024/FSIO.o.d ${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d ${OBJECTDIR}/_ext/1019771169/SClib.o.d ${OBJECTDIR}/_ext/1019771169/SCpic32.o.d ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d ${OBJECTDIR}/_ext/186742988/usb_device.o.d ${OBJECTDIR}/src/indala.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/psk.o.d ${OBJECTDIR}/src/usb_descriptors.o.d ${OBJECTDIR}/src/util.o.d ${OBJECTDIR}/src/emulate.o.d ${OBJECTDIR}/src/ask.o.d ${OBJECTDIR}/src/fsk.o.d ${OBJECTDIR}/src/clock.o.d ${OBJECTDIR}/src/rwd.o.d ${OBJECTDIR}/src/detect.o.d ${OBJECTDIR}/src/hitagcrypto.o.d ${OBJECTDIR}/src/wiegand.o.d ${OBJECTDIR}/src/comms.o.d ${OBJECTDIR}/src/nvm.o.d ${OBJECTDIR}/src/mcp414x.o.d ${OBJECTDIR}/src/spi.o.d ${OBJECTDIR}/src/uart3.o.d ${OBJECTDIR}/src/tags.o.d ${OBJECTDIR}/src/unique.o.d ${OBJECTDIR}/src/led.o.d ${OBJECTDIR}/src/em.o.d ${OBJECTDIR}/src/hid.o.d ${OBJECTDIR}/src/read.o.d ${OBJECTDIR}/src/isr.o.d ${OBJECTDIR}/src/auto.o.d ${OBJECTDIR}/src/fdxb.o.d ${OBJECTDIR}/src/hitag.o.d ${OBJECTDIR}/src/uid.o.d ${OBJECTDIR}/src/login.o.d ${OBJECTDIR}/src/write.o.d ${OBJECTDIR}/src/auth.o.d ${OBJECTDIR}/src/q5.o.d ${OBJECTDIR}/src/vtag.o.d ${OBJECTDIR}/src/config.o.d ${OBJECTDIR}/src/select.o.d ${OBJECTDIR}/src/sdcard.o.d ${OBJECTDIR}/src/debug_pins.o.d ${OBJECTDIR}/src/awid.o.d ${OBJECTDIR}/src/analogue.o.d ${OBJECTDIR}/src/iso7816.o.d ${OBJECTDIR}/src/t55x7.o.d ${OBJECTDIR}/src/sniff.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1209914024/FSIO.o ${OBJECTDIR}/_ext/1209914024/SD-SPI.o ${OBJECTDIR}/_ext/1019771169/SClib.o ${OBJECTDIR}/_ext/1019771169/SCpic32.o ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o ${OBJECTDIR}/_ext/186742988/usb_device.o ${OBJECTDIR}/src/indala.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/psk.o ${OBJECTDIR}/src/usb_descriptors.o ${OBJECTDIR}/src/util.o ${OBJECTDIR}/src/emulate.o ${OBJECTDIR}/src/ask.o ${OBJECTDIR}/src/fsk.o ${OBJECTDIR}/src/clock.o ${OBJECTDIR}/src/rwd.o ${OBJECTDIR}/src/detect.o ${OBJECTDIR}/src/hitagcrypto.o ${OBJECTDIR}/src/wiegand.o ${OBJECTDIR}/src/comms.o ${OBJECTDIR}/src/nvm.o ${OBJECTDIR}/src/mcp414x.o ${OBJECTDIR}/src/spi.o ${OBJECTDIR}/src/uart3.o ${OBJECTDIR}/src/tags.o ${OBJECTDIR}/src/unique.o ${OBJECTDIR}/src/led.o ${OBJECTDIR}/src/em.o ${OBJECTDIR}/src/hid.o ${OBJECTDIR}/src/read.o ${OBJECTDIR}/src/isr.o ${OBJECTDIR}/src/auto.o ${OBJECTDIR}/src/fdxb.o ${OBJECTDIR}/src/hitag.o ${OBJECTDIR}/src/uid.o ${OBJECTDIR}/src/login.o ${OBJECTDIR}/src/write.o ${OBJECTDIR}/src/auth.o ${OBJECTDIR}/src/q5.o ${OBJECTDIR}/src/vtag.o ${OBJECTDIR}/src/config.o ${OBJECTDIR}/src/select.o ${OBJECTDIR}/src/sdcard.o ${OBJECTDIR}/src/debug_pins.o ${OBJECTDIR}/src/awid.o ${OBJECTDIR}/src/analogue.o ${OBJECTDIR}/src/iso7816.o ${OBJECTDIR}/src/t55x7.o ${OBJECTDIR}/src/sniff.o

# Source Files
SOURCEFILES=/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/FSIO.c /opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/SD-SPI.c /opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SClib.c /opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SCpic32.c /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/CDC Device Driver/usb_function_cdc.c /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/usb_device.c src/indala.c src/main.c src/psk.c src/usb_descriptors.c src/util.c src/emulate.c src/ask.c src/fsk.c src/clock.c src/rwd.c src/detect.c src/hitagcrypto.c src/wiegand.c src/comms.c src/nvm.c src/mcp414x.c src/spi.c src/uart3.c src/tags.c src/unique.c src/led.c src/em.c src/hid.c src/read.c src/isr.c src/auto.c src/fdxb.c src/hitag.c src/uid.c src/login.c src/write.c src/auth.c src/q5.c src/vtag.c src/config.c src/select.c src/sdcard.c src/debug_pins.c src/awid.c src/analogue.c src/iso7816.c src/t55x7.c src/sniff.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/_ext/1209914024/FSIO.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1209914024" 
	@${RM} ${OBJECTDIR}/_ext/1209914024/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209914024/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209914024/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1209914024/FSIO.o.d" -o ${OBJECTDIR}/_ext/1209914024/FSIO.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/FSIO.c"   
	
${OBJECTDIR}/_ext/1209914024/SD-SPI.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1209914024" 
	@${RM} ${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209914024/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1209914024/SD-SPI.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/SD-SPI.c"   
	
${OBJECTDIR}/_ext/1019771169/SClib.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart\ Card/SClib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1019771169" 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SClib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SClib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1019771169/SClib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1019771169/SClib.o.d" -o ${OBJECTDIR}/_ext/1019771169/SClib.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SClib.c"   
	
${OBJECTDIR}/_ext/1019771169/SCpic32.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart\ Card/SCpic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1019771169" 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SCpic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SCpic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1019771169/SCpic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1019771169/SCpic32.o.d" -o ${OBJECTDIR}/_ext/1019771169/SCpic32.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SCpic32.c"   
	
${OBJECTDIR}/_ext/631258897/usb_function_cdc.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/631258897" 
	@${RM} ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/_ext/186742988/usb_device.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/186742988" 
	@${RM} ${OBJECTDIR}/_ext/186742988/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/186742988/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/186742988/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/186742988/usb_device.o.d" -o ${OBJECTDIR}/_ext/186742988/usb_device.o /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/usb_device.c   
	
${OBJECTDIR}/src/indala.o: src/indala.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/indala.o.d 
	@${RM} ${OBJECTDIR}/src/indala.o 
	@${FIXDEPS} "${OBJECTDIR}/src/indala.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/indala.o.d" -o ${OBJECTDIR}/src/indala.o src/indala.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
${OBJECTDIR}/src/psk.o: src/psk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/psk.o.d 
	@${RM} ${OBJECTDIR}/src/psk.o 
	@${FIXDEPS} "${OBJECTDIR}/src/psk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/psk.o.d" -o ${OBJECTDIR}/src/psk.o src/psk.c   
	
${OBJECTDIR}/src/usb_descriptors.o: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/usb_descriptors.o.d" -o ${OBJECTDIR}/src/usb_descriptors.o src/usb_descriptors.c   
	
${OBJECTDIR}/src/util.o: src/util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/util.o.d 
	@${RM} ${OBJECTDIR}/src/util.o 
	@${FIXDEPS} "${OBJECTDIR}/src/util.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/util.o.d" -o ${OBJECTDIR}/src/util.o src/util.c   
	
${OBJECTDIR}/src/emulate.o: src/emulate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/emulate.o.d 
	@${RM} ${OBJECTDIR}/src/emulate.o 
	@${FIXDEPS} "${OBJECTDIR}/src/emulate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/emulate.o.d" -o ${OBJECTDIR}/src/emulate.o src/emulate.c   
	
${OBJECTDIR}/src/ask.o: src/ask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ask.o.d 
	@${RM} ${OBJECTDIR}/src/ask.o 
	@${FIXDEPS} "${OBJECTDIR}/src/ask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/ask.o.d" -o ${OBJECTDIR}/src/ask.o src/ask.c   
	
${OBJECTDIR}/src/fsk.o: src/fsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fsk.o.d 
	@${RM} ${OBJECTDIR}/src/fsk.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/fsk.o.d" -o ${OBJECTDIR}/src/fsk.o src/fsk.c   
	
${OBJECTDIR}/src/clock.o: src/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/src/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/clock.o.d" -o ${OBJECTDIR}/src/clock.o src/clock.c   
	
${OBJECTDIR}/src/rwd.o: src/rwd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rwd.o.d 
	@${RM} ${OBJECTDIR}/src/rwd.o 
	@${FIXDEPS} "${OBJECTDIR}/src/rwd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/rwd.o.d" -o ${OBJECTDIR}/src/rwd.o src/rwd.c   
	
${OBJECTDIR}/src/detect.o: src/detect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/detect.o.d 
	@${RM} ${OBJECTDIR}/src/detect.o 
	@${FIXDEPS} "${OBJECTDIR}/src/detect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/detect.o.d" -o ${OBJECTDIR}/src/detect.o src/detect.c   
	
${OBJECTDIR}/src/hitagcrypto.o: src/hitagcrypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hitagcrypto.o.d 
	@${RM} ${OBJECTDIR}/src/hitagcrypto.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hitagcrypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/hitagcrypto.o.d" -o ${OBJECTDIR}/src/hitagcrypto.o src/hitagcrypto.c   
	
${OBJECTDIR}/src/wiegand.o: src/wiegand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/wiegand.o.d 
	@${RM} ${OBJECTDIR}/src/wiegand.o 
	@${FIXDEPS} "${OBJECTDIR}/src/wiegand.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/wiegand.o.d" -o ${OBJECTDIR}/src/wiegand.o src/wiegand.c   
	
${OBJECTDIR}/src/comms.o: src/comms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/comms.o.d 
	@${RM} ${OBJECTDIR}/src/comms.o 
	@${FIXDEPS} "${OBJECTDIR}/src/comms.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/comms.o.d" -o ${OBJECTDIR}/src/comms.o src/comms.c   
	
${OBJECTDIR}/src/nvm.o: src/nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/nvm.o.d 
	@${RM} ${OBJECTDIR}/src/nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/nvm.o.d" -o ${OBJECTDIR}/src/nvm.o src/nvm.c   
	
${OBJECTDIR}/src/mcp414x.o: src/mcp414x.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mcp414x.o.d 
	@${RM} ${OBJECTDIR}/src/mcp414x.o 
	@${FIXDEPS} "${OBJECTDIR}/src/mcp414x.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/mcp414x.o.d" -o ${OBJECTDIR}/src/mcp414x.o src/mcp414x.c   
	
${OBJECTDIR}/src/spi.o: src/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi.o.d 
	@${RM} ${OBJECTDIR}/src/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/src/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/spi.o.d" -o ${OBJECTDIR}/src/spi.o src/spi.c   
	
${OBJECTDIR}/src/uart3.o: src/uart3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/uart3.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uart3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/uart3.o.d" -o ${OBJECTDIR}/src/uart3.o src/uart3.c   
	
${OBJECTDIR}/src/tags.o: src/tags.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tags.o.d 
	@${RM} ${OBJECTDIR}/src/tags.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tags.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/tags.o.d" -o ${OBJECTDIR}/src/tags.o src/tags.c   
	
${OBJECTDIR}/src/unique.o: src/unique.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/unique.o.d 
	@${RM} ${OBJECTDIR}/src/unique.o 
	@${FIXDEPS} "${OBJECTDIR}/src/unique.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/unique.o.d" -o ${OBJECTDIR}/src/unique.o src/unique.c   
	
${OBJECTDIR}/src/led.o: src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/led.o.d 
	@${RM} ${OBJECTDIR}/src/led.o 
	@${FIXDEPS} "${OBJECTDIR}/src/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/led.o.d" -o ${OBJECTDIR}/src/led.o src/led.c   
	
${OBJECTDIR}/src/em.o: src/em.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/em.o.d 
	@${RM} ${OBJECTDIR}/src/em.o 
	@${FIXDEPS} "${OBJECTDIR}/src/em.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/em.o.d" -o ${OBJECTDIR}/src/em.o src/em.c   
	
${OBJECTDIR}/src/hid.o: src/hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hid.o.d 
	@${RM} ${OBJECTDIR}/src/hid.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/hid.o.d" -o ${OBJECTDIR}/src/hid.o src/hid.c   
	
${OBJECTDIR}/src/read.o: src/read.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/read.o.d 
	@${RM} ${OBJECTDIR}/src/read.o 
	@${FIXDEPS} "${OBJECTDIR}/src/read.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/read.o.d" -o ${OBJECTDIR}/src/read.o src/read.c   
	
${OBJECTDIR}/src/isr.o: src/isr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/isr.o.d 
	@${RM} ${OBJECTDIR}/src/isr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/isr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/isr.o.d" -o ${OBJECTDIR}/src/isr.o src/isr.c   
	
${OBJECTDIR}/src/auto.o: src/auto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/auto.o.d 
	@${RM} ${OBJECTDIR}/src/auto.o 
	@${FIXDEPS} "${OBJECTDIR}/src/auto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/auto.o.d" -o ${OBJECTDIR}/src/auto.o src/auto.c   
	
${OBJECTDIR}/src/fdxb.o: src/fdxb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fdxb.o.d 
	@${RM} ${OBJECTDIR}/src/fdxb.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fdxb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/fdxb.o.d" -o ${OBJECTDIR}/src/fdxb.o src/fdxb.c   
	
${OBJECTDIR}/src/hitag.o: src/hitag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hitag.o.d 
	@${RM} ${OBJECTDIR}/src/hitag.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hitag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/hitag.o.d" -o ${OBJECTDIR}/src/hitag.o src/hitag.c   
	
${OBJECTDIR}/src/uid.o: src/uid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uid.o.d 
	@${RM} ${OBJECTDIR}/src/uid.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/uid.o.d" -o ${OBJECTDIR}/src/uid.o src/uid.c   
	
${OBJECTDIR}/src/login.o: src/login.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/login.o.d 
	@${RM} ${OBJECTDIR}/src/login.o 
	@${FIXDEPS} "${OBJECTDIR}/src/login.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/login.o.d" -o ${OBJECTDIR}/src/login.o src/login.c   
	
${OBJECTDIR}/src/write.o: src/write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/write.o.d 
	@${RM} ${OBJECTDIR}/src/write.o 
	@${FIXDEPS} "${OBJECTDIR}/src/write.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/write.o.d" -o ${OBJECTDIR}/src/write.o src/write.c   
	
${OBJECTDIR}/src/auth.o: src/auth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/auth.o.d 
	@${RM} ${OBJECTDIR}/src/auth.o 
	@${FIXDEPS} "${OBJECTDIR}/src/auth.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/auth.o.d" -o ${OBJECTDIR}/src/auth.o src/auth.c   
	
${OBJECTDIR}/src/q5.o: src/q5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/q5.o.d 
	@${RM} ${OBJECTDIR}/src/q5.o 
	@${FIXDEPS} "${OBJECTDIR}/src/q5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/q5.o.d" -o ${OBJECTDIR}/src/q5.o src/q5.c   
	
${OBJECTDIR}/src/vtag.o: src/vtag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/vtag.o.d 
	@${RM} ${OBJECTDIR}/src/vtag.o 
	@${FIXDEPS} "${OBJECTDIR}/src/vtag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/vtag.o.d" -o ${OBJECTDIR}/src/vtag.o src/vtag.c   
	
${OBJECTDIR}/src/config.o: src/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	@${FIXDEPS} "${OBJECTDIR}/src/config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c   
	
${OBJECTDIR}/src/select.o: src/select.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/select.o.d 
	@${RM} ${OBJECTDIR}/src/select.o 
	@${FIXDEPS} "${OBJECTDIR}/src/select.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/select.o.d" -o ${OBJECTDIR}/src/select.o src/select.c   
	
${OBJECTDIR}/src/sdcard.o: src/sdcard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sdcard.o.d 
	@${RM} ${OBJECTDIR}/src/sdcard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sdcard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/sdcard.o.d" -o ${OBJECTDIR}/src/sdcard.o src/sdcard.c   
	
${OBJECTDIR}/src/debug_pins.o: src/debug_pins.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/debug_pins.o.d 
	@${RM} ${OBJECTDIR}/src/debug_pins.o 
	@${FIXDEPS} "${OBJECTDIR}/src/debug_pins.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/debug_pins.o.d" -o ${OBJECTDIR}/src/debug_pins.o src/debug_pins.c   
	
${OBJECTDIR}/src/awid.o: src/awid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/awid.o.d 
	@${RM} ${OBJECTDIR}/src/awid.o 
	@${FIXDEPS} "${OBJECTDIR}/src/awid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/awid.o.d" -o ${OBJECTDIR}/src/awid.o src/awid.c   
	
${OBJECTDIR}/src/analogue.o: src/analogue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/analogue.o.d 
	@${RM} ${OBJECTDIR}/src/analogue.o 
	@${FIXDEPS} "${OBJECTDIR}/src/analogue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/analogue.o.d" -o ${OBJECTDIR}/src/analogue.o src/analogue.c   
	
${OBJECTDIR}/src/iso7816.o: src/iso7816.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/iso7816.o.d 
	@${RM} ${OBJECTDIR}/src/iso7816.o 
	@${FIXDEPS} "${OBJECTDIR}/src/iso7816.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/iso7816.o.d" -o ${OBJECTDIR}/src/iso7816.o src/iso7816.c   
	
${OBJECTDIR}/src/t55x7.o: src/t55x7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/t55x7.o.d 
	@${RM} ${OBJECTDIR}/src/t55x7.o 
	@${FIXDEPS} "${OBJECTDIR}/src/t55x7.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/t55x7.o.d" -o ${OBJECTDIR}/src/t55x7.o src/t55x7.c   
	
${OBJECTDIR}/src/sniff.o: src/sniff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sniff.o.d 
	@${RM} ${OBJECTDIR}/src/sniff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sniff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/sniff.o.d" -o ${OBJECTDIR}/src/sniff.o src/sniff.c   
	
else
${OBJECTDIR}/_ext/1209914024/FSIO.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1209914024" 
	@${RM} ${OBJECTDIR}/_ext/1209914024/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209914024/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209914024/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1209914024/FSIO.o.d" -o ${OBJECTDIR}/_ext/1209914024/FSIO.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/FSIO.c"   
	
${OBJECTDIR}/_ext/1209914024/SD-SPI.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1209914024" 
	@${RM} ${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1209914024/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1209914024/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1209914024/SD-SPI.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/MDD File System/SD-SPI.c"   
	
${OBJECTDIR}/_ext/1019771169/SClib.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart\ Card/SClib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1019771169" 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SClib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SClib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1019771169/SClib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1019771169/SClib.o.d" -o ${OBJECTDIR}/_ext/1019771169/SClib.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SClib.c"   
	
${OBJECTDIR}/_ext/1019771169/SCpic32.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart\ Card/SCpic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1019771169" 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SCpic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019771169/SCpic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1019771169/SCpic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1019771169/SCpic32.o.d" -o ${OBJECTDIR}/_ext/1019771169/SCpic32.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Smart Card/SCpic32.c"   
	
${OBJECTDIR}/_ext/631258897/usb_function_cdc.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/631258897" 
	@${RM} ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/631258897/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/631258897/usb_function_cdc.o "/opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/CDC Device Driver/usb_function_cdc.c"   
	
${OBJECTDIR}/_ext/186742988/usb_device.o: /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/186742988" 
	@${RM} ${OBJECTDIR}/_ext/186742988/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/186742988/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/186742988/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/_ext/186742988/usb_device.o.d" -o ${OBJECTDIR}/_ext/186742988/usb_device.o /opt/microchip/microchip_solutions_v2013-06-15/Microchip/USB/usb_device.c   
	
${OBJECTDIR}/src/indala.o: src/indala.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/indala.o.d 
	@${RM} ${OBJECTDIR}/src/indala.o 
	@${FIXDEPS} "${OBJECTDIR}/src/indala.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/indala.o.d" -o ${OBJECTDIR}/src/indala.o src/indala.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
${OBJECTDIR}/src/psk.o: src/psk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/psk.o.d 
	@${RM} ${OBJECTDIR}/src/psk.o 
	@${FIXDEPS} "${OBJECTDIR}/src/psk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/psk.o.d" -o ${OBJECTDIR}/src/psk.o src/psk.c   
	
${OBJECTDIR}/src/usb_descriptors.o: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/usb_descriptors.o.d" -o ${OBJECTDIR}/src/usb_descriptors.o src/usb_descriptors.c   
	
${OBJECTDIR}/src/util.o: src/util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/util.o.d 
	@${RM} ${OBJECTDIR}/src/util.o 
	@${FIXDEPS} "${OBJECTDIR}/src/util.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/util.o.d" -o ${OBJECTDIR}/src/util.o src/util.c   
	
${OBJECTDIR}/src/emulate.o: src/emulate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/emulate.o.d 
	@${RM} ${OBJECTDIR}/src/emulate.o 
	@${FIXDEPS} "${OBJECTDIR}/src/emulate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/emulate.o.d" -o ${OBJECTDIR}/src/emulate.o src/emulate.c   
	
${OBJECTDIR}/src/ask.o: src/ask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ask.o.d 
	@${RM} ${OBJECTDIR}/src/ask.o 
	@${FIXDEPS} "${OBJECTDIR}/src/ask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/ask.o.d" -o ${OBJECTDIR}/src/ask.o src/ask.c   
	
${OBJECTDIR}/src/fsk.o: src/fsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fsk.o.d 
	@${RM} ${OBJECTDIR}/src/fsk.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/fsk.o.d" -o ${OBJECTDIR}/src/fsk.o src/fsk.c   
	
${OBJECTDIR}/src/clock.o: src/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/src/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/clock.o.d" -o ${OBJECTDIR}/src/clock.o src/clock.c   
	
${OBJECTDIR}/src/rwd.o: src/rwd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rwd.o.d 
	@${RM} ${OBJECTDIR}/src/rwd.o 
	@${FIXDEPS} "${OBJECTDIR}/src/rwd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/rwd.o.d" -o ${OBJECTDIR}/src/rwd.o src/rwd.c   
	
${OBJECTDIR}/src/detect.o: src/detect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/detect.o.d 
	@${RM} ${OBJECTDIR}/src/detect.o 
	@${FIXDEPS} "${OBJECTDIR}/src/detect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/detect.o.d" -o ${OBJECTDIR}/src/detect.o src/detect.c   
	
${OBJECTDIR}/src/hitagcrypto.o: src/hitagcrypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hitagcrypto.o.d 
	@${RM} ${OBJECTDIR}/src/hitagcrypto.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hitagcrypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/hitagcrypto.o.d" -o ${OBJECTDIR}/src/hitagcrypto.o src/hitagcrypto.c   
	
${OBJECTDIR}/src/wiegand.o: src/wiegand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/wiegand.o.d 
	@${RM} ${OBJECTDIR}/src/wiegand.o 
	@${FIXDEPS} "${OBJECTDIR}/src/wiegand.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/wiegand.o.d" -o ${OBJECTDIR}/src/wiegand.o src/wiegand.c   
	
${OBJECTDIR}/src/comms.o: src/comms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/comms.o.d 
	@${RM} ${OBJECTDIR}/src/comms.o 
	@${FIXDEPS} "${OBJECTDIR}/src/comms.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/comms.o.d" -o ${OBJECTDIR}/src/comms.o src/comms.c   
	
${OBJECTDIR}/src/nvm.o: src/nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/nvm.o.d 
	@${RM} ${OBJECTDIR}/src/nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/nvm.o.d" -o ${OBJECTDIR}/src/nvm.o src/nvm.c   
	
${OBJECTDIR}/src/mcp414x.o: src/mcp414x.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mcp414x.o.d 
	@${RM} ${OBJECTDIR}/src/mcp414x.o 
	@${FIXDEPS} "${OBJECTDIR}/src/mcp414x.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/mcp414x.o.d" -o ${OBJECTDIR}/src/mcp414x.o src/mcp414x.c   
	
${OBJECTDIR}/src/spi.o: src/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi.o.d 
	@${RM} ${OBJECTDIR}/src/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/src/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/spi.o.d" -o ${OBJECTDIR}/src/spi.o src/spi.c   
	
${OBJECTDIR}/src/uart3.o: src/uart3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/uart3.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uart3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/uart3.o.d" -o ${OBJECTDIR}/src/uart3.o src/uart3.c   
	
${OBJECTDIR}/src/tags.o: src/tags.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tags.o.d 
	@${RM} ${OBJECTDIR}/src/tags.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tags.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/tags.o.d" -o ${OBJECTDIR}/src/tags.o src/tags.c   
	
${OBJECTDIR}/src/unique.o: src/unique.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/unique.o.d 
	@${RM} ${OBJECTDIR}/src/unique.o 
	@${FIXDEPS} "${OBJECTDIR}/src/unique.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/unique.o.d" -o ${OBJECTDIR}/src/unique.o src/unique.c   
	
${OBJECTDIR}/src/led.o: src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/led.o.d 
	@${RM} ${OBJECTDIR}/src/led.o 
	@${FIXDEPS} "${OBJECTDIR}/src/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/led.o.d" -o ${OBJECTDIR}/src/led.o src/led.c   
	
${OBJECTDIR}/src/em.o: src/em.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/em.o.d 
	@${RM} ${OBJECTDIR}/src/em.o 
	@${FIXDEPS} "${OBJECTDIR}/src/em.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/em.o.d" -o ${OBJECTDIR}/src/em.o src/em.c   
	
${OBJECTDIR}/src/hid.o: src/hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hid.o.d 
	@${RM} ${OBJECTDIR}/src/hid.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/hid.o.d" -o ${OBJECTDIR}/src/hid.o src/hid.c   
	
${OBJECTDIR}/src/read.o: src/read.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/read.o.d 
	@${RM} ${OBJECTDIR}/src/read.o 
	@${FIXDEPS} "${OBJECTDIR}/src/read.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/read.o.d" -o ${OBJECTDIR}/src/read.o src/read.c   
	
${OBJECTDIR}/src/isr.o: src/isr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/isr.o.d 
	@${RM} ${OBJECTDIR}/src/isr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/isr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/isr.o.d" -o ${OBJECTDIR}/src/isr.o src/isr.c   
	
${OBJECTDIR}/src/auto.o: src/auto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/auto.o.d 
	@${RM} ${OBJECTDIR}/src/auto.o 
	@${FIXDEPS} "${OBJECTDIR}/src/auto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/auto.o.d" -o ${OBJECTDIR}/src/auto.o src/auto.c   
	
${OBJECTDIR}/src/fdxb.o: src/fdxb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fdxb.o.d 
	@${RM} ${OBJECTDIR}/src/fdxb.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fdxb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/fdxb.o.d" -o ${OBJECTDIR}/src/fdxb.o src/fdxb.c   
	
${OBJECTDIR}/src/hitag.o: src/hitag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/hitag.o.d 
	@${RM} ${OBJECTDIR}/src/hitag.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hitag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/hitag.o.d" -o ${OBJECTDIR}/src/hitag.o src/hitag.c   
	
${OBJECTDIR}/src/uid.o: src/uid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uid.o.d 
	@${RM} ${OBJECTDIR}/src/uid.o 
	@${FIXDEPS} "${OBJECTDIR}/src/uid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/uid.o.d" -o ${OBJECTDIR}/src/uid.o src/uid.c   
	
${OBJECTDIR}/src/login.o: src/login.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/login.o.d 
	@${RM} ${OBJECTDIR}/src/login.o 
	@${FIXDEPS} "${OBJECTDIR}/src/login.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/login.o.d" -o ${OBJECTDIR}/src/login.o src/login.c   
	
${OBJECTDIR}/src/write.o: src/write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/write.o.d 
	@${RM} ${OBJECTDIR}/src/write.o 
	@${FIXDEPS} "${OBJECTDIR}/src/write.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/write.o.d" -o ${OBJECTDIR}/src/write.o src/write.c   
	
${OBJECTDIR}/src/auth.o: src/auth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/auth.o.d 
	@${RM} ${OBJECTDIR}/src/auth.o 
	@${FIXDEPS} "${OBJECTDIR}/src/auth.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/auth.o.d" -o ${OBJECTDIR}/src/auth.o src/auth.c   
	
${OBJECTDIR}/src/q5.o: src/q5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/q5.o.d 
	@${RM} ${OBJECTDIR}/src/q5.o 
	@${FIXDEPS} "${OBJECTDIR}/src/q5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/q5.o.d" -o ${OBJECTDIR}/src/q5.o src/q5.c   
	
${OBJECTDIR}/src/vtag.o: src/vtag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/vtag.o.d 
	@${RM} ${OBJECTDIR}/src/vtag.o 
	@${FIXDEPS} "${OBJECTDIR}/src/vtag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/vtag.o.d" -o ${OBJECTDIR}/src/vtag.o src/vtag.c   
	
${OBJECTDIR}/src/config.o: src/config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	@${FIXDEPS} "${OBJECTDIR}/src/config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c   
	
${OBJECTDIR}/src/select.o: src/select.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/select.o.d 
	@${RM} ${OBJECTDIR}/src/select.o 
	@${FIXDEPS} "${OBJECTDIR}/src/select.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/select.o.d" -o ${OBJECTDIR}/src/select.o src/select.c   
	
${OBJECTDIR}/src/sdcard.o: src/sdcard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sdcard.o.d 
	@${RM} ${OBJECTDIR}/src/sdcard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sdcard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/sdcard.o.d" -o ${OBJECTDIR}/src/sdcard.o src/sdcard.c   
	
${OBJECTDIR}/src/debug_pins.o: src/debug_pins.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/debug_pins.o.d 
	@${RM} ${OBJECTDIR}/src/debug_pins.o 
	@${FIXDEPS} "${OBJECTDIR}/src/debug_pins.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/debug_pins.o.d" -o ${OBJECTDIR}/src/debug_pins.o src/debug_pins.c   
	
${OBJECTDIR}/src/awid.o: src/awid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/awid.o.d 
	@${RM} ${OBJECTDIR}/src/awid.o 
	@${FIXDEPS} "${OBJECTDIR}/src/awid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/awid.o.d" -o ${OBJECTDIR}/src/awid.o src/awid.c   
	
${OBJECTDIR}/src/analogue.o: src/analogue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/analogue.o.d 
	@${RM} ${OBJECTDIR}/src/analogue.o 
	@${FIXDEPS} "${OBJECTDIR}/src/analogue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/analogue.o.d" -o ${OBJECTDIR}/src/analogue.o src/analogue.c   
	
${OBJECTDIR}/src/iso7816.o: src/iso7816.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/iso7816.o.d 
	@${RM} ${OBJECTDIR}/src/iso7816.o 
	@${FIXDEPS} "${OBJECTDIR}/src/iso7816.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/iso7816.o.d" -o ${OBJECTDIR}/src/iso7816.o src/iso7816.c   
	
${OBJECTDIR}/src/t55x7.o: src/t55x7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/t55x7.o.d 
	@${RM} ${OBJECTDIR}/src/t55x7.o 
	@${FIXDEPS} "${OBJECTDIR}/src/t55x7.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/t55x7.o.d" -o ${OBJECTDIR}/src/t55x7.o src/t55x7.c   
	
${OBJECTDIR}/src/sniff.o: src/sniff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sniff.o.d 
	@${RM} ${OBJECTDIR}/src/sniff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sniff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -DVERSION=`git rev-list HEAD --count` -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include" -I"/opt/microchip/microchip_solutions_v2013-06-15/Microchip/Include/USB" -I"/opt/microchip/xc32/v1.21/pic32-libs/include" -I"./include" -MMD -MF "${OBJECTDIR}/src/sniff.o.d" -o ${OBJECTDIR}/src/sniff.o src/sniff.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  /opt/microchip/xc32/v1.34/pic32mx/lib/libmchp_peripheral_32MX795F512L.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    /opt/microchip/xc32/v1.34/pic32mx/lib/libmchp_peripheral_32MX795F512L.a       -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  /opt/microchip/xc32/v1.34/pic32mx/lib/libmchp_peripheral_32MX795F512L.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    /opt/microchip/xc32/v1.34/pic32mx/lib/libmchp_peripheral_32MX795F512L.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/RFIDler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
