/**play_again1.c
 * purpose:ask if user wants another transaction
 * method: set tty into char-by-char mode, 
 *         read mode and no echo mode
 *         set tty into no-delay mode
 * return result
 * returns: 0=>yes, 1=>no
 * better: reset terminal mode on Interrupt 
 */

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define QUESTION "do you want another transaction"
#define TRIES 3
#define SLEEP 2
#define BEEP putchar('\a')

int get_response(char *, int maxtries);
void set_cr_noecho_mode();
void set_nodelay_mode();
void tty_mode(int);

int main()
{
    int response;
    tty_mode(0);//save the original tty mode
    set_cr_noecho_mode();//set char-by-char mode
    set_nodelay_mode();//noinput -> EOF
    response = get_response(QUESTION, TRIES);//get y/n
    tty_mode(1);//recover the original tty mode

    return response;
}

int get_response(char * question, int maxtries)
/**
 * purpose:ask a question and wait for a y/n answer
 * method: use getcahr and ignore  other non y/n answers
 * return 0=>yes, 1=>no
*/
{
    int input;
    printf("%s (y/n)?\n", question);
    fflush(stdout); //perhaps ↑ use \n so it not works??
    while(1){
        sleep(SLEEP);
        input = tolower(get_ok_char());
        if(input == 'y'){
            return 0;
        }
        if(input == 'n'){
            return 1;
        }
        if(maxtries-- == 0){
            return 2;
        }
        BEEP;//it's slow me a lot
    }
}
int get_ok_char(){
    int c;
    while((c = getchar()) != EOF && strchr("YyNn", c) == NULL)
        ;
    return c;
}
void set_cr_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}
void set_nodelay_mode(){
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NDELAY;
    fcntl(0, F_SETFL, termflags);
}

void tty_mode(int how)
{
    static struct termios original_mode;
    static int original_flags;
    if(how == 0){
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
    }else{
        tcsetattr(0, TCSANOW, &original_mode);
        // original_flags &= ~O_NDELAY;//if you use ctrl+c
        fcntl(0, F_SETFL, original_flags);
    }
}