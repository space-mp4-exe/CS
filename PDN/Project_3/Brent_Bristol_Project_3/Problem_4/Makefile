all: remind_student

remind_student:
	@echo "Please alter the Makefile before running!"

# alter this
make_starter: kmeans_parallel_starter.c
	gcc -fopenmp -g -Wall -o kmeans_parallel_starter kmeans_parallel_starter.c -lm -std=c99
	

clean:
	$(RM) kmeans_parallel_starter


# Below are commands to help you run your program easily.
# You can alter them to run multiple things at once.
run: run_starter

# alter this
run_starter:
	./kmeans_parallel_starter 1000000 points_1M.csv 16 initial_centroids.csv output.csv time.csv 1