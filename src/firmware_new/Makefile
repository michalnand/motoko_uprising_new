LibsCommonPATH 	= ./LibsCommon
LibsDevicePATH 	= ./LibsDevice
LibsDriversPATH = ./LibsDrivers

AppPATH 		= ./usr

GCCPREFIX	=arm-none-eabi-
OUTPUT	 	=bin/build

TARGET 		= -mcpu=cortex-m7 -mthumb -mfloat-abi=softfp -fsingle-precision-constant -DSTM32F746xx

LDSCRIPT 	= $(LibsDevicePATH)/ldscript.ld

INC+= -include $(LibsDevicePATH)/stm32f7xx_conf.h
INC+= -include $(LibsDevicePATH)/device/stm32f7xx.h
INC+= -I $(LibsCommonPATH)/
INC+= -I $(LibsDevicePATH)/
INC+= -I $(LibsDevicePATH)/device/ 
INC+= -I $(LibsDevicePATH)/CMSIS/ 
INC+= -I $(LibsDevicePATH)/STM32F7xx_StdPeriph_Driver/inc
INC+= -I $(LibsDriversPATH)/
INC+= -I $(AppPATH)

C_SRCS = $(shell find  $(LibsCommonPATH) -name 	'*.c')
C_SRCS+= $(shell find  $(LibsDevicePATH) -name 	'*.c')
C_SRCS+= $(shell find  $(LibsDriversPATH) -name '*.c')
C_SRCS+= $(shell find  $(AppPATH) -name '*.c')


CXX_SRCS+= $(shell find $(LibsCommonPATH) -name '*.cpp')
CXX_SRCS+= $(shell find $(LibsDevicePATH) -name '*.cpp')
CXX_SRCS+= $(shell find $(LibsDriversPATH) -name '*.cpp')
CXX_SRCS+= $(shell find $(AppPATH) -name '*.cpp')



CC 		= $(GCCPREFIX)gcc
CXX 	= $(GCCPREFIX)g++
LD 		= $(GCCPREFIX)g++
OBJCOPY = $(GCCPREFIX)objcopy
OBJDUMP = $(GCCPREFIX)objdump
SIZE 	= $(GCCPREFIX)size


LDFLAGS = $(TARGET) -Wl,--gc-sections

CCFLAGS = $(TARGET) $(INC) -c -O2 -Os -s -Wall -Wextra -std=c99 -nostdlib   -fdata-sections -ffunction-sections   -Wl,--gc-sections
CXXFLAGS= $(TARGET) $(INC) -c -O2 -s -funroll-loops -Wall -Wextra -pedantic -std=c++14 -fno-rtti  -fno-exceptions -fdata-sections -ffunction-sections  -Wl,--gc-sections
LDFLAGS = -T$(LDSCRIPT) $(TARGET) -nostdlib -Wl,--gc-sections 


C_OBJS 		= $(C_SRCS:.c=.o)
CXX_OBJS 	= $(CXX_SRCS:.cpp=.o)


all: $(OUTPUT)
	$(OBJDUMP) --disassemble $<.elf > $(OUTPUT).asm
	$(OBJCOPY) -O ihex $<.elf $(OUTPUT).hex
	$(OBJCOPY) -O binary $<.elf $(OUTPUT).bin
	$(SIZE) $(OUTPUT).elf

$(OUTPUT): $(C_OBJS) $(CXX_OBJS) 
	$(LD) -o $@.elf $(C_OBJS) $(CXX_OBJS) $(LDFLAGS)


%.o: %.c
	$(CC) $(CCFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@




CLEAN_FILES = $(C_OBJS)
CLEAN_FILES+= $(CXX_OBJS)
CLEAN_FILES+= $(OUTPUT)*

clean:
	rm $(CLEAN_FILES) -f
