# this is a comment
CFLAGS=-Wall -g

#target: dependencies
    #rules must start with a tab

.PHONY: all clean

all: server client

server: simple-server.c
	${CC} ${CFLAGS} -o $@ simple-server.c
    
client: simple-client.c
	${CC} ${CFLAGS} -o $@ simple-client.c

clean: 
	@rm -f server client
