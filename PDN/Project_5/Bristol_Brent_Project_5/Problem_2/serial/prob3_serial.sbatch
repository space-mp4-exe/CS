#!/bin/bash
#SBATCH --partition=oucspdn_cpu
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
#SBATCH --ntasks=1
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

./dotprod_serial 262144 ../../test_data/vec1_2_18.csv ../../test_data/vec2_2_18.csv result_2_18.csv time_2_18.csv
# add other sizes
