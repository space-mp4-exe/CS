#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int* total;
void *runner(void *param);//threads for processes to run on

int main(int argc, char *argv[]){
	//set up shared memory
	int shmID;//id of shared memory segment
	char* shmAddr;//address of shared memory segment
	struct shmid_ds shm_desc;
	
	//allocate shared memory segment
	shmID = shmget(100, 2048, IPC_CREAT | IPC_EXCL | 0600);
	if(shmID == -1){//operation failed
		//shmctl(shmID, IPC_RMID, &shm_desc);
		perror("main: shmget: ");
		exit(1);
	}

	//attach memory segment 
	shmAddr = shmat(shmID, NULL, 0);
	if(!shmAddr){//operation failed
		perror("main: shmat: ");
		exit(1);
	}

	total = (int*) shmAddr;
	*total = 0;

	//set up threads
	pthread_t tid1; //thread identifier
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;
	pthread_attr_t attr; //thread attributes
	pthread_attr_init(&attr);//get default attributes
	
	//make 4 children threads
	pthread_create(&tid1, &attr, runner, (int*) 1);
	pthread_create(&tid2, &attr, runner, (int*) 2);
	pthread_create(&tid3, &attr, runner, (int*) 3);
	pthread_create(&tid4, &attr, runner, (int*) 5);

	//wait for children to finish executing
	pthread_join(tid1,NULL);
	printf("total count: %d\n",*total);
	pthread_join(tid2,NULL);
	printf("total count: %d\n",*total);
	pthread_join(tid3,NULL);
	printf("total count: %d\n",*total);
	pthread_join(tid4,NULL);
	printf("total count: %d\n",*total);

	//detach shared memory from address space
	if(shmdt(shmAddr) == -1){
		perror("main: shmdt: ");
	}

	//deallocate the shared memory segment
	if(shmctl(shmID, IPC_RMID, &shm_desc) == -1){
		perror("main: shmctl: ");
	}
	exit(0);
}

void *runner(void *param) {
	int k = atoi(param);
	for(int i = 0; i < (k * 100000); i++){
		(*total)++;
	}

	pthread_exit(0);
}

