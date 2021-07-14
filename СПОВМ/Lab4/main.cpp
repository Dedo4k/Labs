#include <iostream>
#include <vector>
#include <unistd.h>
#include "signal.h"
#include "kbhit.h"
#include <sys/wait.h>
#include <pthread.h>

using namespace std;

void *print(void *);

int main(int argc, const char *argv[])
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigprocmask(SIG_BLOCK, &set, NULL);

    int reciever = 0;

    int currentThread = 0;

    vector<pthread_t> threads;

    keyboard keyboard;

    while (true)
    {
        if (keyboard.kbhit())
        {
            switch (keyboard.getch())
            {
            case '+':
                    pthread_t thread;
                    pthread_create(&thread, NULL, print, NULL);
                    threads.push_back(thread);
                    break;
            case '-':
                if (!threads.empty())
                {
                    pthread_cancel(*(threads.rbegin()));
                    pthread_join(*(threads.rbegin()), NULL);
                    threads.pop_back();
                }
                break;
            case 'q':
                while (!threads.empty())
                {
                    pthread_cancel(*(threads.rbegin()));
                    pthread_join(*(threads.rbegin()), NULL);
                    threads.pop_back();
                }
                return 0;
            }
        }

        if (!threads.empty())
        {
            if (currentThread >= threads.size())
            {
                cout << endl;
                fflush(stdout);
                currentThread = 0;
            }
            usleep(200000);
            pthread_kill(threads[currentThread], SIGUSR1);

            sigwait(&set, &reciever);
            currentThread++;
        }
    }
}

void *print(void *)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);

    int reciever = 0;

    while (true)
    {
        sigwait(&set, &reciever);
        pthread_t thread = pthread_self();
        string string = to_string(thread);

        auto iterator = string.begin();
        do
        {
            cout << *iterator;
            fflush(stdout);
            iterator++;
            usleep(100000);
        } while (iterator != string.end());

        cout << endl;

        kill(getpid(), SIGUSR2);
    }
}