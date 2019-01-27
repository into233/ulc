#include <stdio.h>
#include <time.h>

int main()
{
    time_t timer = time(NULL);
    printf("ctiem is %s\n", ctime(&timer));
    return 0;

}
