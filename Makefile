# 	Makefile pro první úkol IJC
#	Řešení IJC-DU1, příklad a), 24.3.2021
#	Autor: Matěj Mudra
#	Makefile pro překlad a spuštění druhého úkolu IJC


CFLAGS  	= -g -std=c11 -Wextra -Wall -pedantic -O2 -march=native -flto
DEBUGFLAGS	= -Og -g -rdynamic -std=c11 -Wextra -Wall -pedantic
LDLIBS  	= -lm # pokud potřebujeme matematickou knihovnu libm
LIBGLAGS	= -shared -fPIC
OBJ			= htab_hash_function.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o
CC 			= gcc

all: tail dynamic-lib static-lib wordcount wordcount-dynamic

# Tail

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c

# Wordcount

io.o: io.c io.h
	$(CC) $(DEBUGFLAGS) -c io.c

# TODO(remove debug flags)
wordcount.o: wordcount.c io.o
	$(CC) $(DEBUGFLAGS) -c wordcount.c io.o

# Lib files

htab_hash_function.o: htab_hash_function.c
	$(CC) $(DEBUGFLAGS) -fPIC -c htab_hash_function.c

htab_init.o: htab_init.c htab_priv.h

htab_move.o: htab_move.c htab_priv.h

htab_size.o: htab_size.c htab_priv.h

htab_bucket_count.o: htab_bucket_count.c htab_priv.h

htab_find.o: htab_find.c htab_priv.h

htab_lookup_add.o: htab_lookup_add.c htab_priv.h

htab_erase.o: htab_erase.c htab_priv.h

htab_for_each.o: htab_for_each.c htab_priv.h

htab_clear.o: htab_clear.c htab_priv.h

htab_free.o: htab_free.c htab_priv.h

dynamic-lib: $(OBJ)
	$(CC) $(LIBGLAGS) -o libhtab.so $(OBJ)

static-lib:
	ar -rs libhtab.a $(OBJ)

wordcount: wordcount.o io.o htab.h
	$(CC) $(DEBUGFLAGS) -o wordcount wordcount.o libhtab.a io.o

wordcount-dynamic: wordcount.o io.o htab.h
	$(CC) $(DEBUGFLAGS) -o wordcount-dynamic wordcount.o io.o /home/dyrkon/code/C/IJC/IJCDU2/libhtab.so

tail: tail.o
	$(CC) $(CFLAGS) -o tail tail.o $(LDLIBS)

clean:
	rm -f  *~  *.bak  *.o  tail libhtab.so libhtab.a wordcount wordcount-dynamic

archiv:
	tar czvf xmudra04.zip *.c *.h *.so *.a Makefile

run: tail wordcount
	./tail
	./wordcount
