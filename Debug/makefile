################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./VCU/source/dabort.obj" \
"./VCU/source/esm.obj" \
"./VCU/source/notification.obj" \
"./VCU/source/pinmux.obj" \
"./VCU/source/sci.obj" \
"./VCU/source/sys_core.obj" \
"./VCU/source/sys_dma.obj" \
"./VCU/source/sys_intvecs.obj" \
"./VCU/source/sys_main.obj" \
"./VCU/source/sys_mpu.obj" \
"./VCU/source/sys_pcr.obj" \
"./VCU/source/sys_phantom.obj" \
"./VCU/source/sys_pmm.obj" \
"./VCU/source/sys_pmu.obj" \
"./VCU/source/sys_selftest.obj" \
"./VCU/source/sys_startup.obj" \
"./VCU/source/sys_vim.obj" \
"./VCU/source/system.obj" \
"../VCU/source/sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-lrtsv7R4_T_be_v3D16_eabi.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include VCU/source/subdir_vars.mk
-include VCU/source/subdir_rules.mk
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
VCU.out \

EXE_OUTPUTS__QUOTED += \
"VCU.out" \

BIN_OUTPUTS += \
VCU.hex \

BIN_OUTPUTS__QUOTED += \
"VCU.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "VCU.out"

# Tool invocations
VCU.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi -z -m"VCU.map" --heap_size=0x800 --stack_size=0x800 -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="VCU_linkInfo.xml" --rom_model --be32 -o "VCU.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

VCU.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armhex"  -o "VCU.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "VCU\source\dabort.obj" "VCU\source\esm.obj" "VCU\source\notification.obj" "VCU\source\pinmux.obj" "VCU\source\sci.obj" "VCU\source\sys_core.obj" "VCU\source\sys_dma.obj" "VCU\source\sys_intvecs.obj" "VCU\source\sys_main.obj" "VCU\source\sys_mpu.obj" "VCU\source\sys_pcr.obj" "VCU\source\sys_phantom.obj" "VCU\source\sys_pmm.obj" "VCU\source\sys_pmu.obj" "VCU\source\sys_selftest.obj" "VCU\source\sys_startup.obj" "VCU\source\sys_vim.obj" "VCU\source\system.obj" 
	-$(RM) "VCU\source\esm.d" "VCU\source\notification.d" "VCU\source\pinmux.d" "VCU\source\sci.d" "VCU\source\sys_dma.d" "VCU\source\sys_main.d" "VCU\source\sys_pcr.d" "VCU\source\sys_phantom.d" "VCU\source\sys_pmm.d" "VCU\source\sys_selftest.d" "VCU\source\sys_startup.d" "VCU\source\sys_vim.d" "VCU\source\system.d" 
	-$(RM) "VCU\source\dabort.d" "VCU\source\sys_core.d" "VCU\source\sys_intvecs.d" "VCU\source\sys_mpu.d" "VCU\source\sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

