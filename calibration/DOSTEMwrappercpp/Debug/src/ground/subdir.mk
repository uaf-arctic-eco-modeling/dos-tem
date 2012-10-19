################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ground/DoubleLinkedList.cpp \
../src/ground/Ground.cpp \
../src/ground/Mineral.cpp \
../src/ground/Moss.cpp \
../src/ground/Peat.cpp \
../src/ground/Richard.cpp \
../src/ground/Rock.cpp \
../src/ground/Snow_Env.cpp \
../src/ground/Soil_Bgc.cpp \
../src/ground/Soil_Env.cpp \
../src/ground/Stefan.cpp 

OBJS += \
./src/ground/DoubleLinkedList.o \
./src/ground/Ground.o \
./src/ground/Mineral.o \
./src/ground/Moss.o \
./src/ground/Peat.o \
./src/ground/Richard.o \
./src/ground/Rock.o \
./src/ground/Snow_Env.o \
./src/ground/Soil_Bgc.o \
./src/ground/Soil_Env.o \
./src/ground/Stefan.o 

CPP_DEPS += \
./src/ground/DoubleLinkedList.d \
./src/ground/Ground.d \
./src/ground/Mineral.d \
./src/ground/Moss.d \
./src/ground/Peat.d \
./src/ground/Richard.d \
./src/ground/Rock.d \
./src/ground/Snow_Env.d \
./src/ground/Soil_Bgc.d \
./src/ground/Soil_Env.d \
./src/ground/Stefan.d 


# Each subdirectory must supply rules for building sources it contributes
src/ground/%.o: ../src/ground/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


