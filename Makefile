# 	Makefile pro první úkol IJC
#	Řešení IJC-DU1, příklad a), 24.3.2021
#	Autor: Matěj Mudra
#	Makefile pro překlad a spuštění druhého úkolu IJC


CFLAGS  	= -g -std=c11 -Wextra -Wall -pedantic -O2
LDFLAGS 	= -g
LDLIBS  	= -lm # pokud potřebujeme matematickou knihovnu libm
LIBGLAGS	= -shared -fPIC
OBJ			= htab_hash_function.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o
CC 			= gcc

all: tail wordcount dynamic-lib

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c

wordcount.o: wordcount.c

# Lib files

htab_hash_function.o: htab_hash_function.c

htab_init.o: htab_init.c

htab_move.o: htab_move.c

htab_size.o: htab_size.c

htab_bucket_count.o: htab_bucket_count.c

htab_find.o: htab_find.c

htab_lookup_add.o: htab_lookup_add.c

htab_erase.o: htab_erase.c

htab_for_each.o: htab_for_each.c

htab_clear.o: htab_clear.c

htab_free.o: htab_free.c

dynamic-lib: $(OBJ)
	$(CC) $(LIBGLAGS) -o libhtab.so $(OBJ)
wordcount: wordcount.o htab.h htab_priv.h


tail: tail.o
	$(CC) $(LDFLAGS) -o tail tail.o $(LDLIBS)

clean:
	rm -f  *~  *.bak  *.o  tail

archiv:
	tar czvf xmudra04.tar.gz *.c *.h *.so *.a Makefile

run: tail wordcount
	./tail
	./wordcount
