#!/bin/sh
gcc 01_sched_with_priority.c -o sched
rm result_*.txt
echo "taskset -c 0 ./<program name> 100ms 1ms will be executed"
echo "task 2 process, work for 1s, check at 1ms.." 
taskset -c 0 ./sched 1000 1 > result_1.txt
echo ""
echo "task 2 process, work for 1s, check at 1ms.." 
taskset -c 0 ./sched 10000 1 > result_2.txt
rm sched
echo "removed elf file"

# taskset -c: -cpu-list option.
# read number as mask of numerical list of processors not bit mask
# ie) 0,5,8-11

