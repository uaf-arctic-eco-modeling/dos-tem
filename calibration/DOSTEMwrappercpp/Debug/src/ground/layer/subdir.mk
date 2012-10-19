################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ground/layer/Front.cpp \
../src/ground/layer/Layer.cpp \
../src/ground/layer/MineralLayer.cpp \
../src/ground/layer/MossLayer.cpp \
../src/ground/layer/OutputDepth.cpp \
../src/ground/layer/PeatLayer.cpp \
../src/ground/layer/RockLayer.cpp \
../src/ground/layer/SnowLayer.cpp \
../src/ground/layer/SoilLayer.cpp 

OBJS += \
./src/ground/layer/Front.o \
./src/ground/layer/Layer.o \
./src/ground/layer/MineralLayer.o \
./src/ground/layer/MossLayer.o \
./src/ground/layer/OutputDepth.o \
./src/ground/layer/PeatLayer.o \
./src/ground/layer/RockLayer.o \
./src/ground/layer/SnowLayer.o \
./src/ground/layer/SoilLayer.o 

CPP_DEPS += \
./src/ground/layer/Front.d \
./src/ground/layer/Layer.d \
./src/ground/layer/MineralLayer.d \
./src/ground/layer/MossLayer.d \
./src/ground/layer/OutputDepth.d \
./src/ground/layer/PeatLayer.d \
./src/ground/layer/RockLayer.d \
./src/ground/layer/SnowLayer.d \
./src/ground/layer/SoilLayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/ground/layer/%.o: ../src/ground/layer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


