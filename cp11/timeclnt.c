/**
 * timeclnt.c - a client for timeserv.c
 *              usage: timeclnt hostname portnumber
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define oops(msg) {perror(msg); exit(1);}


int main(int ac, char *av[])
{
    int sock_id, sock_fd;   //the socket and fd
    struct sockaddr_in servadd; //the number to call
    struct hostent *hp;  //used to get number
    int messlen; //for message length
    char message[BUFSIZ];
    //step 1: Get a socket

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id == -1)
    {
        oops("socket");
    }

    //Setp 2: Connect to server
    //      need to build address (host, port) of server first
    //bzero(&servadd, sizeof(servadd));
    memset(&servadd, 0, sizeof(servadd));
    hp = gethostbyname(av[1]);
    if(hp == NULL){
        oops(av[1]);
    }

    bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);
    
    servadd.sin_port = htons(atoi(av[2]));
    
    servadd.sin_family = AF_INET;//fill in socket type

    if(connect(sock_fd, (struct sockaddr *)&servadd, sizeof(servadd) != 0))
    {
        oops("connect");
    }

    messlen = read(sock_id, message, BUFSIZ);
    if(messlen == -1)
        oops("read");
    if(write(1, message, messlen) != messlen)
        oops("write");
    close(sock_id);



}