CC=gcc
CFLAGS=-I.
HEADERS_SRC = rooms.h items.h rooms.c items.c adventure.c
OBJ = rooms.o items.o adventure.o
PROG = a_game

%.o: %.c $(HEADERS_SRC)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)