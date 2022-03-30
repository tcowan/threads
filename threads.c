#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * threadFunction(void *arg) {
	int number = *(int *)arg;
	int count = 0;
	while (engaged) {
		count++;
		usleep(20);
	}
	printf("thread %d count %d\n", number, count);
	return NULL;
}

int engaged = 1;
int sleepTime = 0;
int seconds = 0;
int threadCount = 0;

int main(int argc, char ** argv) {
	if (argc != 4) {
		printf("Usage: ./threads THREADCOUNT SECONDS SLEEPTIME\n");
		exit(1) 
	}

	threadCount = atoi(argv[1]);
	seconds = atoi(argv[2]);
	sleepTime = atoi(argv[3]);

	int indexes[count];
	int threads[count];
	int rc;

	for (int i = 0; i < count; i++) {
		rc = pthread_create(&threads[i], NULL, &threadFunction, &i);
		if (rc) {
			char msg[1024];
			sprintf(msg, "Error creating thread %d", i);
			perror(msg);
			exit(1);
		}
		sleep(sleepTime);
		engaged = 0;
		sleep(3);
		int *p = &rc;
		for(int i = 0; i < threadCount; i++) {
			pthread_join(threads[i], &p);
		}
	}

