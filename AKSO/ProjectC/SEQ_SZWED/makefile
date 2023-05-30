# Karol Szwed
# 25.04.2022 r.
# Makefile do projektu w C z AKSO

# Wykorzystywany kompilator
CC       = gcc

# Flagi kompilacji
CFLAGS   = -Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2

# Flagi linkowania
LDFLAGS  = -shared -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=reallocarray -Wl,--wrap=free -Wl,--wrap=strdup -Wl,--wrap=strndup

.PHONY: all
all: libseq.so

check_parameters.o: check_parameters.c check_parameters.h
memory_tests.o: memory_tests.c memory_tests.h
my_list.o: my_list.c my_list.h trie.h
seq.o: seq.c seq.h trie.h check_parameters.h
seq_example.o: seq_example.c seq.h memory_tests.h
trie.o: trie.c my_list.h trie.h

# Główny cel - kompilacja oraz linkowanie biblioteki dynamicznej libseq.so
libseq.so: seq.o memory_tests.o check_parameters.o trie.o my_list.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o libseq.so $^

# Cel zawierający podstawowe testy funkcjonalności programu
seq_example: libseq.so seq_example.o
	$(CC) -o seq_example -g seq_example.o -L. -lseq

# Czyści efekty kompilacji i linkowania
clean:
	rm -f *.o libseq.so seq_example
