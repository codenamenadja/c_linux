## 03_Process_wait

### SIGCHLD

> when process terminates, kernel sends SIGCHILD signal to parent process.

_``SIGCHLD``_ interrupts like asyncronously to parent process.

1. ``wait()``
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

2. ``nice()``
    - ``int nice(int inc); //<unistd.h>``
    - DESC:
        add int to nice value for alling thread.
    - Nice value
        range of nice value is +19(low priority) ~ -20(high priority).
    - RETURNS
        - SUCCESS:
            new nice value
        - FAILURE:
            -1, and errno sets


3. multi process stat Program with priority using ``nice()``

    - What to work
        1. running process limits to 2 only.
        2. measure progresses of each process
        3. one process nice with value 0, other 5.

    - SPEC
        - cmd line parameter(total, resol)
            1. total: time of program running(in ms)
            2. resol: data collecting interval(in ms)

    - procedure
        - after process generated,
        - if process itself is second genrated one, set self nice as 5

