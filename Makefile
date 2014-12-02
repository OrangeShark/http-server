CC=gcc
CFLAGS= -Wall -g
OBJS= webserver.o server.o http_message.o strbuffer.o

TARGET= webserver

all: $(TARGET)

$(TARGET): $(OBJS)

server.c: strbuffer.h

.PHONY: clean

clean:
	rm $(TARGET) $(OBJS)
