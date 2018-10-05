################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/dabort.obj" \
"./source/esm.obj" \
"./source/notification.obj" \
"./source/pinmux.obj" \
"./source/sci.obj" \
"./source/sys_core.obj" \
"./source/sys_dma.obj" \
"./source/sys_intvecs.obj" \
"./source/sys_main.obj" \
"./source/sys_mpu.obj" \
"./source/sys_pcr.obj" \
"./source/sys_phantom.obj" \
"./source/sys_pmm.obj" \
"./source/sys_pmu.obj" \
"./source/sys_selftest.obj" \
"./source/sys_startup.obj" \
"./source/sys_vim.obj" \
"./source/system.obj" \
"../source/sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-lrtsv7R4_T_be_v3D16_eabi.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir_vars.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
GPIO.out \

EXE_OUTPUTS__QUOTED += \
"GPIO.out" \

BIN_OUTPUTS += \
GPIO.hex \

BIN_OUTPUTS__QUOTED += \
"GPIO.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "GPIO.out"

# Tool invocations
GPIO.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --preinclude="C:/Users/Neeraj Bansal/GPIO/include/adc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/can.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/crc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/dcc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/Device_header.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/Device_TMS570LS12.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/Device_types.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/ecap.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/eqep.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/esm.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/etpwm.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/fee_interface.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/gio.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/hal_stdtypes.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/het.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/htu.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/i2c.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/lin.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/MemMap.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/mibspi.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/pinmux.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_adc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_can.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_crc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_dcc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_dma.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_ecap.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_efc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_eqep.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_esm.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_etpwm.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_flash.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_gio.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_het.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_htu.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_i2c.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_lin.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_mibspi.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_pbist.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_pcr.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_pinmux.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_pmm.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_rti.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_sci.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_spi.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_stc.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_system.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_tcram.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/reg_vim.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/rti.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sci.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/spi.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/std_nhet.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_common.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_core.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_dma.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_mpu.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_pcr.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_pmm.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_pmu.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_selftest.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/sys_vim.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/system.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/ti_fee_cfg.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/ti_fee_types.h" --preinclude="C:/Users/Neeraj Bansal/GPIO/include/ti_fee.h" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi -z -m"GPIO.map" --heap_size=0x800 --stack_size=0x800 -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="GPIO_linkInfo.xml" --rom_model --be32 -o "GPIO.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

GPIO.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armhex"  -o "GPIO.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "source\dabort.obj" "source\esm.obj" "source\notification.obj" "source\pinmux.obj" "source\sci.obj" "source\sys_core.obj" "source\sys_dma.obj" "source\sys_intvecs.obj" "source\sys_main.obj" "source\sys_mpu.obj" "source\sys_pcr.obj" "source\sys_phantom.obj" "source\sys_pmm.obj" "source\sys_pmu.obj" "source\sys_selftest.obj" "source\sys_startup.obj" "source\sys_vim.obj" "source\system.obj" 
	-$(RM) "source\esm.d" "source\notification.d" "source\pinmux.d" "source\sci.d" "source\sys_dma.d" "source\sys_main.d" "source\sys_pcr.d" "source\sys_phantom.d" "source\sys_pmm.d" "source\sys_selftest.d" "source\sys_startup.d" "source\sys_vim.d" "source\system.d" 
	-$(RM) "source\dabort.d" "source\sys_core.d" "source\sys_intvecs.d" "source\sys_mpu.d" "source\sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

