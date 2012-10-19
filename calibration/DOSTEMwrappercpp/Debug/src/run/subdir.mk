################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/run/AtmOutData.cpp \
../src/run/Cohort.cpp \
../src/run/Controller.cpp \
../src/run/Grid.cpp \
../src/run/ModelData.cpp \
../src/run/RegnOutData.cpp \
../src/run/SiteIn.cpp \
../src/run/SnowSoilOutData.cpp \
../src/run/SoilClm.cpp \
../src/run/Timer.cpp \
../src/run/VegOutData.cpp 

OBJS += \
./src/run/AtmOutData.o \
./src/run/Cohort.o \
./src/run/Controller.o \
./src/run/Grid.o \
./src/run/ModelData.o \
./src/run/RegnOutData.o \
./src/run/SiteIn.o \
./src/run/SnowSoilOutData.o \
./src/run/SoilClm.o \
./src/run/Timer.o \
./src/run/VegOutData.o 

CPP_DEPS += \
./src/run/AtmOutData.d \
./src/run/Cohort.d \
./src/run/Controller.d \
./src/run/Grid.d \
./src/run/ModelData.d \
./src/run/RegnOutData.d \
./src/run/SiteIn.d \
./src/run/SnowSoilOutData.d \
./src/run/SoilClm.d \
./src/run/Timer.d \
./src/run/VegOutData.d 


# Each subdirectory must supply rules for building sources it contributes
src/run/%.o: ../src/run/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-3  -D_JNI_IMPLEMENTATION_ -I"C:\Java\include" -I"C:\Java\include\win32" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


