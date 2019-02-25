#include <stdio.h>

int main()
{
    int i = 0;
    for(i = 0;i < 4;++i){
        printf("my pid = %d, i = %d\n", getpid(), i);
        sleep(1);
        if(fork() == -1){
            exit(0);
        }
    }


    return 0;
}