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

class Autograder_4_4(Base_Autograder):

    def __init__(self, in_student_name="student", in_this_dir=".", in_test_files=["..", "test_data"]):
        super().__init__()

        # Student information
        self.student_name = in_student_name
        self.is_grad =      True
        self.DEBUG =        True

        # Directory information
        self.this_dir =          in_this_dir
        self.student_files =     "Problem_4"
        self.test_files =        ""

        for i in range(len(in_test_files)):
            self.test_files = os.path.join(self.test_files, in_test_files[i])

        self.test_files = os.path.join(self.test_files, "Problem_4")

        # Test information
        self.threads = [8]
        self.test_names = [
            "P4_4_Test"
        ]

    def autograde(self):
        this_dir = os.path.abspath(self.this_dir)
        test_dir = os.path.abspath(self.test_files)
        student_name = self.student_name

        # Print the test dir and project dir
        if self.DEBUG:
            print(f"{G} --> Test dir: {test_dir}{W}")
            print(f"{G} --> Project dir: {this_dir}{W}")

        # get num cols for threads
        columns = []
        for test in self.test_names:
            columns.append(test)

        # student grades
        grade = pd.DataFrame(
            np.nan,
            index=[student_name],
            columns=columns
        )

        # student timing
        time = pd.DataFrame(
            np.nan,
            index=[student_name],
            columns=columns
        )

        # Expected input
        t_p4_in = [
            os.path.join(test_dir, "mat_input.csv")
        ]

        # Expected output
        t_p4_out = [
            os.path.join(test_dir, "mat_p4_output.csv")
        ]

        # Actual program output
        t_dir = os.path.join(this_dir, "Problem_4")
        t_p4_get = [
            os.path.join(t_dir, "results.csv")
        ]
        t_p4_tim = [
            os.path.join(t_dir, "time.csv")
        ]

        # Generate the commands to run the tests here
        c_p4 = []

        # Alternate program names, if needed
        p4_names = [
            "convolution_maxpooling_CUDA"
        ]
        p4_dims = [
            2048,
            2048
        ]

        # Generate the problems command-variables
        for file in range(len(self.test_names)):  # For input
            c_p4.append([
                p4_names[0],     # program name
                p4_dims[0],      # input dim
                p4_dims[1],      # input dim
                t_p4_in[0],      # input file
                t_p4_get[file],  # resulting output file
                t_p4_tim[file]   # resulting time file
            ])

        #  we have everything we need to test a problem now
        test_params = []
        for file in range(len(self.test_names)):  # For input
            test_params.append([
                t_dir,
                t_p4_out[file],
                t_p4_get[file],
                c_p4[file],
                False
            ])

        # testing results
        test_results = [None] * len(columns)
        time_results = [None] * len(columns)

        # test every problem in a loop
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

            # set results
            test_results[file] = result[0]
            time_results[file] = result[1]

            # add each result to the dataframes
            grade.loc[student_name, columns[file]] = test_results[file][0]
            time.loc[student_name, columns[file]] = str(time_results[file][0])

        return [grade, time]
    

def main():
    print(f"{G}Autograding for Project 4 Problem 4:\n{W}")
    
    p4 = Autograder_4_4()
    res = p4.autograde()

    total   = len(res[0].columns)
    correct = int(res[0].sum(axis=1)[0])

    print(f"{Y}\nFinal Grades:{W}")
    res[0].to_csv("P4_4_grades.csv")
    print(res[0])

    print(f"{Y}\nFinal Timings:{W}")
    res[1].to_csv("P4_4_times.csv")
    print(res[1])

    print(f"\n --> {correct}/{total} problems correct\n")


if __name__ == "__main__":
    main()