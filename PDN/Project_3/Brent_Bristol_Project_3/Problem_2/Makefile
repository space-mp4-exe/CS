in=../../test_data/DNA_files/GRCh38_reduced_rna.fna # starter input file name, can set like "make run_starter in=other.fna"
LargeIn=../../test_data/DNA_files/GRCh38_latest_rna.fna # starter input file name, can set like "make run_starter in=other.fna"
gcc =/opt/homebrew/opt/llvm/bin/clang

all: make_starter

# duplicate this for other files
make_starter: compute_average_TF_Exp1_critical.c
	gcc -fopenmp -g -Wall -o compute_average_TF_Exp1_critical compute_average_TF_Exp1_critical.c -lm -std=c99
	gcc -fopenmp -g -Wall -o compute_average_TF_Exp1_atomic compute_average_TF_Exp1_atomic.c -lm -std=c99
	gcc -fopenmp -g -Wall -o compute_average_TF_Exp1_locks compute_average_TF_Exp1_locks.c -lm -std=c99
	gcc -fopenmp -g -Wall -o compute_average_TF_Exp2_schedule compute_average_TF_Exp2_schedule.c -lm -std=c99
	

clean:
	$(RM) *.csv
	$(RM) -r *.dSYM
	$(RM) compute_average_TF_Exp1_critical
	$(RM) compute_average_TF_Exp1_atomic
	$(RM) compute_average_TF_Exp1_locks
	$(RM) compute_average_TF_Exp2_schedule


# Below are commands to help you run your program easily.
# You will need to create more entries for your different files, such as for critical and locks.
run: run_starter

# duplicate this for other files
run_starter:
 	./compute_average_TF_Exp1_critical $(in) OUTPUT_critical_1th.csv TIME_critical_1th.csv 1
 	./compute_average_TF_Exp1_critical $(in) OUTPUT_critical_2th.csv TIME_critical_2th.csv 2
 	./compute_average_TF_Exp1_critical $(in) OUTPUT_critical_4th.csv TIME_critical_4th.csv 4
 	./compute_average_TF_Exp1_critical $(in) OUTPUT_critical_8th.csv TIME_critical_8th.csv 8
	./compute_average_TF_Exp1_atomic $(in) OUTPUT_atomic_1th.csv TIME_atomic_1th.csv 1
 	./compute_average_TF_Exp1_atomic $(in) OUTPUT_atomic_2th.csv TIME_atomic_2th.csv 2
 	./compute_average_TF_Exp1_atomic $(in) OUTPUT_atomic_4th.csv TIME_atomic_4th.csv 4
 	./compute_average_TF_Exp1_atomic $(in) OUTPUT_atomic_8th.csv TIME_atomic_8th.csv 8
 	./compute_average_TF_Exp1_locks $(in) OUTPUT_locks_1th.csv TIME_locks_1th.csv 1
 	./compute_average_TF_Exp1_locks $(in) OUTPUT_locks_2th.csv TIME_locks_2th.csv 2
	./compute_average_TF_Exp1_locks $(in) OUTPUT_locks_4th.csv TIME_locks_4th.csv 4
 	./compute_average_TF_Exp1_locks $(in) OUTPUT_locks_8th.csv TIME_locks_8th.csv 8
	./compute_average_TF_Exp2_schedule $(in) OUTPUT_schedule_1th.csv TIME_schedule_1th.csv 1
	./compute_average_TF_Exp2_schedule $(in) OUTPUT_schedule_2th.csv TIME_schedule_2th.csv 2
	./compute_average_TF_Exp2_schedule $(in) OUTPUT_schedule_4th.csv TIME_schedule_4th.csv 4
	./compute_average_TF_Exp2_schedule $(in) OUTPUT_schedule_8th.csv TIME_schedule_8th.csv 8

run_large:
	./compute_average_TF_Exp1_critical $(LargeIn) OUTPUT_critical_large_4th.csv TIME_critical_large_4th.csv 4
	./compute_average_TF_Exp1_critical $(LargeIn) OUTPUT_critical_large_8th.csv TIME_critical_large_8th.csv 8
	./compute_average_TF_Exp1_atomic $(LargeIn) OUTPUT_atomic_large_4th.csv TIME_atomic_large_4th.csv 4
	./compute_average_TF_Exp1_atomic $(LargeIn) OUTPUT_atomic_large_8th.csv TIME_atomic_large_8th.csv 8
	./compute_average_TF_Exp1_locks $(LargeIn) OUTPUT_locks_large_4th.csv TIME_locks_large_4th.csv 4
	./compute_average_TF_Exp1_locks $(LargeIn) OUTPUT_locks_large_8th.csv TIME_locks_large_8th.csv 8