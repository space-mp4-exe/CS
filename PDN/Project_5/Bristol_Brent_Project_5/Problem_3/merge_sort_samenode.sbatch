#!/bin/bash
#SBATCH --partition=oucspdn_cpu
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=4
#
#SBATCH --time=00:15:00
#SBATCH --job-name=hw5prob3
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --chdir=/home/oucspdn007/Project_5/Bristol_Brent_Project_5/Problem_3
#SBATCH --output=/home/oucspdn007/Project_5/Bristol_Brent_Project_5/Problem_3/_P5-3_%J_stdout.txt
#SBATCH --error=/home/oucspdn007/Project_5/Bristol_Brent_Project_5/Problem_3/_P5-3_%J_stderr.txt

#################################################

echo "Working directory:"
pwd
echo ""

module load intel/2022.2
module load OpenMPI/4.1.4-GCC-11.3.0

make

mpirun -n 4 ./merge_sort_MPI 262144 ../../test_data/Vectors/vec1_2^18.csv result_4_same_18.csv time_4_same_18.csv
mpirun -n 4 ./merge_sort_MPI 524288 ../../test_data/Vectors/vec1_2^19.csv result_4_same_19.csv time_4_same_19.csv
mpirun -n 4 ./merge_sort_MPI 1048576 ../../test_data/Vectors/vec1_2^20.csv result_4_same_20.csv time_4_same_20.csv
# add more here ...