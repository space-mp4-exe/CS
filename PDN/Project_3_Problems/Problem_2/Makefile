in=in.fna # starter input file name, can set like "make run_starter in=other.fna"

all: make_starter

# duplicate this for other files
make_starter: compute_average_TF_Exp1_starter.c
	gcc -fopenmp -g -Wall -o compute_average_TF_Exp1_starter compute_average_TF_Exp1_starter.c -lm -std=c99
	

clean:
	$(RM) compute_average_TF_Exp1_starter


# Below are commands to help you run your program easily.
# You will need to create more entries for your different files, such as for critical and locks.
run: run_starter

# duplicate this for other files
run_starter:
	./compute_average_TF_Exp1_starter $(in) OUTPUT_starter_1th.csv TIME_starter_1th.csv 1
	./compute_average_TF_Exp1_starter $(in) OUTPUT_starter_2th.csv TIME_starter_2th.csv 2
	./compute_average_TF_Exp1_starter $(in) OUTPUT_starter_4th.csv TIME_starter_4th.csv 4
	./compute_average_TF_Exp1_starter $(in) OUTPUT_starter_8th.csv TIME_starter_8th.csv 8