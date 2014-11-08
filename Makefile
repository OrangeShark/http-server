CC=gcc
CFLAGS= -Wall -g
OBJS= webserver.o server.o http_message.o

TARGET= webserver

all: $(TARGET)

$(TARGET): $(OBJS)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJS)
