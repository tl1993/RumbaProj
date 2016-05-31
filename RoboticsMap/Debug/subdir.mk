################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Map.cpp \
../Matrix.cpp \
../Utils.cpp \
../lodepng.cpp \
../main.cpp \
../pngUtil.cpp 

OBJS += \
./Map.o \
./Matrix.o \
./Utils.o \
./lodepng.o \
./main.o \
./pngUtil.o 

CPP_DEPS += \
./Map.d \
./Matrix.d \
./Utils.d \
./lodepng.d \
./main.d \
./pngUtil.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


