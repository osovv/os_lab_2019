CC=gcc
CFLAGS=-I.

all: bin/sequential_min_max bin/parallel_min_max bin/utils.o bin/find_min_max.o bin/run_exec
 
bin/sequential_min_max : bin/utils.o bin/find_min_max.o src/utils.h src/find_min_max.h
	$(CC) -o bin/sequential_min_max bin/find_min_max.o bin/utils.o src/sequential_min_max.c $(CFLAGS)

bin/parallel_min_max : bin/utils.o bin/find_min_max.o src/utils.h src/find_min_max.h
	$(CC) -o bin/parallel_min_max bin/utils.o bin/find_min_max.o src/parallel_min_max.c $(CFLAGS)

bin/utils.o : src/utils.h
	$(CC) -o bin/utils.o -c src/utils.c $(CFLAGS)

bin/find_min_max.o : src/utils.h src/find_min_max.h
	$(CC) -o bin/find_min_max.o -c src/find_min_max.c $(CFLAGS)

bin/run_exec: src/run_exec.c
	$(CC) -o bin/run_exec src/run_exec.c $(CFLGAGS)

clean :
	rm bin/utils.o bin/find_min_max.o bin/sequential_min_max bin/parallel_min_max bin/run_exec
