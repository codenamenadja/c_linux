## 01_process

- fork: ``pid_t fork(void)``
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
