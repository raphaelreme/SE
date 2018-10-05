PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = t.o
RES = results

Os.o: CFLAGS += -Os
O0.o: CFLAGS += -O0
O1.o: CFLAGS += -O1
O2.o: CFLAGS += -O2

all: Os.o O0.o O1.o O2.o


%.o: t.c
	$(COMPILE.c) $< -o $@
	$(PREFIX)objdump -h $@ >>$(RES)

clean:
	rm -f *.o $(RES)

.PHONY: clean all
