//Brent Bristol bris0040
#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 15

void reader();
void printer();

//struct for elements in the buffer
typedef struct{
	char character;
}element;

element buffer[BUFFER_SIZE];
int inFlag = 0;
int outFlag = 0;

char* name = "Buffer";//semaphore name

int main(){
	//create named semaphore
	sem_t* semBuf = sem_open(name, O_EXCL | O_CREAT | O_RDWR, 0666);

	pthread_t tid1[1]; /* process id for thread 1 */
	pthread_t tid2[1]; /* process id for thread 2 */
	pthread_attr_t attr[1]; /* attribute pointer array */

	fflush(stdout);
	/* Required to schedule thread independently.*/
	pthread_attr_init(&attr[0]);
	pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);
	/* end to schedule thread independently */
	/* Create the threads */
	pthread_create(&tid1[0], &attr[0],(void *) reader, NULL);//create producer
	pthread_create(&tid2[0], &attr[0],(void *) printer, NULL);//create consumer


	/* Wait for the threads to finish */
	pthread_join(tid1[0], NULL);
	pthread_join(tid2[0], NULL);
	//Terminate threads
	pthread_exit(NULL);
	
	//deallocate semaphore
	sem_destroy(semBuf);

	//unlink shared memory
	sem_unlink(name);

	return 0;
}

void reader(){
	char newChar;
	FILE* fp;
	fp = fopen("mytest.dat", "r");
	element next_produced;

	sem_t* semBuf = sem_open(name, 0);
	while (fscanf(fp,"%c",&newChar) != EOF) {
		// Generate new item
		next_produced.character = newChar;

		// Wait for there to be space in the buffer
		while (((inFlag + 1) % BUFFER_SIZE) == outFlag); /* do nothing */
		// Place item in the buffer
		sem_wait(semBuf);
		buffer[inFlag] = next_produced;
		sem_post(semBuf);
		inFlag = (inFlag + 1) % BUFFER_SIZE;
	}
	//add end of file character to buffer
	next_produced.character = '*';
	sem_wait(semBuf);
	buffer[inFlag] = next_produced;
	sem_post(semBuf);

	fclose(fp);
}

void printer(){
	element next_consumed;
	sem_t* semBuf = sem_open(name, 0);
	sem_wait(semBuf);//shouldn't run before there is something in the buffer

	while (buffer[outFlag].character != '*') {
		// Wait for item to be available
		while (inFlag == outFlag); /* do nothing */

		// Get the next item
		sem_wait(semBuf);
		next_consumed = buffer[outFlag];
		sem_post(semBuf);
		printf("%c",next_consumed.character);
		fflush(stdout);
		outFlag = (outFlag + 1) % BUFFER_SIZE;
		sleep(1);

		//print next character in file
	}
	//printf("\n");
}
