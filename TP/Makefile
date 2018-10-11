PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as

TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_MACH = $(TARGET_ARCH)

CFLAGS = -Wall -Wextra -Werror -g -O0
ASFLAGS = -g

# Pour que LD soit verbeux
# LDFLAGS = -T ld_ram.lds -nostdlib -Wl,--print-map
LDFLAGS = -T ld_ram.lds -nostdlib

EXE = test
OBJS = t.o crt0.o init.o led.o clocks
SOURCE_C = t.c init.c led.c


all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)


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
