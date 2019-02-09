#include <stdio.h>
#include <signal.h>

void f(int);

int main()
{
    signal(SIGINT, f);
    signal(SIGKILL, SIG_IGN);

    int i = 0;
    while(i < 10){
        printf("hello  \n");
        sleep(1);
        i++;
    }
}
void f(int singnum){
    printf("I'm dying !!!! eeee%d\n", singnum);
    exit(1);
}