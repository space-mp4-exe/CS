import numpy as np
import os
import pandas as pd
import sys

# Tell the script where to find the base autograder
sys.path.append("..")
sys.path.append(os.path.join("..", ".."))
from autograder_base import Base_Autograder

# Colors
W = '\033[0m'  # white (normal)
R = '\033[31m'  # red
O = '\033[33m'  # orange
Y = '\033[93m'  # yellow
G = '\033[32m'  # green


class Autograder_4_1(Base_Autograder):

    def __init__(self, in_student_name="student", in_this_dir=".", in_test_files=["..", "test_data"]):
        super().__init__()

        # Student information
        self.student_name = in_student_name
        self.is_grad = True
        self.DEBUG = True

        # Directory information
        self.this_dir =          in_this_dir
        self.student_files =     "Problem_1"
        self.test_in_files =     ""
        self.test_out_files =    ""

        for i in range(len(in_test_files)):
            self.test_in_files = os.path.join(self.test_in_files, in_test_files[i])
            self.test_out_files = os.path.join(self.test_out_files, in_test_files[i])

        self.test_in_files =    os.path.join(self.test_in_files, "Problem_1_and_2")
        self.test_out_files =   os.path.join(self.test_out_files, "Problem_1_and_2")

        # Test information
        self.threads = [8]
        self.test_names = [
            "P1-20k-5m",
            "P1-20k-10m"
        ]


    def autograde(self):
        this_dir =      os.path.abspath(self.this_dir)
        test_in_dir =   os.path.abspath(self.test_in_files)
        test_out_dir =  os.path.abspath(self.test_out_files)

        # Print the test dir and project dir
        if self.DEBUG:
            print(f"{G} --> Test dir: {test_in_dir}{W}")
            print(f"{G} --> Project dir: {this_dir}{W}")

        # get num cols for threads
        columns = []
        for test in self.test_names:
            columns.append(test)

        # student grades
        grade = pd.DataFrame(
            np.nan,
            index=[self.student_name],
            columns=columns
        )

        # student timing
        time = pd.DataFrame(
            np.nan,
            index=[self.student_name],
            columns=columns
        )

        # Expected input
        t_p1_in = [
            os.path.join(test_in_dir, "in_20k.csv")
        ]

        # Expected output
        t_dir = os.path.join(test_out_dir, "gpu_nonce_files")

        t_p1_out = [
            os.path.join(t_dir, "out_gpu_20k_5m.csv"),
            os.path.join(t_dir, "out_gpu_20k_10m.csv")
        ]

        # Actual student output
        t_dir = os.path.join(this_dir, self.student_files)
        t_p1_get = [
            os.path.join(t_dir, "results_20k_5m.csv"),
            os.path.join(t_dir, "results_20k_10m.csv")
        ]
        t_p1_tim = [
            os.path.join(t_dir, "time_20k_5m.csv"),
            os.path.join(t_dir, "time_20k_10m.csv")
        ]


        # Generate the commands to run the student program
        c_p1 = []

        # Program names, can add alternate ones if need be
        p1_names = [
            "gpu_mining_problem1"
        ]
        p1_dims = [
            [20000],
            [5000000, 10000000]
        ]

        # Command format:
        # gpu_mining_problem1 in_file.csv [in_size] [trial_size] result.csv time.csv
        for file in range(len(self.test_names)):  # For input
            c_p1.append([
                p1_names[0],       # program name
                t_p1_in[0],        # input file
                p1_dims[0][0],     # input size
                p1_dims[1][file],  # trial size
                t_p1_get[file],    # resulting output file
                t_p1_tim[file]     # resulting time file
            ])

        # Test parameters
        test_params = []
        for file in range(len(self.test_names)):  # For input
            test_params.append([
                os.path.join(this_dir, "Problem_1"),
                t_p1_out[file],
                t_p1_get[file],
                c_p1[file],
                True
            ])

        # Testing results
        test_results = [None] * len(columns)
        time_results = [None] * len(columns)

        # Test every problem in a loop
        grade_index = 0
        for file in range(len(self.test_names)):
            params = test_params[file]
            result = self.grade_problem(
                params[0],  # Problem dir
                [params[1]],  # Expected outputs of test i
                [params[2]],  # Output file names
                [params[3]],  # Command for getting test i results
                params[4],  # Whether to let the differences have an error range
            )
            # Set results
            test_results[file] = result[0]
            time_results[file] = result[1]

            # Add each result to the dataframes
            grade.loc[self.student_name, columns[file]] = test_results[file][0]
            time.loc[self.student_name, columns[file]]  = time_results[file][0]
        
        return [grade, time]
    


def main():
    print(f"{G}Autograding for Project 4 Problem 1:\n{W}")
    
    p1 = Autograder_4_1()
    res = p1.autograde()

    total   = len(res[0].columns)
    correct = int(res[0].sum(axis=1)[0])

    print(f"{Y}\nFinal Grades:{W}")
    res[0].to_csv("P4_1_grades.csv")
    print(res[0])

    print(f"{Y}\nFinal Timings:{W}")
    res[1].to_csv("P4_1_times.csv")
    print(res[1])

    print(f"\n --> {correct}/{total} problems correct\n")


if __name__ == "__main__":
    main()