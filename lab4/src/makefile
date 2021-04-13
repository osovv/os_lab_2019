CC=gcc
CFLAGS=-I.

all: bin/parallel_min_max bin/utils.o bin/find_min_max.o bin/make_zombie bin/shared/libsum.so bin/parallel_sum
 
bin/parallel_min_max : bin/utils.o bin/find_min_max.o src/from_lab3/utils.h src/from_lab3/find_min_max.h
	$(CC) -o bin/parallel_min_max bin/utils.o bin/find_min_max.o src/from_lab3/parallel_min_max.c $(CFLAGS)

bin/utils.o : src/from_lab3/utils.h
	$(CC) -o bin/utils.o -c src/from_lab3/utils.c $(CFLAGS)

bin/find_min_max.o : src/from_lab3/utils.h src/from_lab3/find_min_max.h
	$(CC) -o bin/find_min_max.o -c src/from_lab3/find_min_max.c $(CFLAGS)

bin/make_zombie: src/make_zombie.c
	$(CC) -o bin/make_zombie src/make_zombie.c $(CFLGAGS)

bin/parallel_sum: bin/utils.o bin/shared/libsum.so src/parallel_sum.c
	$(CC) -o bin/parallel_sum src/parallel_sum.c bin/utils.o -lpthread -Lbin/shared -lsum

bin/shared/libsum.so: bin/sum.o
	$(CC) -o bin/shared/libsum.so -shared bin/sum.o

bin/sum.o: src/sum.c src/sum.h
	$(CC) -o bin/sum.o -c -fPIC src/sum.c

clean :
	rm bin/utils.o bin/find_min_max.o bin/parallel_min_max bin/make_zombie bin/shared/libsum.so bin/parallel_sum bin/sum.o
