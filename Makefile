CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: rod_cut_lru rod_cut_random

rod_cut_lru: main_lru.o rod_cut.o cache_lru.o
	$(CC) $(CFLAGS) -o $@ $^

rod_cut_random: main_random.o rod_cut.o cache_random.o
	$(CC) $(CFLAGS) -o $@ $^

main_lru.o: main.c rod_cut.h cache_lru.h
	$(CC) $(CFLAGS) -DUSE_LRU -c main.c -o $@

main_random.o: main.c rod_cut.h cache_random.h
	$(CC) $(CFLAGS) -DUSE_RANDOM -c main.c -o $@

rod_cut.o: rod_cut.c rod_cut.h
	$(CC) $(CFLAGS) -c rod_cut.c

cache_lru.o: cache_lru.c cache_lru.h
	$(CC) $(CFLAGS) -c cache_lru.c

cache_random.o: cache_random.c cache_random.h
	$(CC) $(CFLAGS) -c cache_random.c

clean:
	rm -f *.o rod_cut_lru rod_cut_random