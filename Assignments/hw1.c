#include <stdio.h>
#include <stdlib.h>

int multiply(int a, int b){
	return a * b;
}

int main(){
	//variables
	int* arr1;
	int* arr2;
	int size;
	
	//get user input
	printf("Input array size:");
	scanf("%d", &size);
	
	//make dynamic arrays
	arr1 = (int*) malloc(size * sizeof(int));
	arr2 = (int*) malloc(size * sizeof(int));

	printf("%p\n",arr1);
	printf("%zu\n",sizeof(arr1));

	//set array contents
	printf("Input content of arr1:\n");
	for(int i = 0; i < size; i++){
		printf("Enter value of arr1[%d]:",i);
		scanf("%d", &arr1[i]);
	}

	printf("Input content of arr2:\n");
	for(int i = 0; i < size; i++){
		printf("Enter value of arr2[%d]:",i);
		scanf("%d", &arr2[i]);
	}

	//make file
	FILE *file;
	file = fopen("hw1_output.txt", "w");
	
	//write to file
	printf("writting to file\n");
	for(int i = 0; i < size; i++){
		int result = multiply(arr1[i], arr2[i]);
		printf("arr[%d] * arr2[%d] = %d\n", i, i, result);
		if(result % 2 == 0){
			fprintf(file, "%d is an even number\n", result);

		}
		else{
			fprintf(file, "%d is an odd  number\n", result);
		}
	}

	//reopen the file in read mode
	fclose(file);
	file = fopen("hw1_output.txt", "r");

	//print file contents
	printf("reading file\n");
	for(char c = getc(file); c != EOF; c = getc(file)){
		printf("%c",c);
	}

	//deallocating memory
	fclose(file);
	free(arr1);
	free(arr2);
	return 0;
}
