#!/bin/bash
#SBATCH --partition=parallel_programming_cpu
#SBATCH --exclusive
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --chdir=/home/user007/HW4/Problem_3/serial
#SBATCH --output=/home/user007/HW4/Problem_3/serial/prob3_%J_stdout.txt
#SBATCH --error=/home/user007/HW4/Problem_3/serial/prob3_%J_stderr.txt
#SBATCH --time=00:05:00
#SBATCH --job-name=prob3_serial
#SBATCH --mail-user=user007@ou.edu
#SBATCH --mail-type=ALL

#################################################

./convolution_serial 2048 2048 ../../test_data/mat_input.csv result_prob3_serial.csv time_prob3_serial.csv

