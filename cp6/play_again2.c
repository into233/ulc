/**play_again1.c
 * purpose:ask if user wants another transaction
 * method: set tty into char-by-char mode, read mode and no echo mode
 * return result
 * returns: 0=>yes, 1=>no
 * better: do no echo inappropriate input 
 */

#include <stdio.h>
#include <termios.h>

#define QUESTION "do you want another transaction"

int get_response(char *);
void set_cr_noecho_mode();
int main()
{
    int response;
    tty_mode(0);//save the original tty mode
    set_cr_noecho_mode();//set char-by-char mode
    response = get_response(QUESTION);//get y/n
    tty_mode(1);//recover the original tty mode

    return response;
}

int get_response(char * question)
/**
 * purpose:ask a question and wait for a y/n answer
 * method: use getcahr and ignore  other non y/n answers
 * return 0=>yes, 1=>no
*/

{
    printf("%s (y/n)?\n", question);
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
void set_cr_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

tty_mode(int how)
{
    static struct termios original_mode;
    if(how == 0){
        tcgetattr(0, &original_mode);
    }else{
        return tcsetattr(0, TCSANOW, &original_mode);
    }
}