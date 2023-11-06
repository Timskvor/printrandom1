CC=gcc
LD=gcc
CFLAGS=-Wall -rdynamic -fPIC
LDFLAGS=-ldl

all: printrandom

printrandom: main.o linear.o random.o
	$(LD) $(LDFLAGS) -o printrandom main.o linear.o random.o

main.o: main.c random_source.h
	$(CC) $(CFLAGS) -c main.c

linear.o: linear.c random_source.h
	$(CC) $(CFLAGS) -c linear.c

random.o: random.c random_source.h
	$(CC) $(CFLAGS) -c random.c

clean:
	rm -f *.o printrandom