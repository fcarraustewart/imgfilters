OBJ=obligatorio.o imagen.o
CFLAGS=-Wall
CC=gcc
LIBS=-lm
HDR=imagen.h pgm.h

obligatorio: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)
.c.o: $(HDR)
	$(CC) -c -ggdb $(CFLAGS) $<
