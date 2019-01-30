#include <stdio.h>
#include <termios.h>

#define oops(s, x) {perror(s); exit(x);}

main(int ac, char *av[]){
    struct termios info;

    if(ac < 2){
        exit(0);
    }
    if(tcgetattr(0, &info) == -1){
        oops("tcgetattr", 1);
    }
    if(av[1][0] != 'y'){
        info.c_lflag &= ~ECHO;
    }else{
        info.c_lflag |= ECHO;
    }

    if(tcsetattr(0, TCSANOW, &info) == -1){
        oops("tcsetattr", 1);
    }
    return 0;
}