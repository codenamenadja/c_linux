#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void callback()
{
    printf("registered function called\n");
}

int main(void)
{
    long    a;
    int     i;

    a = sysconf(_SC_ATEXIT_MAX);
    printf("ATEXIT_MAX = %ld\n", a);

    i = atexit(callback);
    if (i)
    {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
