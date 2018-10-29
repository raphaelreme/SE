vpath stubs.c libs

CC = arm-none-eabi-gcc
EXE = main
OBJS = main.o t1.o t2.o stubs.o

TARGET_ARCH = -mthumb
CFLAGS = -Wall -Werror -g -Og
LDFLAGS = -L/opt/mylibs
LDLIBS = -lm
stubs.o: CFLAGS = -g -O2

all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)


-include $(subst .o,.d,$(OBJS))

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M -MF $@ -MP $<



clean :
	rm -f *.o *.d $(EXE)

.PHONY: clean
