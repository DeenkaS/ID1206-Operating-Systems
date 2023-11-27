#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int buffer = 0;
pthread_mutex_t lock;

int threadWork[3];
pthread_t threadId[3];

void *Thread_function(void *arg)
{

    pthread_mutex_lock(&lock);
    int threadNumber = *((int*) arg);

    if(threadId[threadNumber] == NULL);
    {
        threadId[threadNumber] = pthread_self();
    }

    printf("TID: %lu PID: %d Buffer: %d\n", threadId[threadNumber], getpid(), buffer);
    buffer++;
    threadWork[threadNumber] = threadWork[threadNumber] + 1;
    //printf("Thread %d has worked %d times ", threadNumber, threadWork[threadNumber]);
    pthread_mutex_unlock(&lock);
    return NULL;
    //mutex unlock
}
int main(void){ 
    threadWork[0] = 0;
    threadWork[1] = 0;
    threadWork[2] = 0;


    pthread_mutex_init(&lock, NULL);    
    
    pthread_t thread1, thread2, thread3;
    int first = 0;
    int second = 1;
    int third = 2;
    while(buffer < 15)
    {
        //creating threads
        pthread_create(&thread1, NULL, Thread_function, (void *) &first); 
        pthread_create(&thread2, NULL, Thread_function, (void *) &second); // busy waiting
        pthread_create(&thread3, NULL, Thread_function, (void *) &third); // busy waiting

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        pthread_join(thread3, NULL);
    }

    // ending threads
    for(int i = 0; i < 3; i++)
    {
    printf("TID %lu worked on the buffer %d\n", threadId[i], threadWork[i]);
    }
    printf("Total work %d", buffer);
    //destroying lock
    pthread_mutex_destroy(&lock);
    return EXIT_SUCCESS;

}