#!/bin/bash
# Choose the partition that you will use.
# You can choose: oucspdn_cpu OR debug_5min OR debug OR others 
#
#
#SBATCH --partition=oucspdn_cpu
#
#SBATCH --ntasks=8
#SBATCH --ntasks-per-node=8
#
#SBATCH --time=00:15:00
#SBATCH --job-name=P3-2
#
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --chdir=/home/oucspdnxxx/ ... /Project_3/Problem_2
#SBATCH --output=/home/oucspdnxxx/ ... /Project_3/Problem_2/_P3-2_%J_stdout.txt
#SBATCH --error=/home/oucspdnxxx/ ... /Project_3/Problem_2/_P3-2_%J_stderr.txt

#################################################

module purge
module load Python

python3 2_algorithm.py