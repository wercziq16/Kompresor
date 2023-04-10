CC = cc
LDLIBS = -lm

SRCS = main.c huffman16.c help.c input.c frequency.c suma.c kompresor.c dekompresor.c padding.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: program

program: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c huffman16.h help.h input.h frequency.h suma.h kompresor.h dekompresor.h padding.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) 