
#include <iostream>
#include <unistd.h>
#include "signal.h"


using namespace std;

int main(int argc, const char * argv[]) {
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);
    int reciever =0;
    while(true){
        sigwait(&set, &reciever);
        string string = to_string(getpid());
        
        auto iterator = string.begin();
        do {
            cout << *iterator;
            fflush(stdout);
            iterator++;
            usleep(100000);
        } while(iterator!= string.end());
        
        cout << endl;
        fflush(stdout);
        
        kill(getppid(), SIGUSR2);
    }
    return 0;
}
