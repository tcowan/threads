#include <pthreads.h>
#include <stdio.h>
#include <stdlib.h>

void * countFunction(void *arg) {
	int number = *(int *)arg;
	while (engaged) {
		usleep(20);
		count++;
	}
	printf("thread %d count %d\n");
	return NULL;
}

int engaged = 1;

int main(int argc, char ** argv) {
	if (argc != 3) {
		printf("Usage: %s

