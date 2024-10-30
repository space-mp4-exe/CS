//Brent Bristol 4x4: bris0040 username: cs0015
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct { //struct for shared memory
	sem_t sem;
	int total;
} sharedVar;

void incTotal(int count);//increment total variable
sharedVar* sharedMem;//shared memory struct


int main(int argc, char *argv[]){
	//set up shared memory
	int shmID, semID;//id of shared memory segment
	char* shmAddr;//address of shared memory segment
	
	//create semaphore
	char* name = "Semaphore";
	int fd;
	fd = shm_open(name, O_EXCL | O_CREAT | O_RDWR, 0666);
	if(fd == -1){//error message
		fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		shm_unlink(name);
		perror("main: shm_open: ");
		exit(1);
	}
	ftruncate(fd, sizeof(sharedVar));
	//map struct to shared memory
	sharedMem = mmap(NULL, sizeof(sharedVar), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	sem_init(&sharedMem->sem, 1, 1);//initialize semaphore

	pid_t pid1, pid2, pid3, pid4;//id's of child processes
	

	//run each of the children
	if((pid1 = fork()) == 0){
		incTotal(100000);
		exit(0);
	}
	else if((pid2 = fork()) == 0){
		incTotal(200000);
		exit(0);
	}
	else if((pid3 = fork()) == 0){
		incTotal(300000);
		exit(0);
	}
	else if((pid4 = fork()) == 0){
		incTotal(500000);
		exit(0);
	}

	//wait for the children to finish running 
	wait(NULL);
	printf("child with ID:%d just exited\n", pid1);
	wait(NULL);
	printf("child with ID:%d just exited\n", pid2);
	wait(NULL);
	printf("child with ID:%d just exited\n", pid3);
	wait(NULL);
	printf("child with ID:%d just exited\n", pid4);

	//deallocate semaphore
	sem_destroy(&sharedMem->sem);

	//unlink shared memory
	shm_unlink(name);

	//end of program statement
	printf("End of Program\n");
	exit(0);
}

void incTotal(int count){
	for(int i = 0; i < count; i++){
		sem_wait(&sharedMem->sem);//request for semaphore access
		//critical section
		sharedMem->total++;
		sem_post(&sharedMem->sem);//release semaphore
	}
	sem_wait(&sharedMem->sem);
	//critical section for printing result
	printf("total value: %d\n", sharedMem->total);
	sem_post(&sharedMem->sem);
}

