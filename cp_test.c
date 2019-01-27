#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int ac, char* avs[]){
    int fd_in, fd_out;

    if((fd_in = open(avs[0], O_RDONLY)) != -1)
    {
            printf("fd_in = %d", fd_in);

        if(fd_out = open(avs[0], O_WRONLY) != -1)
        {
            printf("fd_in == fd_out?  %d", fd_in == fd_out);
        }else{
            printf("fd_in == fd_out?  %d", fd_in == fd_out);

        }
    }

    close(fd_in);
    close(fd_out);
}