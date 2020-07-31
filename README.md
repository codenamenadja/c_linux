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
