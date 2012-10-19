################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lookup/CCohortLookup.cpp \
../src/lookup/CohortLookup.cpp \
../src/lookup/SoilLookup.cpp 

OBJS += \
./src/lookup/CCohortLookup.o \
./src/lookup/CohortLookup.o \
./src/lookup/SoilLookup.o 

CPP_DEPS += \
./src/lookup/CCohortLookup.d \
./src/lookup/CohortLookup.d \
./src/lookup/SoilLookup.d 


# Each subdirectory must supply rules for building sources it contributes
src/lookup/%.o: ../src/lookup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


