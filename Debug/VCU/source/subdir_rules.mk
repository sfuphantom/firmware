################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
VCU/source/dabort.obj: ../VCU/source/dabort.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/dabort.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/esm.obj: ../VCU/source/esm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/esm.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/notification.obj: ../VCU/source/notification.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/notification.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/pinmux.obj: ../VCU/source/pinmux.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/pinmux.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sci.obj: ../VCU/source/sci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sci.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_core.obj: ../VCU/source/sys_core.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_core.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_dma.obj: ../VCU/source/sys_dma.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_dma.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_intvecs.obj: ../VCU/source/sys_intvecs.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_intvecs.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_main.obj: ../VCU/source/sys_main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_main.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_mpu.obj: ../VCU/source/sys_mpu.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_mpu.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_pcr.obj: ../VCU/source/sys_pcr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_pcr.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_phantom.obj: ../VCU/source/sys_phantom.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_phantom.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_pmm.obj: ../VCU/source/sys_pmm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_pmm.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_pmu.obj: ../VCU/source/sys_pmu.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_pmu.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_selftest.obj: ../VCU/source/sys_selftest.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_selftest.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_startup.obj: ../VCU/source/sys_startup.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_startup.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/sys_vim.obj: ../VCU/source/sys_vim.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/sys_vim.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

VCU/source/system.obj: ../VCU/source/system.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="D:/Team_Phantom/Firmware/firmware" --include_path="D:/Team_Phantom/Firmware/firmware/VCU/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="VCU/source/system.d_raw" --obj_directory="VCU/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


