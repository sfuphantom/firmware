################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../source/sys_link.cmd 

ASM_SRCS += \
../source/dabort.asm \
../source/os_portasm.asm \
../source/sys_core.asm \
../source/sys_intvecs.asm \
../source/sys_mpu.asm \
../source/sys_pmu.asm 

C_SRCS += \
../source/Phantom_sci.c \
../source/adc.c \
../source/errata_SSWF021_45.c \
../source/esm.c \
../source/gio.c \
../source/notification.c \
../source/os_croutine.c \
../source/os_event_groups.c \
../source/os_heap.c \
../source/os_list.c \
../source/os_mpu_wrappers.c \
../source/os_port.c \
../source/os_queue.c \
../source/os_tasks.c \
../source/os_timer.c \
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

C_DEPS += \
./source/Phantom_sci.d \
./source/adc.d \
./source/errata_SSWF021_45.d \
./source/esm.d \
./source/gio.d \
./source/notification.d \
./source/os_croutine.d \
./source/os_event_groups.d \
./source/os_heap.d \
./source/os_list.d \
./source/os_mpu_wrappers.d \
./source/os_port.d \
./source/os_queue.d \
./source/os_tasks.d \
./source/os_timer.d \
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

OBJS += \
./source/Phantom_sci.obj \
./source/adc.obj \
./source/dabort.obj \
./source/errata_SSWF021_45.obj \
./source/esm.obj \
./source/gio.obj \
./source/notification.obj \
./source/os_croutine.obj \
./source/os_event_groups.obj \
./source/os_heap.obj \
./source/os_list.obj \
./source/os_mpu_wrappers.obj \
./source/os_port.obj \
./source/os_portasm.obj \
./source/os_queue.obj \
./source/os_tasks.obj \
./source/os_timer.obj \
./source/pinmux.obj \
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
./source/system.obj 

ASM_DEPS += \
./source/dabort.d \
./source/os_portasm.d \
./source/sys_core.d \
./source/sys_intvecs.d \
./source/sys_mpu.d \
./source/sys_pmu.d 

OBJS__QUOTED += \
"source\Phantom_sci.obj" \
"source\adc.obj" \
"source\dabort.obj" \
"source\errata_SSWF021_45.obj" \
"source\esm.obj" \
"source\gio.obj" \
"source\notification.obj" \
"source\os_croutine.obj" \
"source\os_event_groups.obj" \
"source\os_heap.obj" \
"source\os_list.obj" \
"source\os_mpu_wrappers.obj" \
"source\os_port.obj" \
"source\os_portasm.obj" \
"source\os_queue.obj" \
"source\os_tasks.obj" \
"source\os_timer.obj" \
"source\pinmux.obj" \
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
"source\system.obj" 

C_DEPS__QUOTED += \
"source\Phantom_sci.d" \
"source\adc.d" \
"source\errata_SSWF021_45.d" \
"source\esm.d" \
"source\gio.d" \
"source\notification.d" \
"source\os_croutine.d" \
"source\os_event_groups.d" \
"source\os_heap.d" \
"source\os_list.d" \
"source\os_mpu_wrappers.d" \
"source\os_port.d" \
"source\os_queue.d" \
"source\os_tasks.d" \
"source\os_timer.d" \
"source\pinmux.d" \
"source\sci.d" \
"source\sys_dma.d" \
"source\sys_main.d" \
"source\sys_pcr.d" \
"source\sys_phantom.d" \
"source\sys_pmm.d" \
"source\sys_selftest.d" \
"source\sys_startup.d" \
"source\sys_vim.d" \
"source\system.d" 

ASM_DEPS__QUOTED += \
"source\dabort.d" \
"source\os_portasm.d" \
"source\sys_core.d" \
"source\sys_intvecs.d" \
"source\sys_mpu.d" \
"source\sys_pmu.d" 

C_SRCS__QUOTED += \
"../source/Phantom_sci.c" \
"../source/adc.c" \
"../source/errata_SSWF021_45.c" \
"../source/esm.c" \
"../source/gio.c" \
"../source/notification.c" \
"../source/os_croutine.c" \
"../source/os_event_groups.c" \
"../source/os_heap.c" \
"../source/os_list.c" \
"../source/os_mpu_wrappers.c" \
"../source/os_port.c" \
"../source/os_queue.c" \
"../source/os_tasks.c" \
"../source/os_timer.c" \
"../source/pinmux.c" \
"../source/sci.c" \
"../source/sys_dma.c" \
"../source/sys_main.c" \
"../source/sys_pcr.c" \
"../source/sys_phantom.c" \
"../source/sys_pmm.c" \
"../source/sys_selftest.c" \
"../source/sys_startup.c" \
"../source/sys_vim.c" \
"../source/system.c" 

ASM_SRCS__QUOTED += \
"../source/dabort.asm" \
"../source/os_portasm.asm" \
"../source/sys_core.asm" \
"../source/sys_intvecs.asm" \
"../source/sys_mpu.asm" \
"../source/sys_pmu.asm" 


