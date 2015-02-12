# Makefile for remove expired files and dirs
CC=gcc 
CFLAGS=-Wall -O3 -I. -static
SOURCES=dirlist.c filelist.c writelog.c recursivepass.c scandir.c main.c
EXEC=removebkps
OBJECTS=$(SOURCES:.c=.o)
LIBPATH=-L/usr/lib/x86_64-linux-gnu
LIBS=-lc
all:$(EXEC) 

filelist:dirlist.c dirlist.h filelist.c filelist.h 
	$(CC) $(CFLAGS) filelist.c -c -I. -o filelist.o
scandir:scandir.c 
	$(CC) $(CFLAGS) scandir.c -I. -c -o scandir.o
recursivepass:recursivepass.c
	$(CC) $(CFLAGS) recursivepass.c -I. -c -o recursivepass.o
writelog:writelog.c writelist.h
	$(CC) $(CFLAGS) writelog.c -I. -c -o writelog.o
$(EXEC):$(SOURCES) 
	$(CC) $(CFLAGS) $(SOURCES) $(LIBPATH) $(LIBS) -o $(EXEC)
.PHONY:	clean
clean:
	-rm -rf $(EXEC) $(OBJECTS)
