CC=gcc

all: bin/shared/libmult.so bin/mult.o bin/server

bin/shared/libmult.so: bin/mult.o
	$(CC) -o bin/shared/libmult.so -shared bin/mult.o

bin/mult.o: mult.c mult.h
	$(CC) -o bin/mult.o -c -fPIC mult.c

bin/server: server.c  bin/shared/libmult.so
	$(CC) -o bin/server server.c -lpthread -lmult -Lbin/shared

bin/client: client.c
	$(CC) -o bin/client client.c -lpthread -lmult -Lbin/shared

clean:
	rm bin/shared/libmult.so bin/mult.o bin/server
