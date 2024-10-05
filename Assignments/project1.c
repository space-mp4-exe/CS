//Brent Bristol 4x4: bris0040 username: cs0015
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int* total;//shared variable
void incTotal(int count);//increment total variable

int main(int argc, char *argv[]){
	//set up shared memory
	int shmID;//id of shared memory segment
	char* shmAddr;//address of shared memory segment
	struct shmid_ds shm_desc;

	//allocate shared memory segment
	shmID = shmget(100, 2048, IPC_CREAT | IPC_EXCL | 0600);
	if(shmID == -1){//operation failed
		perror("main: shmget: ");
		exit(1);
	}

	//attach memory segment 
	shmAddr = shmat(shmID, NULL, 0);
	if(!shmAddr){//operation failed
		perror("main: shmat: ");
		exit(1);
	}

	total = (int*) shmAddr;//set total to shared memory location

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
	printf("total value: %d\n", *total);
	printf("child with ID:%d just exited\n", pid1);
	wait(NULL);
	printf("total value: %d\n", *total);
	printf("child with ID:%d just exited\n", pid2);
	wait(NULL);
	printf("total value: %d\n", *total);
	printf("child with ID:%d just exited\n", pid3);
	wait(NULL);
	printf("total value: %d\n", *total);
	printf("child with ID:%d just exited\n", pid4);

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
	for(int i = 0; *total < count; i++){
		(*total)++;
	}
}

