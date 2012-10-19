################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/BgcData.cpp \
../src/data/CohortData.cpp \
../src/data/EnvData.cpp \
../src/data/FirData.cpp \
../src/data/GridData.cpp \
../src/data/RegionData.cpp \
../src/data/RestartData.cpp 

OBJS += \
./src/data/BgcData.o \
./src/data/CohortData.o \
./src/data/EnvData.o \
./src/data/FirData.o \
./src/data/GridData.o \
./src/data/RegionData.o \
./src/data/RestartData.o 

CPP_DEPS += \
./src/data/BgcData.d \
./src/data/CohortData.d \
./src/data/EnvData.d \
./src/data/FirData.d \
./src/data/GridData.d \
./src/data/RegionData.d \
./src/data/RestartData.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/%.o: ../src/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


