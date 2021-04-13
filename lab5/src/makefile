CC=gcc
target all: bin/mutex bin/no_mutex bin/parallel_fact bin/deadlock

bin/mutex: mutex.c
	$(CC) -o bin/mutex mutex.c -lpthread

bin/no_mutex: no_mutex.c
	$(CC) -o bin/no_mutex no_mutex.c -lpthread

bin/parallel_fact: parallel_fact.c
	$(CC) -o bin/parallel_fact parallel_fact.c -lpthread

bin/deadlock: deadlock.c
	$(CC) -o bin/deadlock deadlock.c -lpthread

clean:
	rm bin/mutex bin/no_mutex bin/parallel_fact bin/deadlock
