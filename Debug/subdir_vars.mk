################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/cmd/28069_RAM_lnk.cmd \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_headers/cmd/F2806x_Headers_nonBIOS.cmd 

ASM_SRCS += \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_CodeStartBranch.asm \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_usDelay.asm 

C_SRCS += \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_CpuTimers.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_DefaultIsr.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_headers/source/F2806x_GlobalVariableDefs.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_Gpio.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_PieCtrl.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_PieVect.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_Sci.c \
C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_SysCtrl.c \
C:/controlSUITE/device_support/f2806x/v130/MWare/utils/cmdline.c \
../console.c \
C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/interrupt.c \
../jpmc.c \
C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/sysctl.c \
C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/uart.c \
C:/controlSUITE/device_support/f2806x/v130/MWare/utils/uartstdio.c 

OBJS += \
./F2806x_CodeStartBranch.obj \
./F2806x_CpuTimers.obj \
./F2806x_DefaultIsr.obj \
./F2806x_GlobalVariableDefs.obj \
./F2806x_Gpio.obj \
./F2806x_PieCtrl.obj \
./F2806x_PieVect.obj \
./F2806x_Sci.obj \
./F2806x_SysCtrl.obj \
./F2806x_usDelay.obj \
./cmdline.obj \
./console.obj \
./interrupt.obj \
./jpmc.obj \
./sysctl.obj \
./uart.obj \
./uartstdio.obj 

ASM_DEPS += \
./F2806x_CodeStartBranch.pp \
./F2806x_usDelay.pp 

C_DEPS += \
./F2806x_CpuTimers.pp \
./F2806x_DefaultIsr.pp \
./F2806x_GlobalVariableDefs.pp \
./F2806x_Gpio.pp \
./F2806x_PieCtrl.pp \
./F2806x_PieVect.pp \
./F2806x_Sci.pp \
./F2806x_SysCtrl.pp \
./cmdline.pp \
./console.pp \
./interrupt.pp \
./jpmc.pp \
./sysctl.pp \
./uart.pp \
./uartstdio.pp 

C_DEPS__QUOTED += \
"F2806x_CpuTimers.pp" \
"F2806x_DefaultIsr.pp" \
"F2806x_GlobalVariableDefs.pp" \
"F2806x_Gpio.pp" \
"F2806x_PieCtrl.pp" \
"F2806x_PieVect.pp" \
"F2806x_Sci.pp" \
"F2806x_SysCtrl.pp" \
"cmdline.pp" \
"console.pp" \
"interrupt.pp" \
"jpmc.pp" \
"sysctl.pp" \
"uart.pp" \
"uartstdio.pp" 

OBJS__QUOTED += \
"F2806x_CodeStartBranch.obj" \
"F2806x_CpuTimers.obj" \
"F2806x_DefaultIsr.obj" \
"F2806x_GlobalVariableDefs.obj" \
"F2806x_Gpio.obj" \
"F2806x_PieCtrl.obj" \
"F2806x_PieVect.obj" \
"F2806x_Sci.obj" \
"F2806x_SysCtrl.obj" \
"F2806x_usDelay.obj" \
"cmdline.obj" \
"console.obj" \
"interrupt.obj" \
"jpmc.obj" \
"sysctl.obj" \
"uart.obj" \
"uartstdio.obj" 

ASM_DEPS__QUOTED += \
"F2806x_CodeStartBranch.pp" \
"F2806x_usDelay.pp" 

ASM_SRCS__QUOTED += \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_CodeStartBranch.asm" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_usDelay.asm" 

C_SRCS__QUOTED += \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_CpuTimers.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_DefaultIsr.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_headers/source/F2806x_GlobalVariableDefs.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_Gpio.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_PieCtrl.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_PieVect.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_Sci.c" \
"C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_SysCtrl.c" \
"C:/controlSUITE/device_support/f2806x/v130/MWare/utils/cmdline.c" \
"../console.c" \
"C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/interrupt.c" \
"../jpmc.c" \
"C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/sysctl.c" \
"C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/uart.c" \
"C:/controlSUITE/device_support/f2806x/v130/MWare/utils/uartstdio.c" 


