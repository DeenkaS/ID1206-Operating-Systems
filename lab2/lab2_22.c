
//CONSUMERS CODE


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>


sem_t *semaphore1, *semaphore2;
int smhid;
int *shared_int;

void* consumer1(){
    pid_t pid = getpid();
    
    while(1){
        sem_wait(semaphore2);
        printf("the reader (%d) reads value %d \n" , pid , *shared_int);
        

        if(*shared_int >= 15){
            break;
        }
    }

}

void* consumer2(){
    pid_t pid = getpid();
    
    while(1){
        sem_wait(semaphore2);
        printf("the reader (%d) reads value %d \n" , pid , *shared_int);
        

        if(*shared_int >= 15){
            break;
        }
        sem_post(semaphore1);
    }

}


int main(){
    semaphore1 = sem_open("/sem1",0); //opens the semaphore
    semaphore2 = sem_open("/sem2",0); //opens the semaphore
    pthread_t thread1, thread2; //

    
    key_t key = 1337;
    smhid = shmget(key,sizeof(int),0666);
    shared_int = (int*) shmat(smhid,(void*)0,0);
    
    /*printf("%d\n",*shared_int);
    *shared_int += 17;
    printf("%d\n",*shared_int);*/
    

    pthread_create(&thread1,NULL,consumer1,0);
    pthread_create(&thread2,NULL,consumer2,0); 

    pthread_join(thread1,NULL);         //close thread1
    pthread_join(thread2,NULL);         //close thread2

    shmdt(shared_int);                  //detach shared in
    shmctl(smhid, IPC_RMID, NULL);      //remove shared int
    sem_unlink("/sem1");
    sem_unlink("/sem2");


}