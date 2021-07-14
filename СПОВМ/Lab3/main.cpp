#include <iostream>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main()
{
    sembuf sembuf;
    int semaphore = semget(ftok("/home/vlad/VSCProjects/spovm/lab3/main", 200), 2, IPC_CREAT | 0777);

    if (semaphore == -1)
    {
        perror("semget error");
    }

    int piped[2] = {};

    if (pipe(piped) == -1)
    {
        perror("pipiDescriptor error");
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("pid error");
    }
    else if (pid == 0)
    {
        close(piped[1]);
        while (true)
        {
            sembuf.sem_num = 0;
            sembuf.sem_op = -1;
            semop(semaphore, &sembuf, 1);

            int msLength = 0;
            read(piped[0], (char *)&msLength, sizeof(int));
            char *message = new char[msLength + 1];
            read(piped[0], (char *)message, (msLength + 1));
            cout << endl
                 << "<<<Client>>>" << endl;
            cout << "Message (recieved:" << msLength << "): " << message << endl;

            delete[] message;

            sembuf.sem_num = 1;
            sembuf.sem_op = 1;
            semop(semaphore, &sembuf, 1);
        }
    }

    close(piped[0]);

    while (true)
    {
        cout << endl
             << "<<<Server>>>" << endl;
        cout << "Send [q], Exit [e]." << endl;
        fflush(stdin);
        switch (getchar())
        {
        case 'q':
        {
            cout << endl <<"<<<Server>>>" <<endl;
            cout << endl << "Enter message: ";
            string message;
            cin.ignore(32767,'\n');
            getline(cin, message);

            int msLength = message.length();
            write(piped[1], (char *)&msLength, sizeof(int));
            write(piped[1], message.c_str(), msLength);

            cout << "Sended: " << msLength << endl;
            fflush(stdout);

            sembuf.sem_num = 0;
            sembuf.sem_op = 1;
            semop(semaphore, &sembuf, 1);

            sembuf.sem_num = 1;
            sembuf.sem_op = -1;
            semop(semaphore, &sembuf, 1);
            break;
        }
        case 'e':
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, NULL);
            close(piped[1]);
            return 0;
            break;
        }
        }
    }
}