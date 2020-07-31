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

    - TEST util
        - ``taskset -c 0 ./<FILENAME> <n_process> <TOTAL_TIME> <INTERVAL>

        - taskset program
            - DESC: retrive the CPU affinity of a running process.
            - MEANS: taskset may use ptrace to observe and control the execution of another process.
             
    - CONCLUSION
        - when using single logical cpu, except io/bound work?  
time slicing equals.
        - after forks a process and main_process check spawned process right away,  
it's easliy processed as pid not generated yet.  
checking pid generated should work after a slight single work.
    
2. ``lscpu`` program.

    - DESC:

        lscpu gathers CPU architecture information from sysfs, /proc/cpuinfo  
and any applicable architecture-specific libraries.

    - COLUMNS:

        - CPU: logical CPU number of a CPU as used by the kernel.
        - CORE: logical core number. core can contain several cpus.
        - SOCKET: logical socket number. socket can contain serveral cores.
        - BOOK: logical book number. book can contain several sockets.
        - DRAWER: logical drawer number. drawer can contain several books.
        - NODE: logical NUMA node number, node can contain serveral drawers.
        - CACHE: info about how caches are shared between CPUs.
        - ADDRESS: Physical address of a CPU.
        - ONLINE: indicator, shows linux instance currently make use of cpu or not
        - CONFIGURED: indicator, shows if hypervisor allocated the cpu to virtual hardware on which linux instance runs.  
cpus that are configured can be set only if hardware system and hypervisor supprot ``dynamic CPU resource allocation``.
        - POLARIZATION: contains data for linux instance run on v_hd with hyper_v which can switch the ``cpu dispatching mode (polarization)``.  
polarization can be,
            - horizontal: workload is spread across all avail CPUs.
            - vertical: workload is concentrated on few CPUs.
        - MAXMHZ: maximum magahertz value for the cpu.  
(useful when ``lscpu`` is used as hardware inventory information gathering tool).  
megahertz value is dynamic, driven by CPU governor depending on current resource need.
        - MINMHZ: minimun megahertz value for cpu.

    - MY CPU

    ```bash
    # my cpu
    Architecture:        x86_64
    CPU op-mode(s):      32-bit, 64-bit
    Byte Order:          Little Endian
    CPU(s):              4
    On-line CPU(s) list: 0-3
    Thread(s) per core:  2
    Core(s) per socket:  2
    Socket(s):           1
    NUMA node(s):        1
    ```

        - DESC:
            - in 1 Socket has 2 cores.
            - core has 2 Threds.
            - logical cpu is 4cpu.
            - logical cpu is virtualized by "VT-x" intel.

    - multiple LOGICAL_CPU scheduling

        
