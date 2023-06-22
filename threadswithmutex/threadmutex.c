#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
pthread_mutex_t pthreadLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pReqWait = PTHREAD_MUTEX_INITIALIZER;
void *xThreadFun(int *argx)
{
	pthread_mutex_lock(&pthreadLock);
	struct timespec timeToWait;
    clock_gettime(CLOCK_REALTIME, &timeToWait);
    timeToWait.tv_sec += 10; //10sec
	for(int i=0; i<argx; i++){
			printf("Tik Tik %d for X thread\n",i);
			pthread_cond_timedwait(&pReqWait, &pthreadLock, &timeToWait);
			sleep(1);}
    pthread_mutex_unlock(&pthreadLock);
	return NULL;
}

void *yThreadFun(int *argy)
{
     
	 for(int i=0; i<argy; i++){
             printf("Tik Tik %d for Y thread \n",i);
             sleep(1);}
	 pthread_cond_signal(&pReqWait);
     return NULL;
}

int main()
{
	pthread_t thread_x;
	pthread_t thread_y;
	int numx, numy;
	printf("Enter counter limit for thread X: \n");
	scanf("%d",&numx);
	printf("Enter counter limit for thread Y: \n");
	scanf("%d",&numy);
	pthread_create(&thread_x, NULL, xThreadFun, numx);
	pthread_create(&thread_y, NULL, yThreadFun, numy);
	pthread_join(thread_x, NULL);
	printf("After Thread X\n");
	pthread_join(thread_y, NULL);
	printf("After Thread Y\n");
	exit(0);
}

