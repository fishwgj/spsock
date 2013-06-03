CC=gcc
CFLAGS=-g -Wall
LIBS=

server: server.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

client: client.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
