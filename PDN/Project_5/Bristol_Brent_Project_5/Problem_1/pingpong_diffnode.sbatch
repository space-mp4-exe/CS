#!/bin/bash
#SBATCH --partition=oucspdn_cpu
#SBATCH --ntasks-per-node=2
#SBATCH --ntasks=2
#
#SBATCH --time=00:15:00
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --job-name=hw5prob1_diff
#
#SBATCH --chdir=/home/oucspdnxxx/  ... /Project_5/Problem_1
#SBATCH --output=/home/oucspdnxxx/ ... /Project_5/Problem_1/_P5-1_diff_%J_stdout.txt
#SBATCH --error=/home/oucspdnxxx/  ... /Project_5/Problem_1/_P5-1_diff_%J_stderr.txt
#
#################################################

echo "Working directory:"
pwd
echo ""

module load intel/2022.2
module load OpenMPI/4.1.4-GCC-11.3.0

mpirun -n 2 ./pingpong_MPI 1000000 time_1M_diff.csv
# add for other sizes