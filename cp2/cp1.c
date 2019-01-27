#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFERSIZE 4096
#define COPYMODE 0664

void oops(char * mes, char *);

int main(int ac, char *argv[])
{
    int fd_in, fd_out, n_chars;
    char buf[BUFFERSIZE];
    printf("fd_in = %d, fd_out = %d", fd_in, fd_out);
    
    if(ac != 3){
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(-1);
    }

    if((fd_in = open(argv[1], O_RDONLY) == -1)){
        oops("Cannot open ", argv[1]);
    }
    printf("fd_in = %d, fd_out = %d", fd_in, fd_out);

    if((fd_out = creat(argv[2], COPYMODE)) == -1){
        oops("Cannot creat ", argv[2]);
    }
    
    while((n_chars = read(fd_in, buf, BUFFERSIZE)) > 0){
        if(write(fd_out, buf, n_chars) != n_chars)
            oops("Write errors ", argv[2]);
    }
    if(n_chars == -1){
        oops("Read error ", argv[1]);
    }

    if(close(fd_in) == -1 || close(fd_out) == -1){
        oops("Close error ", "");
    }

    return 0;
}
void oops(char *s1, char *s2){
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}