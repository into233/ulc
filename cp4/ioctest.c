#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

void print_screen_profile(){
    struct winsize winbuf;

    if(ioctl(0, TIOCGWINSZ, &winbuf) != -1){
        printf("windows clo is %d, row is %d \n", winbuf.ws_col, winbuf.ws_row);
        printf("windows x is %d, y is %d \n", winbuf.ws_xpixel, winbuf.ws_ypixel);
    }

}

int main(){
    print_screen_profile();
}

