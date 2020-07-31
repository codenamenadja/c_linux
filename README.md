# 01_process

- fork: MAKE PROCESS COPY AND EXECUTE BOTH, INHERITS .TEXT PROGRESS
- execve: MAKE RUN PROGRAM AT CALLEE PROCESS AND EXECUTE FROM THE .TEXT ENTRYPOINT
- ptrace: Processes a tracing. defined in ``<sys/ptrace.h>``
- fflush: flush a stream, means, do things that should be done.

## 02_process_scheduling

1. multi process stat Program
    - What to work
        1. what process is in progress at specific point
        2. measure progresses of each process
2. ``lscpu`` program.
    - DESC:
        lscpu gathers CPU architecture information from sysfs, /proc/cpuinfo  
and any applicable architecture-specific libraries.
## 03_exit_process

1. ``exit()``
    - DESC:
        causes normal process termination.  

2. ``atexit()`` // glibc official
    - DESC:
        registers a given function to be called at noremal process termination.  
via ``exit()`` or via ``return`` from the program's ``main()``

3. ``on_exit()`` // sunos official
    - DESC:
        registers given fuction like wise.  this function is not come from glibc

4. ``tmpfile()``
    - DESC:
        opens a ``unique`` temp file in binary read/write(w+b) mode.  

5. ``_exit()`` and ``_Exit()``
    - DESC:
        ``_exit()`` terminates the calling process _"imediately"_.

### SIGCHILD
> when process terminates, kernel sends SIGCHILD signal to parent process.  

