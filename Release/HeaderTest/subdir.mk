################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HeaderTest/HeaderTest.cpp \
../HeaderTest/stdafx.cpp 

OBJS += \
./HeaderTest/HeaderTest.o \
./HeaderTest/stdafx.o 

CPP_DEPS += \
./HeaderTest/HeaderTest.d \
./HeaderTest/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
HeaderTest/%.o: ../HeaderTest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


