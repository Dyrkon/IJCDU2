# 	Makefile pro první úkol IJC
#	Řešení IJC-DU1, příklad a), 24.3.2021
#	Autor: Matěj Mudra
#	Makefile pro překlad a spuštění druhého úkolu IJC


CFLAGS  	= -g -std=c99 -Wextra -Wall -pedantic -O2 -march=native -flto
CFLAGS_L	= -g -std=c99 -Wextra -Wall -pedantic -O2 -march=native -flto -fPIC
DEBUGFLAGS	= -Og -g -rdynamic -std=c11 -Wextra -Wall -pedantic
LIBGLAGS	= -shared -fPIC
OBJ			= htab_init.o htab_hash_function.o htab_move.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o
CC 			= gcc

all: tail wordcount-dynamic wordcount  wordcount-orig

# Tail

tail.o: tail.c tail.h
	$(CC) $(CFLAGS) -c tail.c

# Wordcount

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

wordcount.o: io.c wordcount.c
	$(CC) $(CFLAGS_L) -c wordcount.c io.o

# Lib files

htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS_L) -c htab_hash_function.c

htab_init.o: htab_init.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_init.c

htab_move.o: htab_move.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_move.c

htab_size.o: htab_size.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_size.c

htab_bucket_count.o: htab_bucket_count.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_bucket_count.c

htab_find.o: htab_find.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_find.c

htab_lookup_add.o: htab_lookup_add.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_lookup_add.c

htab_erase.o: htab_erase.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_erase.c

htab_for_each.o: htab_for_each.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_for_each.c

htab_clear.o: htab_clear.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_clear.c

htab_free.o: htab_free.c htab_priv.h
	$(CC) $(CFLAGS_L) -c htab_free.c

wordcount-orig: wordcount-orig.cpp
	g++ -std=c++11 -O2 wordcount-orig.cpp -o wordcount-orig

# Lib linking


libhtab.so: $(OBJ)
	LD_LIBRARY_PATH="."
	$(CC) -shared -fPIC $(OBJ) -o $@

libhtab.a: $(OBJ)
	LD_LIBRARY_PATH="."
	ar crsv libhtab.a $(OBJ)
	ranlib $@

# Runnable files

wordcount: libhtab.a io.o wordcount.o htab.h
	LD_LIBRARY_PATH="."
	$(CC) $(CFLAGS) wordcount.o io.o -L. -lhtab -Wl,-rpath="$(PWD)" -o wordcount

wordcount-dynamic: libhtab.so io.o wordcount.o htab.h
	$(CC) $(CFLAGS) wordcount.o io.o -L. -lhtab -Wl,-rpath="$(PWD)" -o wordcount-dynamic

tail: tail.o
	$(CC) $(CFLAGS) -o tail tail.o

clean:
	rm -f  *~  *.bak  *.o  tail wordcount wordcount-dynamic wordcount-orig libhtab.so libhtab.a

pack: clean
	zip xmudra04.zip *.c *.h wordcount-orig.cpp Makefile