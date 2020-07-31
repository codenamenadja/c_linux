## 03_Process_wait

### SIGCHLD

> when process terminates, kernel sends SIGCHILD signal to parent process.

_``SIGCHLD``_ interrupts like asyncronously to parent process.

- ``wait()``
    - ``pid_t wait (int *status);//<sys/wait.h>``

    - DESC:
        All of these syscalls are used to wait for stat chages in child process.  
if child has already changed state, then there calls return immediately.  
_if not,_ these call blocks untils child changes state or signal handler interrupts the call.

    - state chages:
        1. child was terminated
            - performing a wait allows the system to release the resources associated with the child.
            - if wait() not called in parent process, terminated child remains in ``zombie`` state.
        2. child was stopped by a signal
        3. child was resumed by a signal

    - RETURNS:
        - SUCCESS:
            process ID of child whose state has changed.
        - FAILURE:
            -1

- wait_family

    1. ``pid_t wait(int *wstatus)``
    2. ``pid_t waitpid(pid_t pid, int *wstatus, int options);``
    3. ``int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);``
