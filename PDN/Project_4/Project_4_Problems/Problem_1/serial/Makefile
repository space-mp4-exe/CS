
all: make_serial

# ------------------------------------------------------------------------------- #

# input file and size
FILE     = debug_1000.csv
SIZE	 = 1000

# number of trials to run
TRIALS_A = 5000
TRIALS_B = 10000

# output file suffix
OUT_A    = 1k_5k
OUT_B    = 1k_10k


run:
	clear 
	make
	./serial_mining $(FILE) $(SIZE) $(TRIALS_A) _out_$(OUT_A).csv _time_$(OUT_A).csv
	./serial_mining $(FILE) $(SIZE) $(TRIALS_B) _out_$(OUT_B).csv _time_$(OUT_B).csv


# ------------------------------------------------------------------------------- #

make_serial:
	gcc -fopenmp -g -Wall -o serial_mining serial_mining.c -lm -std=c99
clean:
	$(RM) serial_mining
