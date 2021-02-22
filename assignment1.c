/*
* COURSE: COMP 3340 SECTION [A02]
* INSTRUCTOR: Rasit Eskicioglu
* NAME: Adedotun Adeyemo
* ASSIGNMENT: 1
*
* PURPOSE: The program intended to compare and contrast threads and processes
           and see the performance differences when launching them.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

struct timespec diff(struct timespec start, struct timespec end);
static void runThreads(int numProcesses, int numConcurrent, int workRate);
static void runProcesses(int numProcesses, int numConcurrent, int workRate);

/*
 * This is used to simulate the work done by either the threads or processes
*/

static void *hard_work(void *work)
{
    int *amount = (int *)work;
    struct timespec t = {.tv_sec = 0, .tv_nsec = *amount * 100000};
    nanosleep(&t, NULL); // **Really** hard work.
    return amount;
}

/*
 * This calls the helper methods runProcesses and runThreads
*/

int main(int argc, char *argv[])
{
    int numProcesses;
    int numConcurrent;
    int workRate = 150;
    if (argc > 2)
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
    struct timespec time1, time2;
    clock_gettime(CLOCK_REALTIME, &time1);
    runThreads(numProcesses, numConcurrent, workRate);
    clock_gettime(CLOCK_REALTIME, &time2);

    printf("Time elapsed for threads is %ld nanoseconds\n", diff(time1, time2).tv_nsec);
    runProcesses(numProcesses, numConcurrent, workRate);
}

/*
 * This function implements the thread creation and perfomance testing for this program
 */
static void runThreads(int numThreads, int numConcurrent, int workRate)
{
    pthread_t pid[numConcurrent];
    void *returnValues[numConcurrent];
    struct timespec time1, time2;
    clock_gettime(CLOCK_REALTIME, &time1);

    /*
     * This creates the first batch of numConcurrent threads. 
     */
    for (int i = 0; i < numConcurrent; i++)
    {
        if (numThreads < 1)
        {
            break;
        }
        pthread_create(&pid[i], NULL, hard_work, (void *)&workRate);
        // printf("Creating thread index %d\n", numThreads--);
        numThreads--;
    }

    /*
    * Loops till the total number of threads have been made.
    * It waits for a thread to finish then creates a thread
    * to take the place of the one that has finished.
    */

    while (numThreads > 0)
    {
        /*
        * This waits for a thread in the current batch of threads to finish.
        * Then it creates a new thread to join the batch.
        */
        for (int j = 0; j < numConcurrent; j++)
        {
            if (numThreads < 1)
            {
                break;
            }
            if (pthread_join(pid[j], &returnValues[j]) == 0)
            {
                // printf("Creating thread index %d\n", numThreads--);
                pthread_create(&pid[j], NULL, hard_work, (void *)&workRate);
                numThreads--;
            }
        }
    }

    clock_gettime(CLOCK_REALTIME, &time2);

    //printf("Time elapsed for threads is %ld nanoseconds\n", diff(time1, time2).tv_nsec);
}

/*
 * This function implements the process creation and perfomance testing for this program
 */

static void runProcesses(int numProcesses, int numConcurrent, int workRate)
{
    struct timespec time1, time2;
    clock_gettime(CLOCK_REALTIME, &time1);

    /*
     * This creates the first batch of numConcurrent processes. 
     */
    for (int i = 0; i < numConcurrent; i++)
    {
        int pid = fork();

        if (pid == 0)
        {
            // printf("Forking into index %d\n", numProcesses);
            hard_work((void *)&workRate);
            exit(0);
        }
        numProcesses--;
    }
    /*
     * This waits for a process to finish and creates a new process
     * to take its place. It will keep running till we meet the 
     * required number of processes.
     */
    for (int j = numProcesses; j > 0; j--)
    {
        wait(NULL);
        numProcesses--;
        // printf("Forking into index %d\n", j);
        int pid = fork();
        if (pid == 0)
        {
            hard_work((void *)&workRate);
            exit(0);
        }
    }

    clock_gettime(CLOCK_REALTIME, &time2);

    printf("Time elapsed for processes is %ld nanoseconds\n", diff(time1, time2).tv_nsec);
}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
