OUTPUT_NAME = main

CXX_SRCS+= $(shell find . -name '*.cpp')

C_SRCS+= $(shell find  ./device/ -name '*.c')
C_SRCS+= $(shell find  ./STM32F7xx_StdPeriph_Driver/ -name '*.c')


INC = -I .
INC+= -I ./config/
INC+= -I ./device/
INC+= -I ./device/CMSIS/
INC+= -I ./STM32F7xx_StdPeriph_Driver/inc/
INC+= -I ./STM32F7xx_StdPeriph_Driver/
INC+= -include ./STM32F7xx_StdPeriph_Driver/stm32f7xx_conf.h
INC+= -include ./device/stm32f7xx.h

INC_CPP+= -I .
INC_CPP+= -I ./embedded_libs/
INC_CPP+= -I ./embedded_libs/common/
INC_CPP+= -I ./embedded_libs/control/
INC_CPP+= -I ./embedded_libs/drivers/

TARGET = -mcpu=cortex-m7 -mthumb -mfloat-abi=softfp -fsingle-precision-constant -DSTM32F746xx



GCCPREFIX	=arm-none-eabi-
LDSCRIPT 	= ./device/ldscript.ld



CC 			= $(GCCPREFIX)gcc
CXX 		= $(GCCPREFIX)g++
LD 			= $(GCCPREFIX)g++

OBJCOPY 	= $(GCCPREFIX)objcopy
OBJDUMP 	= $(GCCPREFIX)objdump
SIZE 		= $(GCCPREFIX)size




CCFLAGS 	= $(TARGET) $(INC) -c -O2 -Os -s -Wall -Wextra -std=c99 -nostdlib   -fdata-sections -ffunction-sections   -Wl,--gc-sections
CXXFLAGS	= $(TARGET) $(INC) $(INC_CPP) -c -O2 -s -funroll-loops -Wall -Wextra -pedantic -std=c++14 -fno-rtti  -fno-exceptions -fdata-sections -ffunction-sections  -Wl,--gc-sections
LDFLAGS 	= -T$(LDSCRIPT) $(TARGET) -nostdlib -Wl,--gc-sections
  
C_OBJS 		= $(C_SRCS:.c=.o)
CXX_OBJS 	= $(CXX_SRCS:.cpp=.o)

all: $(OUTPUT_NAME)
	$(OBJDUMP) --disassemble -D -z bin/$(OUTPUT_NAME).elf > bin/$(OUTPUT_NAME).asm
	$(OBJCOPY) -O ihex bin/$(OUTPUT_NAME).elf bin/$(OUTPUT_NAME).hex
	$(OBJCOPY) -O binary bin/$(OUTPUT_NAME).elf bin/$(OUTPUT_NAME).bin
	$(SIZE) bin/$(OUTPUT_NAME).elf

$(OUTPUT_NAME): $(C_OBJS) $(CXX_OBJS)
	$(LD) $(LDFLAGS) -o bin/$(OUTPUT_NAME).elf $(C_OBJS) $(CXX_OBJS)

%.o: %.c
	$(CC) $(CCFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

CLEAN_FILES = $(C_OBJS)
CLEAN_FILES+= $(CXX_OBJS)
CLEAN_FILES+= bin/main*

clean:
	rm -f $(C_OBJS)
	rm -f $(CXX_OBJS)
	rm -f bin/$(OUTPUT_NAME).elf
	rm -f bin/$(OUTPUT_NAME).asm
	rm -f bin/$(OUTPUT_NAME).hex
	rm -f bin/$(OUTPUT_NAME).bin
