#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <pthread.h>
#include <dirent.h>
#include <dlfcn.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>

#define DIRNAME "/media/vlad/93134a84-bc92-4b91-ae8e-ee30139e88df/vlad/VSCProjects/spovm/lab5"
#define OFNAME "file4.txt"
#define LIBPATH "/media/vlad/93134a84-bc92-4b91-ae8e-ee30139e88df/vlad/VSCProjects/spovm/lab5/lib.so"

sem_t semaphore1;
sem_t semaphore2;

int checkTxt(char *filename)
{
    int size = strlen(filename);
    if (filename[size - 3] == 't' && filename[size - 2] == 'x' && filename[size - 1] == 't')
        return 0;
    else
        return 1;
}

void *read(void *q)
{   
    char buf[256];
    char filename[128];
    int sharedMemory = shmget(200,sizeof(buf),IPC_CREAT|0666);
    struct dirent *de;
    DIR *dir = opendir(DIRNAME);
    void *handle = dlopen(LIBPATH, RTLD_LAZY);
    char *(*fun)(char *) = dlsym(handle, "readFromFile");

    while (de = readdir(dir))
    {
        if (!checkTxt(de->d_name))
        {
            strcpy(filename, de->d_name);
            printf("%s\n", filename);

            char* data = (*fun) (filename);
            strcpy(buf,data);
            printf("%s\n", buf);

            free(data);
        }
    }
    closedir(dir);
    return (void *)NULL;
}

void *write(void *q)
{
    char buf[256];
    int sharedMemory = shmget(200,sizeof(buf),0);
    DIR* dir = opendir(DIRNAME);
    struct dirent *de;
    void* handle = dlopen(LIBPATH,RTLD_LAZY);
    char* (*fun)(char*) = dlsym(handle,"writeToFile");
    

    
    //(*fun)(OFNAME,buf);

    return (void *)NULL;
}

int main(void)
{
    char memory[256];
    int sharedMemory = shmget(300, sizeof(memory), IPC_CREAT | 0666);

    pthread_t threadToRead;
    pthread_t threadToWrite;

    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 1);

    pthread_create(&threadToRead, NULL, read, NULL);
    pthread_create(&threadToWrite, NULL, write, NULL);

    pthread_join(threadToRead, NULL);

    pthread_cancel(threadToRead);
    pthread_cancel(threadToWrite);

    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);

    printf("\nExit.\n");

    return 0;
}