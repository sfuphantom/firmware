################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../VCU/source/sys_link.cmd 

ASM_SRCS += \
../VCU/source/dabort.asm \
../VCU/source/sys_core.asm \
../VCU/source/sys_intvecs.asm \
../VCU/source/sys_mpu.asm \
../VCU/source/sys_pmu.asm 

C_SRCS += \
../VCU/source/adc.c \
../VCU/source/can.c \
../VCU/source/crc.c \
../VCU/source/dcc.c \
../VCU/source/ecap.c \
../VCU/source/eqep.c \
../VCU/source/esm.c \
../VCU/source/etpwm.c \
../VCU/source/gio.c \
../VCU/source/het.c \
../VCU/source/i2c.c \
../VCU/source/lin.c \
../VCU/source/mibspi.c \
../VCU/source/notification.c \
../VCU/source/pinmux.c \
../VCU/source/rti.c \
../VCU/source/sci.c \
../VCU/source/spi.c \
../VCU/source/sys_dma.c \
../VCU/source/sys_main.c \
../VCU/source/sys_pcr.c \
../VCU/source/sys_phantom.c \
../VCU/source/sys_pmm.c \
../VCU/source/sys_selftest.c \
../VCU/source/sys_startup.c \
../VCU/source/sys_vim.c \
../VCU/source/system.c 

C_DEPS += \
./VCU/source/adc.d \
./VCU/source/can.d \
./VCU/source/crc.d \
./VCU/source/dcc.d \
./VCU/source/ecap.d \
./VCU/source/eqep.d \
./VCU/source/esm.d \
./VCU/source/etpwm.d \
./VCU/source/gio.d \
./VCU/source/het.d \
./VCU/source/i2c.d \
./VCU/source/lin.d \
./VCU/source/mibspi.d \
./VCU/source/notification.d \
./VCU/source/pinmux.d \
./VCU/source/rti.d \
./VCU/source/sci.d \
./VCU/source/spi.d \
./VCU/source/sys_dma.d \
./VCU/source/sys_main.d \
./VCU/source/sys_pcr.d \
./VCU/source/sys_phantom.d \
./VCU/source/sys_pmm.d \
./VCU/source/sys_selftest.d \
./VCU/source/sys_startup.d \
./VCU/source/sys_vim.d \
./VCU/source/system.d 

OBJS += \
./VCU/source/adc.obj \
./VCU/source/can.obj \
./VCU/source/crc.obj \
./VCU/source/dabort.obj \
./VCU/source/dcc.obj \
./VCU/source/ecap.obj \
./VCU/source/eqep.obj \
./VCU/source/esm.obj \
./VCU/source/etpwm.obj \
./VCU/source/gio.obj \
./VCU/source/het.obj \
./VCU/source/i2c.obj \
./VCU/source/lin.obj \
./VCU/source/mibspi.obj \
./VCU/source/notification.obj \
./VCU/source/pinmux.obj \
./VCU/source/rti.obj \
./VCU/source/sci.obj \
./VCU/source/spi.obj \
./VCU/source/sys_core.obj \
./VCU/source/sys_dma.obj \
./VCU/source/sys_intvecs.obj \
./VCU/source/sys_main.obj \
./VCU/source/sys_mpu.obj \
./VCU/source/sys_pcr.obj \
./VCU/source/sys_phantom.obj \
./VCU/source/sys_pmm.obj \
./VCU/source/sys_pmu.obj \
./VCU/source/sys_selftest.obj \
./VCU/source/sys_startup.obj \
./VCU/source/sys_vim.obj \
./VCU/source/system.obj 

ASM_DEPS += \
./VCU/source/dabort.d \
./VCU/source/sys_core.d \
./VCU/source/sys_intvecs.d \
./VCU/source/sys_mpu.d \
./VCU/source/sys_pmu.d 

