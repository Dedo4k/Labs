#include <iostream>
#include <vector>
#include <unistd.h>
#include "signal.h"
#include "kbhit.h"
#include <sys/wait.h>

using namespace std;

int main(int argc, const char *argv[])
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    int reciever = 0;
    
    int currentProcess = 0;

    vector<pid_t> processes;

    keyboard keyboard;

    while (true)
    {
        if (keyboard.kbhit())
        {
            switch (keyboard.getch())
            {
            case '+':
                processes.push_back(fork());

                switch (*(processes.rbegin()))
                {
                case -1:
                    perror("fork");
                    break;
                case 0:
                {
                    sigset_t set;
                    sigemptyset(&set);
                    sigaddset(&set, SIGUSR1);
                    sigprocmask(SIG_BLOCK, &set, NULL);
                    
                    int reciever = 0;
                    
                    while (true)
                    {
                        sigwait(&set, &reciever);
                        string string = to_string(getpid());

                        auto iterator = string.begin();
                        do
                        {
                            cout << *iterator;
                            fflush(stdout);
                            iterator++;
                            usleep(200000);
                        } while (iterator != string.end());

                        cout << endl;
                        fflush(stdout);

                        kill(getppid(), SIGUSR2);
                    }
                    break;
                }
                default:
                    break;
                }
                break;
            case '-':
                if (!processes.empty())
                {
                    kill(*(processes.rbegin()), SIGKILL);
                    waitpid(*(processes.rbegin()), 0, 0);
                    processes.pop_back();
                }
                break;
            case 'q':
                while (!processes.empty())
                {
                    kill(*(processes.rbegin()), SIGKILL);
                    waitpid(*(processes.rbegin()), 0, 0);
                    processes.pop_back();
                }
                return 0;
            }
        }

        if (!processes.empty())
        {
            if (currentProcess >= processes.size())
            {
                cout << endl;
                fflush(stdout);
                currentProcess = 0;
            }
            usleep(200000);
            kill(processes[currentProcess], SIGUSR1);

            sigwait(&set, &reciever);
            currentProcess++;
        }
    }
}
