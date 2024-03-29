#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MAX_PROCESSORS 4

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
	int numConcurrent;
	int numProcesses;
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

	pthread_t pid[numConcurrent];
	void *returnValues[numConcurrent];
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
