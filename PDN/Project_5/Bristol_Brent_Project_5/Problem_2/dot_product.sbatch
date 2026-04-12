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
#SBATCH --chdir=/home/oucspdnxxx/  ... /Project_5/Problem_2
#SBATCH --output=/home/oucspdnxxx/ ... /Project_5/Problem_2/_P5-2_%J_stdout.txt
#SBATCH --error=/home/oucspdnxxx/  ... /Project_5/Problem_2/_P5-2_%J_stderr.txt
#
#################################################

echo "Working directory:"
pwd
echo ""

module load intel/2022.2
module load OpenMPI/4.1.4-GCC-11.3.0

mpirun -n 2 ./dot_product_MPI 262144 vec1_2_18.csv vec2_2_18.csv result_2p_18.csv time_2p_18.csv
# add for other sizes