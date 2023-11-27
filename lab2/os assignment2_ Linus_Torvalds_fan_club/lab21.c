#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int buffer = 0;
pthread_mutex_t bufferLock;

void* incrementBuffer(){
	int total = 0;
	while(1){
	
		pthread_mutex_lock(&bufferLock);

		if(buffer < 15){
			printf("TID: %ld, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
			total++;
			buffer++;
		}else{
			printf("TID: %ld worked on the buffer %d times\n", pthread_self(), total);
			pthread_mutex_unlock(&bufferLock);
			return NULL;
		}

		pthread_mutex_unlock(&bufferLock);

	}

	
}


int main(){
	pthread_t t1, t2, t3;

	pthread_mutex_init(&bufferLock, NULL);

	pthread_create(&t1, NULL, &incrementBuffer, NULL);
	pthread_create(&t2, NULL, &incrementBuffer, NULL);
	pthread_create(&t3, NULL, &incrementBuffer, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	pthread_mutex_destroy(&bufferLock);

	printf("Total buffer accesses: %d\n", buffer);

	return 0;
}
