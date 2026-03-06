in=../../test_data/DNA_files/GRCh38_reduced_rna.fna # starter input file name, can set like "make run_starter in=other.fna"
gcc=/opt/homebrew/opt/llvm/bin/clang

all: make_starter

# duplicate this for other files
make_starter: 
	gcc -fopenmp -g -Wall -o compute_median_TF_Exp1_baseline compute_median_TF_Exp1_baseline.c -lm -std=c99
	gcc -fopenmp -g -Wall -o compute_median_TF_Exp2_mapreduce compute_median_TF_Exp2_mapreduce.c -lm -std=c99

clean:
	$(RM) *.csv
	$(RM) -r *.dSYM
	$(RM) compute_median_TF_Exp1_baseline
	$(RM) compute_median_TF_Exp2_mapreduce


# Below are commands to help you run your program easily.
# You will need to create more entries for your different files, such as for critical and locks.
run: run_starter

# duplicate this for other files
run_starter:
	./compute_median_TF_Exp1_baseline $(in) OUTPUT_baseline_1th.csv TIME_baseline_1th.csv 1
	./compute_median_TF_Exp1_baseline $(in) OUTPUT_baseline_2th.csv TIME_baseline_2th.csv 2
	./compute_median_TF_Exp1_baseline $(in) OUTPUT_baseline_4th.csv TIME_baseline_4th.csv 4
	./compute_median_TF_Exp1_baseline $(in) OUTPUT_baseline_8th.csv TIME_baseline_8th.csv 8
	./compute_median_TF_Exp2_mapreduce $(in) OUTPUT_mapreduce_1th.csv TIME_mapreduce_1th.csv 1
	./compute_median_TF_Exp2_mapreduce $(in) OUTPUT_mapreduce_2th.csv TIME_mapreduce_2th.csv 2
	./compute_median_TF_Exp2_mapreduce $(in) OUTPUT_mapreduce_4th.csv TIME_mapreduce_4th.csv 4
	./compute_median_TF_Exp2_mapreduce $(in) OUTPUT_mapreduce_8th.csv TIME_mapreduce_8th.csv 8