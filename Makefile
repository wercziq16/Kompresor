CC = gcc
LDLIBS = -lm

SRCS = main.c huff.c input.c help.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: huff

huff: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c huff.h input.h help.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) huff

