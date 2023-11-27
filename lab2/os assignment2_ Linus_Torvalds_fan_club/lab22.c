#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

char* activeReadersName = "/2a2c3tiveReaid";
char* valueName = "/value232";
char* sem_rw_name = "semrw";
char* sem_r_name = "semr";
char* sem_initialized_name = "semini";


int main() {

	sem_t* sem_rw = sem_open(sem_rw_name, O_CREAT, 0600, 0);
	sem_t* sem_r = sem_open(sem_r_name, O_CREAT, 0600, 0);
	sem_t* sem_initialized = sem_open(sem_initialized_name, O_CREAT, 0600, 0);

	pid_t pid = fork();
	pid_t pid2 = fork();

	if(pid == 0){
		
		sem_wait(sem_initialized);
		sem_post(sem_initialized);

	        int fd = shm_open(valueName, O_RDONLY, 0666);

		int* val = (int*)mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, fd, 0);

		int fd2 = shm_open(activeReadersName, O_RDWR, 0666);

		int* activeReaders = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);

		while(1){
			sem_wait(sem_r);
		
			if(*activeReaders <= 0){
				sem_wait(sem_rw);
				printf("The first reader acquires the lock\n");
			}
			(*activeReaders)++;
			sem_post(sem_r);
			
			printf("Reader (%d) reads the value %d\n", getpid(), *val);
			int done = 0;
			if(*val == INT_MAX)
				done = 1;

			sleep(1);
			sem_wait(sem_r);
			(*activeReaders)--;
			if(*activeReaders <= 0){
				sem_post(sem_rw);
				printf("The last reader releases the lock. \n");
			}
			sem_post(sem_r);

			if(done == 1){
				shm_unlink(activeReadersName);
				shm_unlink(valueName);
				exit(1);
			}

			sleep(1);
		
		}


	}
	else if(pid2 != 0){
	
	int fd = shm_open(valueName, O_RDWR | O_CREAT, 0666);

	ftruncate(fd, sizeof(int));

	int* val = (int*)mmap(NULL, sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

	int fd2 = shm_open(activeReadersName, O_RDWR | O_CREAT, 0666);

	ftruncate(fd2, sizeof(int));

	int* activeReaders = (int*)mmap(NULL, sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED, fd2, 0);

	*activeReaders = 0;

	*val = 0;

	sem_init(sem_rw, 1, 1);
	sem_init(sem_r, 1, 1);
	sem_init(sem_initialized, 1, 1);
	

	while(1){
		sem_wait(sem_rw);
		printf("The writer acquires the lock.\n");
		(*val)++;
		printf("Writer (%d) writes the value %d\n", getpid(), *val);

		sleep(1);
		printf("The writer releases the lock.\n");

		int done = 0;
		if(*val == INT_MAX)
			done = 1;

		sem_post(sem_rw);

		if(done == 1){
			wait(NULL);
			wait(NULL);
			shm_unlink(valueName);
			shm_unlink(activeReadersName);
			sem_unlink(sem_rw_name);
			sem_unlink(sem_r_name);
			sem_unlink(sem_initialized_name);

			return 0;	

		}

		sleep(1);

	}


	}

	return 0;
}
