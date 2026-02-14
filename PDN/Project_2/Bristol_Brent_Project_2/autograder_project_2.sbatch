#!/bin/bash
# Choose the partition that you will use.
# You can choose: oucspdn_cpu OR debug_5min OR debug OR others 
#
#SBATCH --partition=oucspdn_cpu
#
#SBATCH --ntasks=8
#SBATCH --ntasks-per-node=8
#
#SBATCH --time=00:30:00
#SBATCH --job-name=auto
#
#
# --------------------- Change the items below here! ---------------------
#
#SBATCH --mail-user=youremail@ou.edu
#SBATCH --mail-type=ALL
#
#SBATCH --chdir=/home/user007/HW2/
#SBATCH --output=/home/user007/HW2/autograding_%J_stdout.txt
#SBATCH --error=/home/user007/HW2/autograding_%J_stderr.txt

#################################################

source /home/oucspdnta/activate_pdn_env.sh

# To run all the problems and get all results
python3 -u autograder_project_2.py

# To run just problem 1's autograder
# python3 -u autograder_problem_2_1.py

# To run just problem 2a's autograder
# python3 -u autograder_problem_2_2a.py
 
# To run just problem 2b's autograder
# python3 -u autograder_problem_2_2b.py

# To run just problem 3's autograder
# python3 -u autograder_problem_2_3.py

# To run just problem 4's autograder
# python3 -u autograder_problem_2_4.py