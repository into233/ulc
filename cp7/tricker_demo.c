#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

int main()
{
    void countdown(int);
    signal(SIGALRM, countdown);
    if(set_tricker(1000) == -1){
        perror("set_tricker");
    }else{
        while(1){
            pause();
        }
    }

    return 0;
}
void countdown(int signum)
{
    static int num = 10;
    printf("%d ...", num--);
    fflush(stdout);
    if(num == 0){
        printf("DONE");
        exit(0);
    }
}

int set_tricker(int n_msecs)
{
    struct itimerval new_itimeset;

    long n_sec, n_usecs;

    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000;

    new_itimeset.it_interval.tv_sec = n_sec;
    new_itimeset.it_interval.tv_usec = n_usecs;
    new_itimeset.it_value.tv_sec = n_sec;
    new_itimeset.it_value.tv_usec = n_usecs;
    
    return setitimer(ITIMER_REAL, &new_itimeset, NULL);
}