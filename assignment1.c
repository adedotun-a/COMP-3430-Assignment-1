#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct timespec diff(struct timespec start, struct timespec end);

static void *hard_work(void *work)
{
    int *amount = (int *)work;
    struct timespec t = {.tv_sec = 0, .tv_nsec = *amount * 100000};
    nanosleep(&t, NULL); // **Really** hard work.
    return amount;
}

int main(int argc, char *argv[])
{
    int workRate = 5000;
    struct timespec time1, time2;
    int numProcesses;
    int numConcurrent;
    if (argc > 1)
    {
        numProcesses = atoi(argv[1]);
        numConcurrent = atoi(argv[2]);
    }
    else
    {
        printf("Please enter the value of x: ");
        scanf("%d", &numProcesses);
        printf("Please enter the value of y: ");
        scanf("%d", &numConcurrent);
    }
    clock_gettime(CLOCK_REALTIME, &time1);
}