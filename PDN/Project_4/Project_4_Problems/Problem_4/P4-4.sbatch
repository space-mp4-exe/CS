#!/bin/bash
# Choose the partition that you will use.
# You can choose: oucspdn_gpu or debug_gpu or gpu 
#
#
#SBATCH --partition=oucspdn_gpu
#
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#
#SBATCH --job-name=P4-4_gpu
#SBATCH --time=00:15:00
#SBATCH --job-name=P4-4
#
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --chdir=/home/oucspdnxxx/ ... /Project_4/Problem_1
#SBATCH --output=/home/oucspdnxxx/ ... /Project_4/Problem_1/_P4-4_%J_stdout.txt
#SBATCH --error=/home/oucspdnxxx/ ... /Project_4/Problem_1/_P4-4_%J_stderr.txt

#################################################

module purge
module load CUDA/10.1.243-GCC-8.3.0

# Add commands here
make run