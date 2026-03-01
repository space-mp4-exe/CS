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

# Note: Running the _latest file may take up to 10 minutes.
# Please use another node and change the time if you wish to test
#	multiple runs of your code!

# make run <-- You can run commands from your makefile if you so wish.
./compute_median_TF_Exp1_starter in.fna OUTPUT_starter_1th.csv TIME_starter_1th.csv 1