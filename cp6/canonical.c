#include <stdio.h>
#include <ctype.h>
//you can use stty -canoni -echo
//to try this ex
int main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == 'z')
        {
            c = 'a';
        }
        else if (islower(c))
        {
            c++;
        }
        putchar(c);
    }

    return 0;
}