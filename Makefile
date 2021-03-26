# 	Makefile pro první úkol IJC
#	Řešení IJC-DU1, příklad a), 24.3.2021
#	Autor: Matěj Mudra
#	Makefile pro překlad a spuštění druhého úkolu IJC


CFLAGS  = -g -std=c11 -Wextra -Wall -pedantic -O2
LDFLAGS = -g
LDLIBS  = -lm # pokud potřebujeme matematickou knihovnu libm
CC = gcc

all: tail wordcount

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c

# wordcount.o: wordcount.c

tail: tail.o
	$(CC) $(LDFLAGS) -o tail tail.o $(LDLIBS)

clean:
	rm -f  *~  *.bak  *.o  primes primes-i

archiv:
	tar czvf xmudra04.tar.gz *.c *.h *.so *.a Makefile

run: tail wordcount
	./tail
	./wordcount
