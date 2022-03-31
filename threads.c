#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// Option-Shift-F to Reindent code in VSCode

int engaged = 1;
int sleepTime = 0;
useconds_t microSeconds = 0;
int threadCount = 0;
void *threadFunction(void *arg)
{
	int number = *(int *)arg;
	int count = 0;
	while (engaged)
	{
		count++;
		usleep(microSeconds);
	}
	printf("thread %d count %d\n", number, count);
	*(int *)arg = count; // return count
	return NULL;
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf("Usage: ./threads THREADCOUNT SECONDS SLEEPTIME\n");
		exit(1);
	}

	threadCount = atoi(argv[1]);
	microSeconds = atoi(argv[2]);
	sleepTime = atoi(argv[3]);

	pthread_t threads[threadCount];
	int rc;
	int index[threadCount]; // has thread number going in,
							// count when thread ends
	for (int i = 0; i < threadCount; i++)
	{
		index[i] = i;
		rc = pthread_create(&threads[i], NULL, &threadFunction, &index[i]);
		if (rc)
		{
			char msg[1024];
			sprintf(msg, "Error creating thread %d\n", i);
			perror(msg);
			exit(1);
		}
	}
	sleep(sleepTime);
	engaged = 0;
	int maxCount = 0;
	int minCount = INT_MAX;
	int aveCount = 0;
	float percent = 0.0;
	for (int i = 0; i < threadCount; i++)
	{
		int threadRC = 0;
		void *rcPtr = (void *)&threadRC;
		pthread_join(threads[i], &rcPtr);
	}
	for (int i = 0; i < threadCount; i++)
	{
		if (index[i] > maxCount)
		{
			maxCount = index[i];
		}
		if (index[i] < minCount)
		{
			minCount = index[i];
		}
		aveCount += index[i]; // add count to bucket so we can average
	}
	aveCount = aveCount / threadCount; // calculate average count
	percent = (maxCount - minCount) * 100.0 / aveCount;
	printf("\n\nLowest Count:%d", minCount);
	printf("\nHighest Count:%d", maxCount);
	printf("\nAverage  Count:%d", aveCount);
	printf("\nPercentage away from average:%.2f\n", percent);
	// wRange = (maxCount - minCount) / aveCount * 100;
	// printf("\nPercent Waiting Count Range:%.2f", wRange);

	return 0;
}
