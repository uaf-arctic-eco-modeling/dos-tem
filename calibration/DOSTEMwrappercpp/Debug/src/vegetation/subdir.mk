################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vegetation/Vegetation_Bgc.cpp \
../src/vegetation/Vegetation_Env.cpp 

OBJS += \
./src/vegetation/Vegetation_Bgc.o \
./src/vegetation/Vegetation_Env.o 

CPP_DEPS += \
./src/vegetation/Vegetation_Bgc.d \
./src/vegetation/Vegetation_Env.d 


# Each subdirectory must supply rules for building sources it contributes
src/vegetation/%.o: ../src/vegetation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


