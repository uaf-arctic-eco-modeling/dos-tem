################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/disturb/WildFire.cpp 

OBJS += \
./src/disturb/WildFire.o 

CPP_DEPS += \
./src/disturb/WildFire.d 


# Each subdirectory must supply rules for building sources it contributes
src/disturb/%.o: ../src/disturb/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


