CC = cc
LDLIBS = -lm

SRCS = main.c huff.c help.c input.c frequency.c suma.c dekompresor.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: program

program: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c huff.h help.h input.h frequency.h suma.h dekompresor.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) 