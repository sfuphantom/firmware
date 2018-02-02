################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../source/sys_link.cmd 

ASM_SRCS += \
../source/dabort.asm \
../source/sys_core.asm \
../source/sys_intvecs.asm \
../source/sys_mpu.asm \
../source/sys_pmu.asm 

C_SRCS += \
../source/A_LCD.c \
../source/A_PID.c \
../source/A_control_methods.c \
../source/A_exception_handler.c \
../source/adc.c \
../source/alarmLogic.c \
../source/can.c \
../source/esm.c \
../source/gio.c \
../source/het.c \
../source/i2c.c \
../source/inputOutput.c \
../source/mainStateMachine.c \
../source/notification.c \
../source/pinmux.c \
../source/rti.c \
../source/sci.c \
../source/sys_dma.c \
../source/sys_main.c \
../source/sys_pcr.c \
../source/sys_phantom.c \
../source/sys_pmm.c \
../source/sys_selftest.c \
../source/sys_startup.c \
../source/sys_vim.c \
../source/system.c \
../source/utilities.c 

C_DEPS += \
./source/A_LCD.d \
./source/A_PID.d \
./source/A_control_methods.d \
./source/A_exception_handler.d \
./source/adc.d \
./source/alarmLogic.d \
./source/can.d \
./source/esm.d \
./source/gio.d \
./source/het.d \
./source/i2c.d \
./source/inputOutput.d \
./source/mainStateMachine.d \
./source/notification.d \
./source/pinmux.d \
./source/rti.d \
./source/sci.d \
./source/sys_dma.d \
./source/sys_main.d \
./source/sys_pcr.d \
./source/sys_phantom.d \
./source/sys_pmm.d \
./source/sys_selftest.d \
./source/sys_startup.d \
./source/sys_vim.d \
./source/system.d \
./source/utilities.d 

OBJS += \
./source/A_LCD.obj \
./source/A_PID.obj \
./source/A_control_methods.obj \
./source/A_exception_handler.obj \
./source/adc.obj \
./source/alarmLogic.obj \
./source/can.obj \
./source/dabort.obj \
./source/esm.obj \
./source/gio.obj \
./source/het.obj \
./source/i2c.obj \
./source/inputOutput.obj \
./source/mainStateMachine.obj \
./source/notification.obj \
./source/pinmux.obj \
./source/rti.obj \
./source/sci.obj \
./source/sys_core.obj \
./source/sys_dma.obj \
./source/sys_intvecs.obj \
./source/sys_main.obj \
./source/sys_mpu.obj \
./source/sys_pcr.obj \
./source/sys_phantom.obj \
./source/sys_pmm.obj \
./source/sys_pmu.obj \
./source/sys_selftest.obj \
./source/sys_startup.obj \
./source/sys_vim.obj \
./source/system.obj \
./source/utilities.obj 

ASM_DEPS += \
./source/dabort.d \
./source/sys_core.d \
./source/sys_intvecs.d \
./source/sys_mpu.d \
./source/sys_pmu.d 

OBJS__QUOTED += \
"source\A_LCD.obj" \
"source\A_PID.obj" \
"source\A_control_methods.obj" \
"source\A_exception_handler.obj" \
"source\adc.obj" \
"source\alarmLogic.obj" \
"source\can.obj" \
"source\dabort.obj" \
"source\esm.obj" \
"source\gio.obj" \
"source\het.obj" \
"source\i2c.obj" \
"source\inputOutput.obj" \
"source\mainStateMachine.obj" \
"source\notification.obj" \
"source\pinmux.obj" \
"source\rti.obj" \
"source\sci.obj" \
"source\sys_core.obj" \
"source\sys_dma.obj" \
"source\sys_intvecs.obj" \
"source\sys_main.obj" \
"source\sys_mpu.obj" \
"source\sys_pcr.obj" \
"source\sys_phantom.obj" \
"source\sys_pmm.obj" \
"source\sys_pmu.obj" \
"source\sys_selftest.obj" \
"source\sys_startup.obj" \
"source\sys_vim.obj" \
"source\system.obj" \
"source\utilities.obj" 

C_DEPS__QUOTED += \
"source\A_LCD.d" \
"source\A_PID.d" \
"source\A_control_methods.d" \
"source\A_exception_handler.d" \
"source\adc.d" \
"source\alarmLogic.d" \
"source\can.d" \
"source\esm.d" \
"source\gio.d" \
"source\het.d" \
"source\i2c.d" \
"source\inputOutput.d" \
"source\mainStateMachine.d" \
"source\notification.d" \
"source\pinmux.d" \
"source\rti.d" \
"source\sci.d" \
"source\sys_dma.d" \
"source\sys_main.d" \
"source\sys_pcr.d" \
"source\sys_phantom.d" \
"source\sys_pmm.d" \
"source\sys_selftest.d" \
"source\sys_startup.d" \
"source\sys_vim.d" \
"source\system.d" \
"source\utilities.d" 

ASM_DEPS__QUOTED += \
"source\dabort.d" \
"source\sys_core.d" \
"source\sys_intvecs.d" \
"source\sys_mpu.d" \
"source\sys_pmu.d" 

C_SRCS__QUOTED += \
"../source/A_LCD.c" \
"../source/A_PID.c" \
"../source/A_control_methods.c" \
"../source/A_exception_handler.c" \
"../source/adc.c" \
"../source/alarmLogic.c" \
"../source/can.c" \
"../source/esm.c" \
"../source/gio.c" \
"../source/het.c" \
"../source/i2c.c" \
"../source/inputOutput.c" \
"../source/mainStateMachine.c" \
"../source/notification.c" \
"../source/pinmux.c" \
"../source/rti.c" \
"../source/sci.c" \
"../source/sys_dma.c" \
"../source/sys_main.c" \
"../source/sys_pcr.c" \
"../source/sys_phantom.c" \
"../source/sys_pmm.c" \
"../source/sys_selftest.c" \
"../source/sys_startup.c" \
"../source/sys_vim.c" \
"../source/system.c" \
"../source/utilities.c" 

ASM_SRCS__QUOTED += \
"../source/dabort.asm" \
"../source/sys_core.asm" \
"../source/sys_intvecs.asm" \
"../source/sys_mpu.asm" \
"../source/sys_pmu.asm" 


