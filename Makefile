EXECUTABLE = disas
EXECDIR = /.
CC = gcc
CFLAGS = -Wall 
LIBS = -lpthread

CFILES = $(wildcard *.c) $(wildcard *.h)

disas: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(CFILES) $(LIBS)

