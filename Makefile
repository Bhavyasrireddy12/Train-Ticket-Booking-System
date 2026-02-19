CC = gcc
CFLAGS = -Wall

all:
	$(CC) src/main.c -o bin/train_booking

run:
	./bin/train_booking

clean:
	rm -f bin/train_booking
