################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Serwer.c 

OBJS += \
./src/Serwer.o 

C_DEPS += \
./src/Serwer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/kamil/Documents/workspace/SharedLibrary/Debug" -I"/home/kamil/Documents/workspace/SharedLibrary" -include"/home/kamil/Documents/workspace/SharedLibrary/biblioteka.h" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


