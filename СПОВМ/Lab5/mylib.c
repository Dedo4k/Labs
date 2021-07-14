#include <stdio.h>
#include <stdlib.h>
#include <aio.h>
#include <dlfcn.h>
#include <string.h>

int writoToFile(char *filename, char *data)
{
    FILE *file = fopen(filename, "a");

    struct aiocb aio;
    aio.aio_fildes = fileno(file);
    aio.aio_offset = 0;
    aio.aio_buf = data;
    aio.aio_nbytes = strlen(data) - 1;

    int st = aio_write(&aio);
    if (st)
        printf("Error: %d\n",st);

    const struct aiocb *list[1];
    list[0] = &aio;

    st = aio_suspend(list, 1, NULL);
    if (st)
        printf("Error: %d\n",st);

    st = aio_error(&aio);
    if (st)
        printf("Error: %d\n",st);

    fclose(file);
    return 0;
}

char *readFromFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    char *buf = (char *)calloc(250, sizeof(char));

    struct aiocb aio = {0};
    aio.aio_fildes = fileno(file);
    aio.aio_offset = 0;
    aio.aio_buf = buf;
    aio.aio_nbytes = 250;

    int st = aio_read(&aio);
    if (st)
        printf("Error: %d\n",st);

    const struct aiocb *list[1];
    list[0] = &aio;

    st = aio_suspend(list, 1, NULL);
    if (st)
        printf("Error: %d\n",st);

    st = aio_error(&aio);
    if (st)
        printf("Error: %d\n",st);

    fclose(file);
    return buf;
}