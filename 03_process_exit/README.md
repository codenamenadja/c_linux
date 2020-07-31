## 03_exit_process

1. ``exit()``
    - ``void exit (int status); //<stdlib.h>``
    
    - DESC:
        causes normal process termination.  
value of ``status & 0377`` is returned to parent.  
_Wraaper function of ``_exit()`` function call_.

    - ACTIONS:
        1. return upper value to parent process.
        2. all functions registered with ``atexit()``, ``on_exit()`` called in reverse order of registration
        3. open all stream's buffer, fflush()
        4. remove all temp files made by using ``tmpfile()``.

2. ``atexit()`` // glibc official
    - ``int atexit(void (*function)(void));//<stdlib.h>``

    - DESC:
        registers a given function to be called at noremal process termination.  
via ``exit()`` or via ``return`` from the program's ``main()``

    - RETURNS:
        - ON_SUCCESS: 0
        - FAILURE: non zero

3. ``on_exit()`` // sunos official
    - ``int on_exit(void (*function)(int , void *), void *arg);// <stdlib.h>``
 
    - DESC:
        registers given fuction like wise.  this function is not come from glibc

    - ALERT:
        but, Portable application should avoid this function.

4. ``tmpfile()``
    - ``FILE *tmpfile(void); //<stdio.h>``

    - DESC:
        opens a ``unique`` temp file in binary read/write(w+b) mode.  
automatically deleted when is closed or program terminates.

    - RETURNS:
        - SUCCCESS: stream descriptor
        - FAILURE: NULL
            - NULL: if a unique filename cannot be gneratred or cannot be opened.

5. ``_exit()`` and ``_Exit()``
    - ``void _exit(int status);//<unistd.h>``  ``void _Exit(int status);//<stdlib.h>``
    - DESC:
        ``_exit()`` terminates the calling process _"imediately"_.  
beloning fildescriptors are closed.  
children of process are ingerited by ``init(1)``  
process's parent is sent a SIGCHLD signal  
value ``status & 0377`` is returns to parent process, and value can be collected using one of the ``wait()``family of calls.  
function ``_EXIT()`` is eq to ``_exit()``

    - RETURNS:
        NO return

    ### SIGCHILD

    > when process terminates, kernel sends SIGCHILD signal to parent process.  
    > default, do nothing on this signal.  
    > but if to use ``signal()`` or ``sigaction()`` can handle the signal. 

