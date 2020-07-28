## 01_process

- fork: ``pid_t fork(void)``
    - desc: fork create new process __by duplicating the calling process.__  
    new process is referred as ``child process``.  
    child prcess and parent process run in seperatre memory spaces.  
    at the time of ``fork()`` called, bote memory spaces have the same content,  
    writes with ``mmap()`` and unmap with ``munmap()``.

