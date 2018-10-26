PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
OBJCOPY = $(PREFIX)objcopy

TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_MACH = $(TARGET_ARCH)

CPPFLAGS = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include -DSTM32L475xx
CFLAGS = -Wall -Wextra -Werror -g -O1
ASFLAGS = -g
OBJCOPYFLAGS = -I binary -O elf32-littlearm -B arm

# Pour que LD soit verbeux
# LDFLAGS = -T ld_ram.lds -nostdlib -Wl,--print-map
LDFLAGS = -T ld_ram.lds -nostdlib

EXE = main
SOURCE_C = main.c init.c led.c uart.c matrix.c irq.c buttons.c clocks.c
OBJS = $(subst .c,.o,$(SOURCE_C)) crt0.o image.o


####################################################################
####################################################################
#########################  Main rules  #############################
all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

image.o: image.raw
	$(OBJCOPY) $(OBJCOPYFLAGS) $^ $@




####################################################################
####################################################################
##################  Generate prerequisites  ########################

-include $(subst .c,.d,$(SOURCE_C))

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M -MF $@ -MP $<


####################################################################
####################################################################
#####################  Launch gdb server  ##########################

JLinkGDBServer:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly




clean:
	rm -f *.o *.out *.d $(EXE)

.PHONY: JLinkGDBServer clean
