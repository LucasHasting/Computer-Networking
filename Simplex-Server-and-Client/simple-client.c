/* ID BLOCK */

//Need to know: address to listen, port to listen
//port is a demultiplexor that specefies what apps I want to use
//AINA - assign port numbers 
//  1024 and down are well known
//socket, bind, listen, accept
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int SERVER_PORT   = 11002;
const int MAX_LINE      = 256;

int
main(int argc, char **argv)
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    struct hostent *hp;
    char *host;
    size_t len;
    int s;

    /* Process Command Line Arguments */
    if (argc == 2)
	host = argv[1];
        // all good, grab the argument 
    else 
        err(1, "usage: client hostname");
    
    /* ask resolver for IP address of hostname */
    hp = gethostbyname(host);

    if (!hp){
        errx(1, "unknown host %s", host);
    }

    /* build address data structure */
    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    memcpy((char*)&sin.sin_addr.s_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT); /* network byte order */

    /* begin active open */
    if((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err(1, "unable to open socket");
    
    if((connect(s, (struct sockaddr*)&sin, sizeof sin))==-1){
        close(s);
        err(1, "connect failed");
    }

    /* main loop: get text from stdin and send */
    memset(buf, 0, sizeof buf);
	
    while (fgets(buf, sizeof buf, stdin)) {
        len = strnlen(buf, sizeof buf) + 1;
        send(s, buf, len, 0);
        memset(buf, 0, sizeof buf);
    }
    
    /* NOT REACHED */
    close(s);

    return 0;
}
//simplex is one way, half-duplex is one way and announce, full-duplex is two way
