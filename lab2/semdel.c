#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    
    int shmid;
    int *shared_int;
    key_t key = 1337;

    sem_unlink("/SharedMemSem");
    sem_unlink("/sem1");
    sem_unlink("/sem2");

    shmid = shmget(key,sizeof(int),0666);
    shared_int = (int*) shmat(shmid,(void*)0,0);
    shmdt(shared_int);                  //detach shared in
    shmctl(shmid, IPC_RMID, NULL);      //remove shared int
}