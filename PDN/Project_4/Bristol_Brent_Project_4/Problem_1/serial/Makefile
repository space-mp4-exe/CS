
all: make_serial

# ------------------------------------------------------------------------------- #

# input file and size
FILE     = ../../Project_4_Tests/Problem_1_and_2/in_20k.csv
SIZE	 = 20000

# number of trials to run
TRIALS_A = 5000000
TRIALS_B = 10000000

# output file suffix
OUT_A    = 20k_5m
OUT_B    = 20k_10m


run:
#	clear 
	make
	./serial_mining $(FILE) $(SIZE) $(TRIALS_A) _out_$(OUT_A).csv _time_$(OUT_A).csv
	./serial_mining $(FILE) $(SIZE) $(TRIALS_B) _out_$(OUT_B).csv _time_$(OUT_B).csv


# ------------------------------------------------------------------------------- #

make_serial:
	gcc -fopenmp -g -Wall -o serial_mining serial_mining.c -lm -std=c99
clean:
	$(RM) serial_mining
