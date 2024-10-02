#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int total = 0; //variable for processes to add to
void *runner(void *param);//threads for processes to run on

int main(int argc, char *argv[]){
	pthread_t tid; //thread identifier
	pthread_attr_t attr; //thread attributes

	pthread_attr_init(&attr);//get default attributes
	//Make the 4 children
	for(int i = 0; i < 5; i++){
		pthread_create(&tid, &attr, runner, i);//put children on own thread
	}
	pthread_join(tid,NULL);
}

void *runner(void *param) {

	pthread_exit(0);
}
