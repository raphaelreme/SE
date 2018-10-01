
CC = arm-none-eabi-gcc
EXE = test
OBJS = t.o
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS = -Wall -Wextra -Werror -g -O1
# Pour que LD soit verbeux
# LDFLAGS = -T ld_ram.lds -nostdlib -Wl,--print-map
LDFLAGS = -T ld_ram.lds -nostdlib



all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

#path:
#	export PATH=/comelec/softs/bin:$$PATH

JLinkGDBServer:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean:
	rm -f *.o *.out *.h $(EXE)


.PHONY: JLinkGDBServer clean
