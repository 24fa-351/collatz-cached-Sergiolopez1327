CC = gcc
CFLAGS = -Wall -O2
TARGET = collatz

all: $(TARGET)

$(TARGET): main.o collatz.o cache.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o collatz.o cache.o

main.o: main.c collatz.h cache.h
	$(CC) $(CFLAGS) -c main.c

collatz.o: collatz.c collatz.h
	$(CC) $(CFLAGS) -c collatz.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

clean:
	rm -f $(TARGET) *.o
