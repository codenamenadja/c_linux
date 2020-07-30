#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static void child();
static void parent(pid_t pid_child);

int main(void)
{
    pid_t forked_pid;
    forked_pid = fork();

    if (forked_pid == -1) // caller can find it
        err(EXIT_FAILURE, "fork() failed!");
    else if (forked_pid == 0) // from other process, only a variable forked_pid changes to 0
        child();
    else // expects child process's pid returned, in context of parent process
        parent(forked_pid);
     err(EXIT_FAILURE, "should not reach here.");
}

static void parent(pid_t pid_c)
{
    printf("1.caller:'caller process: pid %d, forked process pid %d.'\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

static void child()
{
    char *args[] = {"/bin/echo", "hello", NULL};
    printf("2.forked process: 'pid %d'\n", getpid());
    fflush(stdout);
    execve("/bin/echo", args, NULL);// restart from entry point of echo bin-exe file.
    err(EXIT_FAILURE, "exec() failed");
}
