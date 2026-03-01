#!/bin/bash
# Choose the partition that you will use.
# You can choose: oucspdn_cpu OR debug_5min OR debug OR others 
#
#
#SBATCH --partition=oucspdn_cpu # change this for multiple runs
#
#SBATCH --ntasks=8
#SBATCH --ntasks-per-node=8
#
#SBATCH --time=00:15:00	# change for another node
#SBATCH --job-name=P3-3
#
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --chdir=/home/oucspdnxxx/ ... /Project_3/Problem_3
#SBATCH --output=/home/oucspdnxxx/ ... /Project_3/Problem_3/_P3-3_%J_stdout.txt
#SBATCH --error=/home/oucspdnxxx/ ... /Project_3/Problem_3/_P3-3_%J_stderr.txt

#################################################

module purge
module load Python

python3 3_algorithm.py