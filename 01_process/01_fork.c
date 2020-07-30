#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <err.h>

static void child()
{
    pid_t cur_pid;

    cur_pid = getpid();
    printf("expect as child process, is %d\n", cur_pid);
    // child process have no idea about parents things.
    exit(EXIT_SUCCESS);
}

static void caller(pid_t pid_c)
{
    printf("expect as parent process, is %d and child expects as %d\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

int main(void)
{
    pid_t ret;

    ret = fork(); // 1.fork() returns pid of process very fast.
    if (ret == -1)
        err(EXIT_FAILURE, "fork()failed");
    else if (ret == 0) // 3. fork() will be done with 0 in child procees.
        child();
    else // 2. ret is pid at this point. caller exits first
        caller(ret);
    err(EXIT_FAILURE, "totally error");
}
