CC=gcc
CFLAGS=-ansi -Wall -pedantic-errors -std=c99
LIBS=-lm
BINS=fitymi
OBJS=fitymi.o dictionary.o

all: $(BINS)

fitymi: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o $(BINS)
