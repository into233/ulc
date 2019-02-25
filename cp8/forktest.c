#include <stdio.h>

int main()
{
    int ret_from_fork, PID;
    PID = getpid();
    printf("Before: my pid is %d\n", PID);

    ret_from_fork = fork();

    sleep(1);
    printf("After: my pid is %d, and fork() said %d\n", getpid(), ret_from_fork);

    return 0;
}