################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../source/dabort.asm \
../source/sys_core.asm \
../source/sys_intvecs.asm \
../source/sys_mpu.asm \
../source/sys_pmu.asm 

C_SRCS += \
../source/BMS_Tester_Board_Thermistor_Firmware.c \
../source/errata_SSWF021_45.c \
../source/esm.c \
../source/gio.c \
../source/lin.c \
../source/mibspi.c \
../source/notification.c \
../source/pinmux.c \
../source/sci.c \
../source/sys_dma.c \
../source/sys_main.c \
../source/sys_pcr.c \
../source/sys_phantom.c \
../source/sys_pmm.c \
../source/sys_selftest.c \
../source/sys_startup.c \
../source/sys_vim.c \
../source/system.c 

OBJS += \
./source/BMS_Tester_Board_Thermistor_Firmware.o \
./source/dabort.o \
./source/errata_SSWF021_45.o \
./source/esm.o \
./source/gio.o \
./source/lin.o \
./source/mibspi.o \
./source/notification.o \
./source/pinmux.o \
./source/sci.o \
./source/sys_core.o \
./source/sys_dma.o \
./source/sys_intvecs.o \
./source/sys_main.o \
./source/sys_mpu.o \
./source/sys_pcr.o \
./source/sys_phantom.o \
./source/sys_pmm.o \
./source/sys_pmu.o \
./source/sys_selftest.o \
./source/sys_startup.o \
./source/sys_vim.o \
./source/system.o 

C_DEPS += \
./source/BMS_Tester_Board_Thermistor_Firmware.d \
./source/errata_SSWF021_45.d \
./source/esm.d \
./source/gio.d \
./source/lin.d \
./source/mibspi.d \
./source/notification.d \
./source/pinmux.d \
./source/sci.d \
./source/sys_dma.d \
./source/sys_main.d \
./source/sys_pcr.d \
./source/sys_phantom.d \
./source/sys_pmm.d \
./source/sys_selftest.d \
./source/sys_startup.d \
./source/sys_vim.d \
./source/system.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"D:\Team Phantom\Embedded\Tasks\BMS_Tester_Board_Firmware\BMS_Tester_Board_Thermistor_Firmware\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


