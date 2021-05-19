CC=gcc

all: bin/tcpclient bin/tcpserver bin/udpclient bin/udpserver

bin/tcpclient: tcpclient.c
	$(CC) -o bin/tcpclient tcpclient.c

bin/tcpserver: tcpserver.c
	$(CC) -o bin/tcpserver tcpserver.c

bin/udpclient: udpclient.c
	$(CC) -o bin/udpclient udpclient.c

bin/udpserver: udpserver.c
	$(CC) -o bin/udpserver udpserver.c

clean:
	rm bin/tcpclient bin/tcpserver bin/udpclient bin/udpserver