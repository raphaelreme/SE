CC = arm-none-eabi-gcc
OBJS = t.o

CFLAGS = -Wall -Wextra -Werror


compilation: $(OBJS)

optim: CFLAGS += -Os

optim: $(OBJS)

clean :
		rm -f *.o *.s

.PHONY: clean compilation
