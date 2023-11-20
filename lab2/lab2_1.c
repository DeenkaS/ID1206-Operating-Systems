//KOMPILERA: gcc -o aa lab2_1.c -pthread
//KÖR: ./aa



#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

int BUFFER;
pthread_t thread1, thread2, thread3;
pthread_mutex_t buffer_mutex;

int process1runs;
int process2runs;
int process3runs;

void *threads()
{
    while (1)
    {

        pid_t pid = getpid();
        pid_t tid = syscall(SYS_gettid);
        pthread_t current_thread_id = pthread_self();

        pthread_mutex_lock(&buffer_mutex);

        if (BUFFER >= 15)
        {

            if (pthread_equal(current_thread_id, thread1))
            {
                printf("TID %d worked on the buffer %d times \n", tid, process1runs);
            }
            else if (pthread_equal(current_thread_id, thread2))
            {
                printf("TID %d worked on the buffer %d times \n", tid, process3runs);
            }
            else if (pthread_equal(current_thread_id, thread3))
            {
                printf("TID %d worked on the buffer %d times \n", tid, process2runs);
            }
            pthread_mutex_unlock(&buffer_mutex);
            break;
        }

        if (pthread_equal(current_thread_id, thread1))
        {
            process1runs++;
        }
        else if (pthread_equal(current_thread_id, thread2))
        {
            process2runs++;
        }
        else if (pthread_equal(current_thread_id, thread3))
        {
            process3runs++;
        }
        else
        {
            printf("ERROR WITH THREAD PROCESS NUMBERS \n");
        }

        printf("TID: %d, PID: %d, Buffer: %d \n", tid, pid, BUFFER);
        BUFFER++;

        pthread_mutex_unlock(&buffer_mutex);
    }
}

int main()
{

    BUFFER = 0;

    process1runs = 0;
    process2runs = 0;
    process3runs = 0;

    pthread_create(&thread1, NULL, threads, NULL);
    pthread_create(&thread2, NULL, threads, NULL);
    pthread_create(&thread3, NULL, threads, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("total buffer accesses: %d\n", BUFFER);
}