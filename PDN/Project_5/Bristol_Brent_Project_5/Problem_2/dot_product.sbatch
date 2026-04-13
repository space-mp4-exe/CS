#!/bin/bash
#SBATCH --partition=oucspdn_cpu
#SBATCH --ntasks-per-node=8
#SBATCH --ntasks=8
#
#SBATCH --time=00:15:00
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --job-name=hw5prob2
#
#SBATCH --chdir=/home/oucspdn007/Project_5/Bristol_Brent_Project_5/Problem_2
#SBATCH --output=/home/oucspdn007/Project_5/Bristol_Brent_Project_5/Problem_2/_P5-2_%J_stdout.txt
#SBATCH --error=/home/oucspdn007/Project_5/Bristol_Brent_Project_5/Problem_2/_P5-2_%J_stderr.txt
#
#################################################

echo "Working directory:"
pwd
echo ""

module load intel/2022.2
module load OpenMPI/4.1.4-GCC-11.3.0

make

mpirun -n 2 ./dot_product_MPI 262144 ../../test_data/Vectors/vec1_2^18.csv ../../test_data/Vectors/vec2_2^18.csv result_2p_18.csv time_2p_18.csv
mpirun -n 2 ./dot_product_MPI 524288 ../../test_data/Vectors/vec1_2^19.csv ../../test_data/Vectors/vec2_2^19.csv result_2p_19.csv time_2p_19.csv
mpirun -n 2 ./dot_product_MPI 1048576 ../../test_data/Vectors/vec1_2^20.csv ../../test_data/Vectors/vec2_2^20.csv result_2p_20.csv time_2p_20.csv
mpirun -n 4 ./dot_product_MPI 262144 ../../test_data/Vectors/vec1_2^18.csv ../../test_data/Vectors/vec2_2^18.csv result_4p_18.csv time_4p_18.csv
mpirun -n 4 ./dot_product_MPI 524288 ../../test_data/Vectors/vec1_2^19.csv ../../test_data/Vectors/vec2_2^19.csv result_4p_19.csv time_4p_19.csv
mpirun -n 4 ./dot_product_MPI 1048576 ../../test_data/Vectors/vec1_2^20.csv ../../test_data/Vectors/vec2_2^20.csv result_4p_20.csv time_4p_20.csv
mpirun -n 8 ./dot_product_MPI 262144 ../../test_data/Vectors/vec1_2^18.csv ../../test_data/Vectors/vec2_2^18.csv result_8p_18.csv time_8p_18.csv
mpirun -n 8 ./dot_product_MPI 524288 ../../test_data/Vectors/vec1_2^19.csv ../../test_data/Vectors/vec2_2^19.csv result_8p_19.csv time_8p_19.csv
mpirun -n 8 ./dot_product_MPI 1048576 ../../test_data/Vectors/vec1_2^20.csv ../../test_data/Vectors/vec2_2^20.csv result_8p_20.csv time_8p_20.csv