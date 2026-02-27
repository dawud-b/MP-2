################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/verbose/verbose.c 

OBJS += \
./src/verbose/verbose.o 

C_DEPS += \
./src/verbose/verbose.d 


# Each subdirectory must supply rules for building sources it contributes
src/verbose/%.o: ../src/verbose/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -I../../ZedBoard_FMC_Pcam_Adapter_DEMO_bsp/ps7_cortexa9_0/include -I"D:\repos\Incercare2019\repo2018\ZedBoard-FMC-Pcam-Adapter-DEMO\proj\ZedBoard-FMC-Pcam-Adapter-DEMO.sdk\ZedBoard_FMC_Pcam_Adapter_DEMO\src" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


