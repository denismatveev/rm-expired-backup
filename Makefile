# Makefile for remove expired files and dirs
CC=gcc 
CFLAGS=-Wno-unused-result -O3 
SOURCES=filelist.c recursivepass.c scandir.c main.c
EXEC=rm_expired 
OBJECTS=$(SOURCES:.c=.o)
all:$(EXEC) 
filelist:filelist.c 
	$(CC) $(CFLAGS) filelist.c -c -I. -o filelist.o
scandir:scandir.c
	$(CC) $(CFLAGS) scandir.c -c -o scandir.o
recursivepass:recursivepass.c
	$(CC) $(CFLAGS) recursivepass.c -c -o recursivepass.o

.PHONY:	clean
clean:
	-rm -rf $(EXEC) $(OBJECTS)
