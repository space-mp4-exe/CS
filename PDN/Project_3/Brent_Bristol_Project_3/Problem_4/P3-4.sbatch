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
#SBATCH --job-name=P3-4
#
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=yourEmailHere@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --chdir=/home/oucspdnxxx/ ... /Project_3/Problem_4
#SBATCH --output=/home/oucspdnxxx/ ... /Project_3/Problem_4/_P3-4_%J_stdout.txt
#SBATCH --error=/home/oucspdnxxx/ ... /Project_3/Problem_4/_P3-4_%J_stderr.txt

#################################################

# make run <-- You can run commands from your makefile if you so wish.
./kmeans_parallel_starter 1000000 points_1M.csv 16 initial_centroids.csv output.csv time.csv 1