NVCC        = nvcc
NVCC_FLAGS  = -O3 -I/usr/local/cuda/include  
LD_FLAGS    = -lcudart -L/usr/local/cuda/lib64
EXE	    = gpu_mining_starter
OBJ	    = gpu_mining_starter.o support.o

default: $(EXE)

$(EXE):$(OBJ)
	$(NVCC) -o $@ $^ $(LD_FLAGS)

# ------------------------------------------------------------------------------- #

# input file and size
FILE     = debug_1k.csv
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
	./gpu_mining_starter $(FILE) $(SIZE) $(TRIALS_A) _out_$(OUT_A).csv _time_$(OUT_A).csv
	./gpu_mining_starter $(FILE) $(SIZE) $(TRIALS_B) _out_$(OUT_B).csv _time_$(OUT_B).csv


# ------------------------------------------------------------------------------- #

gpu_mining_starter.o: gpu_mining_starter.cu nonce_kernel.cu hash_kernel.cu support.h
	$(NVCC) -c -o $@ gpu_mining_starter.cu $(NVCC_FLAGS) $(LD_FLAGS)

support.o: support.cu support.h
	$(NVCC) -c -o $@ support.cu $(NVCC_FLAGS) $(LD_FLAGS)

clean:
	rm -rf *.o $(EXE)
