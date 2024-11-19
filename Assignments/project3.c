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
#define BUFFER_SIZE 15

void writer();
void reader();

typedef struct{
	char character;
}element;
element buffer[BUFFER_SIZE];
int inFlag = 0;
int outFlag = 0;

int main(){
	pthread_t tid1[1]; /* process id for thread 1 */
	pthread_t tid2[1]; /* process id for thread 2 */
	pthread_attr_t attr[1]; /* attribute pointer array */

	fflush(stdout);
	/* Required to schedule thread independently.*/
	pthread_attr_init(&attr[0]);
	pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);
	/* end to schedule thread independently */
	/* Create the threads */
	pthread_create(&tid1[0], &attr[0],(void *) writer, NULL);//create producer
	pthread_create(&tid2[0], &attr[0],(void *) reader, NULL);//create consumer


	/* Wait for the threads to finish */
	pthread_join(tid1[0], NULL);
	pthread_join(tid2[0], NULL);
	//Terminate threads
	pthread_exit(NULL);

	return 0;
}

void writer(){
	element next_produced;
	while (true) {
		// Generate new item
		next_produced.character = 'h';
		// Wait for there to be space in the buffer
		while (((inFlag + 1) % BUFFER_SIZE) == outFlag); /* do nothing */
		// Place item in the buffer
		buffer[inFlag] = next_produced;
		inFlag = (inFlag + 1) % BUFFER_SIZE;
	}
}

void reader(){
	printf("nuthin\n");
}
