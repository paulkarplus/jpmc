################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2806x_CodeStartBranch.obj: C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/source/F2806x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_common/include" --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="F2806x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_GlobalVariableDefs.obj: C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_common/include" --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="F2806x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

eBike\ MC-DevInit_F2806x.obj: ../eBike\ MC-DevInit_F2806x.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_common/include" --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="eBike MC-DevInit_F2806x.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

eBike\ MC-Main.obj: ../eBike\ MC-Main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v100/F2806x_common/include" --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="eBike MC-Main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


