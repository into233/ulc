#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LINELEN 20


int main(int ac, char *args[])
{
    FILE *fp;
    char buf[LINELEN];

    if((fp = open(args[0], "r")) != -1){
        while(fgets(buf, LINELEN, fp))
        {
            sleep(20000);
            if(fputs(buf, stdout) == EOF){
                exit(1);
            }
        }
    }else{
        printf("error input");
    }

    
    return 0;

}
