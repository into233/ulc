#include <stdio.h>

int main(int ac, char *args[])
{
    printf("ac = %d\n", ac);
    int av = 0;
    while(ac--){
        printf("av[%d] = %s\n", av++, args[av]);

    }



}
