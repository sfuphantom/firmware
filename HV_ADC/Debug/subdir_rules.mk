################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/Users/ryanh/Desktop/HV_VS_BMS" --include_path="C:/Users/ryanh/Desktop/HV_VS_BMS/include" --include_path="C:/Users/ryanh/Desktop/HV_VS_BMS/source" --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


