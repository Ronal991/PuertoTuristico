CC=gcc
CFLAGS=-Wall -Wextra -std=c11
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=terminal

all: $(TARGET)

$(TARGET): $(OBJECTS)
$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@

clean:
rm -f $(OBJECTS) $(TARGET)
