//PRODUCER CODE

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

int main(){
    int shmid;
    int *shared_int;
    key_t key = 1337;

    sem_t *semaphore1 = sem_open("/sem1",O_CREAT,0664,1);
    sem_t *semaphore2 = sem_open("/sem2",O_CREAT,0664,2);
    shmid = shmget(key,sizeof(int), 0666|IPC_CREAT);
    shared_int = (int*) shmat(shmid,(void*)0,0);


    for(int i = 0; i < 15; i++){
        
        sem_wait(semaphore1);
        printf("Writer aquires the lock \n");
        
        sleep(5);

        *shared_int +=1;
        printf("%d",*shared_int);
        
        sem_post(semaphore2);
        sem_post(semaphore2);
    }

    
    
    shmdt(shared_int);

    sem_close(semaphore1);
    sem_unlink("/sem1");
    sem_unlink("/sem2");
}