CC = cc
LDLIBS = -lm

SRCS = main.c huff.c help.c input.c 
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: program

program: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c huff.h help.h input.h compres12.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) 