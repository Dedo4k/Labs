
#include <iostream>
#include <curses.h>

#include <sys/wait.h>
#include <unistd.h>

void printTime(){
    initscr();
    time_t now;
    for (int i = 0; i < 10; i++) {
        now = time(0);
        printw("%s", ctime(&now));
        refresh();
        napms(1000);
    }
}


int main(int argc, const char * argv[]) {
    
    while(true){
        int pid = fork();
        
        if(pid == -1){
            return 0;
        }
        
        if(pid == 0){
            execvp("/home/vlad/VSCProjects/spovm/lab1/child", NULL);
        }else{
            printTime();
            
            int status;
            waitpid(pid, &status, 0);
            endwin();
            return 0;
        }
    }
}
