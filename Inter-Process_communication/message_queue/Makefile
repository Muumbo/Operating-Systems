all: server client

server: server.c
	gcc -Wall -Wextra -std=c11 -D_XOPEN_SOURCE=500 $^ -o $@ -lrt

client: client.c
	gcc -Wall -Wextra -std=c11 $^ -o $@ -lrt

clean: server client
	rm $^