NVCC        = nvcc
NVCC_FLAGS  = -O3 -I/usr/local/cuda/include  
NVCC_FLAGS_WIN = -O3 -I"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.2/include/CL"
LD_FLAGS    = -lcudart -L/usr/local/cuda/lib64
LD_FLAGS_WIN   = -lcudart -L"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.2/lib/x64"
EXE	    = gpu_mining_problem1
OBJ	    = gpu_mining_problem1.o support.o

default: $(EXE)

$(EXE):$(OBJ)
	$(NVCC) -o $@ $^ $(LD_FLAGS_WIN)

# ------------------------------------------------------------------------------- #

# input file and size
FILE     =  ../Bristol_Brent_Project_4/Problem_1_and_2/in_20k.csv
SIZE	 = 20000

# number of trials to run
TRIALS_A = 5000
TRIALS_B = 10000

# output file suffix
OUT_A    = 20k_5k
OUT_B    = 20k_10k


run:
	make
	./gpu_mining_problem1 $(FILE) $(SIZE) $(TRIALS_A) _results_$(OUT_A).csv _time_$(OUT_A).csv
	./gpu_mining_problem1 $(FILE) $(SIZE) $(TRIALS_B) _results_$(OUT_B).csv _time_$(OUT_B).csv


# ------------------------------------------------------------------------------- #

gpu_mining_problem1.o: gpu_mining_problem1.cu nonce_kernel.cu hash_kernel.cu support.h
	$(NVCC) -c -o $@ gpu_mining_problem1.cu $(NVCC_FLAGS_WIN) $(LD_FLAGS_WIN) 

support.o: support.cu support.h
	$(NVCC) -c -o $@ support.cu $(NVCC_FLAGS_WIN) $(LD_FLAGS_WIN)

clean:
	rm -rf *.o $(EXE)
