#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int numProcesses;
int numConcurrent;
int workRate = 5000;

struct timespec diff(struct timespec start, struct timespec end);
static void threads();
static void processes();

static void *hard_work(void *work)
{
    int *amount = (int *)work;
    struct timespec t = {.tv_sec = 0, .tv_nsec = *amount * 100000};
    nanosleep(&t, NULL); // **Really** hard work.
    return amount;
}

int main(int argc, char *argv[])
{
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
}

static void threads()
{
    pthread_t pid[numConcurrent];
    void *returnValues[numConcurrent];
    struct timespec time1, time2;
    clock_gettime(CLOCK_REALTIME, &time1);
    while (numProcesses > 0)
    {
        for (int i = 0; i < numConcurrent; i++)
        {
            if (numProcesses < 1)
            {
                break;
            }
            pthread_create(&pid[i], NULL, hard_work, (void *)&workRate);
            // printf("Forking into index %d\n", numProcesses--);
            numProcesses--;
        }

        for (int j = 0; j < numConcurrent; j++)
        {
            if (numProcesses < 1)
            {
                break;
            }
            if (pthread_join(pid[j], &returnValues[j]) == 0)
            {
                // printf("Forking into index %d\n", numProcesses--);
                numProcesses--;
            }
        }
    }

    clock_gettime(CLOCK_REALTIME, &time2);

    printf("Time elapsed is %ld nanoseconds\n", diff(time1, time2).tv_nsec);
}

static void processes()
{
    struct timespec time1, time2;
    clock_gettime(CLOCK_REALTIME, &time1);

    for (int i = 0; i < numConcurrent; i++)
    {
        int pid = fork();

        if (pid == 0)
        {
            printf("Forking into index %d\n", numProcesses);
            hard_work((void *)&workRate);
            exit(0);
        }
        numProcesses--;
    }
    for (int j = numProcesses; j > 0; j--)
    {
        wait(NULL);
        // numProcesses--;
        printf("Forking into index %d\n", j);
        int pid = fork();
        if (pid == 0)
        {
            hard_work((void *)&workRate);
            exit(0);
        }
    }

    clock_gettime(CLOCK_REALTIME, &time2);

    printf("Time elapsed is %ld nanoseconds\n", diff(time1, time2).tv_nsec);
}
