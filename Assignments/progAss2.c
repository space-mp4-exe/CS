//Brent Bristol 4x4: bris0040 username: cs0015
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct { //struct for shared memory
	sem_t* sem;
	int* total;
} sharedVar;

void incTotal(int count);//increment total variable
sharedVar* sharedMem;//shared memory struct
//sem_t sem;
//int* total;//shared variable


int main(int argc, char *argv[]){
	//set up shared memory
	int shmID, semID;//id of shared memory segment
	char* shmAddr;//address of shared memory segment
	struct shmid_ds shm_desc;
	sharedMem = (sharedVar*) malloc(sizeof(sharedVar));
	int zero = 0;
	sharedMem->total = &zero;

	//allocate shared memory segment
	shmID = shmget(100, 2048, IPC_CREAT | IPC_EXCL | 0600);
	if(shmID == -1){//operation failed
		shmID = shmget(100, 2048, IPC_CREAT | 0600);
		shmctl(shmID, IPC_RMID, &shm_desc);
		perror("main: shmget: ");
		exit(1);
	}

	//attach memory segment 
	shmAddr = shmat(shmID, NULL, 0);
	if(!shmAddr){//operation failed
		perror("main: shmat: ");
		exit(1);
	}

	sharedMem = (sharedVar*) shmAddr;//set struct to shared memory location
	
	
	//create semaphore
	char* name = "Semaphore";
	int fd;
	fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("main: shm_open: ");
		exit(1);
	}
	ftruncate(fd, sizeof(sem_t));
	sharedMem->sem = (sem_t*) mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	sem_init(sharedMem->sem, 1, 1);//initialize semaphore

	pid_t pid1, pid2, pid3, pid4;//id's of child processes

	//run each of the children
	if((pid1 = fork()) == 0){
		incTotal(100000);
		exit(0);
	}
	/*
	else if((pid2 = fork()) == 0){
		//sleep(1);
		incTotal(200000);
		exit(0);
	}
	else if((pid3 = fork()) == 0){
		//sleep(2);
		incTotal(300000);
		exit(0);
	}
	else if((pid4 = fork()) == 0){
		//sleep(3);
		incTotal(500000);
		exit(0);
	}
	*/

	//wait for the children to finish running 
	wait(NULL);
	printf("total value: %d\n", *sharedMem->total);
	/*
	printf("child with ID:%d just exited\n", pid1);
	wait(NULL);
	//printf("total value: %d\n", *sharedMem->total);
	printf("child with ID:%d just exited\n", pid2);
	wait(NULL);
	//printf("total value: %d\n", *sharedMem->total);
	printf("child with ID:%d just exited\n", pid3);
	wait(NULL);
	//printf("total value: %d\n", *sharedMem->total);
	printf("child with ID:%d just exited\n", pid4);
	*/

	//deallocate semaphore
	sem_destroy(sharedMem->sem);

	//detach shared memory from address space
	if(shmdt(shmAddr) == -1){
		perror("main: shmdt: ");
	}

	//deallocate the shared memory segment
	if(shmctl(shmID, IPC_RMID, &shm_desc) == -1){
		perror("main: shmctl: ");
	}

	//end of program statement
	printf("End of Program\n");
	exit(0);
}

void incTotal(int count){
	/*
	sem_wait(sharedMem->sem);
	for(int i = 0; i < count; i++){
		(*(sharedMem->total))++;
	}
	printf("total value: %d\n", *sharedMem->total);
	sem_post(sharedMem->sem);
	*/
}

