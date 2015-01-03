CFLAGS=-Wall
LDFLAGS=-lncurses
all: shellda
shellda: map.c actor.c shellda.c
clean:
	rm -f shellda

