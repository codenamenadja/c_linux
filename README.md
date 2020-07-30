## 01_process

- fork: MAKE PROCESS COPY AND EXECUTE BOTH, INHERITS .TEXT PROGRESS
    - ``pid_t fork(void)``
    - start from parent process's code progress. copy all things to completly different memspace.
    - desc: fork create new process __by duplicating the calling process.__  
    new process is referred as ``child process``.  
    child prcess and parent process run in seperatre memory spaces.  
    at the time of ``fork()`` called, bote memory spaces have the same content,  
    writes with ``mmap()`` and unmap with ``munmap()``.

    - Note:
        - child process is created wuth single thread.
        - virtual address space of parent replicated in the child.
            - includes, states of mutexes, condition variables, other pthreads object.
        - after fork call in mulitithreaded program, child cand safely call only async-signal-afe functions,  
until such time as it calls execve

- execve: MAKE RUN PROGRAM AT CALLEE PROCESS AND EXECUTE FROM THE .TEXT ENTRYPOINT
    - ``int execve(const char *filename, char *const argv[], char *const envp[]);``
    - executes the program to ``filename`` and file must be binary executable or,  
script starting with a line of form:
        - ``#! interpreter [optional-arg]``: instantly iterprets program with specified interpreter.
            - ie) ``#!/bin/sh``
    - ARGUMENTS:
        1. ``char *const argv`` is an array of arguments strings, passes to new program.
            - By convention, first of these strings should contain the filename associated with the file being executed.
        2. ``char *const envp[]`` is an array of strings.
            - form of key=value, which are passed as environment to the new program.
        - ``argv``, ``envp`` arrays must each include NULL pointer at the end of the array.

    - RETURNS:
        - does not return on success.: break from caller process.
        - text, initialized data, bss(uninitialized data), and tack of caller process are over written.
        - if current program is being ptraced, a ``SIGTRAP`` signal is sent to it after successful execve().


- ptrace: Processes a tracing. defined in ``<sys/ptrace.h>``
    - ``long ptrace(enum __ptrace_request request, pid_t pid, void *addr, void *data);``
    - DESC: caller, the tracer may observe and control the execution of other process(the callee, tracee),  
and examine and chage the tracee's memory and register.
    - It Primarily used to implement breakpoint debugging, and system call tracing.


- fflush: flush a stream, means, do things that should be done.
    - ``int fflush(FILE *stream);//in <stdio.h>``
    - DESC:
        - for output stream(writable), forces a write of all user-space buffered data  
or update stream via the stream's underlying write function.
        - for input streams associated with seekable files(files but not pipes or terminals),  
discards any buffered data which has been fetched from underlying file but not consumed by the application.
        - consumed means like read and fflushed.
 
___

## 02_process_scheduling

1. multi process stat Program

    - What to work
        1. what process is in progress at specific point
        2. measure progresses of each process

    - SPEC
        - cmd line parameter(n, total, resol)
            1. n: count of process work on same cpu.
            2. total: time of program running(in ms)
            3. resol: data collecting interval(in ms)
    - procedure
        1. start n of processes.
        2. each processes works like,
            - use cpu time for total ms-time and exit
            - for each use of resol ms-time in total ms-time
                - record their pid, program running time(in ms) and percentage of work progress.
            
