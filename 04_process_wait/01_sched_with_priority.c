#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define NLOOP_FOR_ESTIMATION    1000000000UL
#define NSECS_PER_MSEC          1000000UL
#define NSECS_PER_SEC           1000000000UL

static unsigned long        loops_per_msec();

static inline void          load(unsigned long n_loop);

static void                 parent_fn(int n_proc);

static inline long          diff_nsec(
        struct timespec t_before, struct timespec t_after
        );

static void                 child_fn(
        int id, struct timespec *buf,
        int n_record, unsigned long n_loop_per_itv,
        struct timespec start_t
        );
static                      pid_t *pids;

#include <assert.h>
int argv_validation(int argc, char *argv[]);
int main(int argc, char *argv[])
{
    int n_proc, total_t, check_itv_t;
    int n_record; // count of logs
    struct timespec *log_buf; // check log buffer
    unsigned long n_loop_per_check; // check_itv_t * loops_per_msec
    struct timespec start_t;
    int i, n_created;
    int ret;

    ret = EXIT_FAILURE;
    // 1. check argument
    if (argv_validation(argc, argv))
        return (EXIT_FAILURE);

    // 2. parse argv 
    n_proc = 2; // number of processes
    total_t = atoi(argv[1]); // time of program running
    check_itv_t = atoi(argv[2]); // unit-time of checking interval

    // 3. check times
    n_record = total_t / check_itv_t;
 
    // 4. mem allocation of structure timespec, for n_record times.
    log_buf = malloc(sizeof(struct timespec) * n_record);
    if (!log_buf)
        err(EXIT_FAILURE, "malloc(sizeof(timespect) * n_record)) failed.");
 
    // 5. recordable times in 1ms * interval : for interval how many loops?
    n_loop_per_check = (loops_per_msec() * check_itv_t); // #1 loops_per_msec

    // 6. pointer to store pid to static variable
    pids = malloc(n_proc * sizeof(pid_t));
    if (!pids)
    {
        warn("malloc(pids) failed");
        goto free_log_buf;
    }

    // 7. get time and store to start_t
    clock_gettime(CLOCK_MONOTONIC, &start_t);
    
    pid_t origin_pid = getpid();
    printf("callerProcess_%d will create %d process.\n", origin_pid, n_proc);
    printf("\n");
    for (i = 0, n_created = 0; i < n_proc; i++, n_created++)
    {
        pids[i] = fork(); // gen copy of process
        if (origin_pid == getpid())
            printf("caller_Process_%d: %dth process created as pid:%d\n", origin_pid, i, pids[i]);
        if (pids[i] < 0) // pid not generated and returned yet
        {
            printf("%d, pid not generated in pid[%d], now is %d\n", i, i, pids[i]);
            goto wait_pid_gen; // go wait for pid genrates
        }
        if (pids[i] == 0) // pid 0 means it's forked process
        {
            printf("child process %d start entry entered\n",i);
            if (i == 1)
                nice(5); // ---------- new added part
            child_fn(i, log_buf, n_record, n_loop_per_check, start_t); // #2 process differs
        }
            //execve and break from this code
        // origin process keeps POP_TOP
    }
    printf("caller_Process_%d ends for-fork loop.\n", getpid());
    printf("exit by%d\n", getpid());
    ret = EXIT_SUCCESS;
    exit(EXIT_SUCCESS); // origin process can meet this line
wait_pid_gen:
    printf("goto wait_pid_gen\n");
    if (ret == EXIT_FAILURE)
    {
        i = -1;
        while (++i < n_created) // one fail all fail.
            if (kill(pids[i], SIGINT) < 0) // >
                warn("kill(%d) process failed", pids[i]);
    }
    i = -1;
    while (++i < n_created) // check all killed?
        if (wait(NULL) < 0) // ?
            warn("wait() failed.");


    free_pids:
        printf("goto free_pids\n");
        free(pids);


    free_log_buf:
        printf("goto free_log_buf\n");
        free(log_buf);


    printf("a line which should not be reached, by %d\n", getpid());
    return (EXIT_FAILURE);
}


int argv_validation(int argc, char *argv[])
{
    // 1. check argc count is at least 4
    assert(argc > 2);
    if (argc < 2)
        return (EXIT_FAILURE);

    // 2. parse argv
    int n_proc, total_t, check_itv_t;
    n_proc = 2; // number of processes
    total_t = atoi(argv[1]); // time of program running
    check_itv_t = atoi(argv[2]); // unit-time of checking interval

    assert(n_proc >= 1); // at least 2 process work means scheduling
    assert(total_t >= 1); // ms 100ms == 1s
    assert(check_itv_t >= 1); // check interval at least 2ms
    if (n_proc < 1 || total_t < 1 || check_itv_t < 1)
        return (EXIT_FAILURE);

    assert(total_t % check_itv_t == 0); // interval should end with total worktime
    if (total_t % check_itv_t)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}


// function returns (estimations in 1ms) / (start end, time diff) 
static unsigned long        loops_per_msec()
{
    struct timespec t_before, t_after;
    unsigned long i;

    clock_gettime(CLOCK_MONOTONIC, &t_before);

    i = 0;
    while (i++ < NLOOP_FOR_ESTIMATION) // delay time
        continue;

    clock_gettime(CLOCK_MONOTONIC, &t_after);
    return (NLOOP_FOR_ESTIMATION * NSECS_PER_MSEC / diff_nsec(t_before, t_after));
}

static void                 child_fn(int id, struct timespec *buf, int n_record, unsigned long n_loop_per_itv, struct timespec start_t)
{
    int i;

    i = -1;
    while (++i < n_record)
    {
        struct timespec ts;

        load(n_loop_per_itv); // ?
        clock_gettime(CLOCK_MONOTONIC, &ts);
        buf[i] = ts;
    }

    i = -1;
    while (++i < n_record)
        printf("%d\t%ld\t%d\n", id, (diff_nsec(start_t, buf[i]) / NSECS_PER_MSEC),
                ((i + 1) * 100) / n_record);
    if (id ==1)
        printf("%d:%d process nice+5 exits\n", id, getpid());
    else
        printf("%d:%d process exits\n", id, getpid());
    exit(EXIT_SUCCESS);
}

static inline long          diff_nsec(struct timespec t_before, struct timespec t_after)
{
    return (((t_after.tv_sec * NSECS_PER_SEC) + t_after.tv_nsec) -
        ((t_before.tv_sec * NSECS_PER_SEC) + t_before.tv_nsec));
}

static inline void          load(unsigned long nloop)
{
    unsigned long   i;
    i = 0;
    while(i++ < nloop);
}
