################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2806x_CodeStartBranch.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_CpuTimers.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_CpuTimers.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_CpuTimers.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_DefaultIsr.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_DefaultIsr.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_DefaultIsr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_GlobalVariableDefs.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_Gpio.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_Gpio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_Gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_PieCtrl.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_PieCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_PieCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_PieVect.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_PieVect.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_PieVect.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_Sci.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_Sci.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_Sci.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_SysCtrl.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_SysCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_SysCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_usDelay.obj: C:/ti/controlSUITE/device_support/f2806x/v130/F2806x_common/source/F2806x_usDelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2806x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cmdline.obj: C:/controlSUITE/device_support/f2806x/v130/MWare/utils/cmdline.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="cmdline.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

console.obj: ../console.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="console.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interrupt.obj: C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/interrupt.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="interrupt.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

jpmc.obj: ../jpmc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="jpmc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sysctl.obj: C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/sysctl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="sysctl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: C:/controlSUITE/device_support/f2806x/v130/MWare/driverlib/uart.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="uart.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uartstdio.obj: C:/controlSUITE/device_support/f2806x/v130/MWare/utils/uartstdio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_headers/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../F2806x_common/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/IQmath/v15c/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../../../../libs/math/FPUfastRTS/v100/include" --include_path="C:/TI/controlSUITE/device_support/f2806x/v130/F2806x_examples/cpu_timer/../../MWare" --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="uartstdio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


