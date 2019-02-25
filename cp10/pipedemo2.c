#include <stdio.h>

#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS "TESTING....\n"
#define oops(m, x) { perror(m);exit(x) }

int main()
{
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;

    if(pipe(pipefd) == -1)
    {
        oops("Cannot get a pipe", 1);
    }

    weitch(fork()){
        case -1:
            oops("cannot fork", 2);
        case 0:
            len = strlen(CHILD_MESS);
            while(1){
                if(write(pipefd[1], CHILD_MESS, len) != len)
                    oops("write", 3);
                sleep(5);
            }
        
    }

}