OBJS__QUOTED += \
"VCU\source\adc.obj" \
"VCU\source\can.obj" \
"VCU\source\crc.obj" \
"VCU\source\dabort.obj" \
"VCU\source\dcc.obj" \
"VCU\source\ecap.obj" \
"VCU\source\eqep.obj" \
"VCU\source\esm.obj" \
"VCU\source\etpwm.obj" \
"VCU\source\gio.obj" \
"VCU\source\het.obj" \
"VCU\source\i2c.obj" \
"VCU\source\lin.obj" \
"VCU\source\mibspi.obj" \
"VCU\source\notification.obj" \
"VCU\source\pinmux.obj" \
"VCU\source\rti.obj" \
"VCU\source\sci.obj" \
"VCU\source\spi.obj" \
"VCU\source\sys_core.obj" \
"VCU\source\sys_dma.obj" \
"VCU\source\sys_intvecs.obj" \
"VCU\source\sys_main.obj" \
"VCU\source\sys_mpu.obj" \
"VCU\source\sys_pcr.obj" \
"VCU\source\sys_phantom.obj" \
"VCU\source\sys_pmm.obj" \
"VCU\source\sys_pmu.obj" \
"VCU\source\sys_selftest.obj" \
"VCU\source\sys_startup.obj" \
"VCU\source\sys_vim.obj" \
"VCU\source\system.obj" 

C_DEPS__QUOTED += \
"VCU\source\adc.d" \
"VCU\source\can.d" \
"VCU\source\crc.d" \
"VCU\source\dcc.d" \
"VCU\source\ecap.d" \
"VCU\source\eqep.d" \
"VCU\source\esm.d" \
"VCU\source\etpwm.d" \
"VCU\source\gio.d" \
"VCU\source\het.d" \
"VCU\source\i2c.d" \
"VCU\source\lin.d" \
"VCU\source\mibspi.d" \
"VCU\source\notification.d" \
"VCU\source\pinmux.d" \
"VCU\source\rti.d" \
"VCU\source\sci.d" \
"VCU\source\spi.d" \
"VCU\source\sys_dma.d" \
"VCU\source\sys_main.d" \
"VCU\source\sys_pcr.d" \
"VCU\source\sys_phantom.d" \
"VCU\source\sys_pmm.d" \
"VCU\source\sys_selftest.d" \
"VCU\source\sys_startup.d" \
"VCU\source\sys_vim.d" \
"VCU\source\system.d" 

ASM_DEPS__QUOTED += \
"VCU\source\dabort.d" \
"VCU\source\sys_core.d" \
"VCU\source\sys_intvecs.d" \
"VCU\source\sys_mpu.d" \
"VCU\source\sys_pmu.d" 

C_SRCS__QUOTED += \
"../VCU/source/adc.c" \
"../VCU/source/can.c" \
"../VCU/source/crc.c" \
"../VCU/source/dcc.c" \
"../VCU/source/ecap.c" \
"../VCU/source/eqep.c" \
"../VCU/source/esm.c" \
"../VCU/source/etpwm.c" \
"../VCU/source/gio.c" \
"../VCU/source/het.c" \
"../VCU/source/i2c.c" \
"../VCU/source/lin.c" \
"../VCU/source/mibspi.c" \
"../VCU/source/notification.c" \
"../VCU/source/pinmux.c" \
"../VCU/source/rti.c" \
"../VCU/source/sci.c" \
"../VCU/source/spi.c" \
"../VCU/source/sys_dma.c" \
"../VCU/source/sys_main.c" \
"../VCU/source/sys_pcr.c" \
"../VCU/source/sys_phantom.c" \
"../VCU/source/sys_pmm.c" \
"../VCU/source/sys_selftest.c" \
"../VCU/source/sys_startup.c" \
"../VCU/source/sys_vim.c" \
"../VCU/source/system.c" 

ASM_SRCS__QUOTED += \
"../VCU/source/dabort.asm" \
"../VCU/source/sys_core.asm" \
"../VCU/source/sys_intvecs.asm" \
"../VCU/source/sys_mpu.asm" \
"../VCU/source/sys_pmu.asm" 


