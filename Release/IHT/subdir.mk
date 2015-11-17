################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IHT/IHT.cpp \
../IHT/stdafx.cpp 

OBJS += \
./IHT/IHT.o \
./IHT/stdafx.o 

CPP_DEPS += \
./IHT/IHT.d \
./IHT/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
IHT/%.o: ../IHT/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


