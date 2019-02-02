#include <stdio.h>

#define QUESTION "do you want another transaction"

int get_response(char *);

int main()
{
    int response;

    response = get_response(QUESTION);
    
    return response;
}

int get_response(char * question)
/**
 * purpose:ask a question and wait for a y/n answer
 * method: use getcahr and ignore  other non y/n answers
 * return 0=>yes, 1=>no
*/

{
    printf("%s (y/n)?", question);
    while(1){
        switch (getchar())
        {
            case 'y':
            case 'Y':return 0;
            case 'n':
            case 'N':
            case EOF:return 1;
        }
        
    }
}