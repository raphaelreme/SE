CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = t.o
EXE = t

all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.c) $^ $(LDLIBS) $(OUTPUT_OPTION)

results: all
	./$(EXE)


clean:
	rm -f *.o $(EXE)
