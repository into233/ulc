#include <stdio.h>
#include <curses.h>
main()
{
    initscr();
    
    clear();
    move(10, 20);
    for(int i = 0;i < LINES; ++i){
        
        move(i, 2 * i + 1);
        if(i % 2 == 1){
            standout();
        }
        addstr("HELLO WORLD");
        if(i % 2 == 1){
            standend();
        }
        sleep(1);
        refresh();

        move(i, 2 * i + 1);
        addstr("           ");

    }
    refresh();
    getch();
    endwin();

    return 0;
}