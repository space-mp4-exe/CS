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


class Autograder_4_3(Base_Autograder):

    def __init__(self, in_student_name="student", in_this_dir=".", in_test_files=["..", "test_data"]):
        super().__init__()

        # Student information
        self.student_name = in_student_name
        self.is_grad =      True
        self.DEBUG =        True

        # Directory information
        self.this_dir =          in_this_dir
        self.student_files =     "Problem_3"
        self.test_files =        ""

        for i in range(len(in_test_files)):
            self.test_files = os.path.join(self.test_files, in_test_files[i])

        self.test_files = os.path.join(self.test_files, "Problem_3")

        # Test information
        self.threads = [8]
        self.test_names = [
            "P4_3_Test"
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
        t_p3_in = [
            os.path.join(test_dir, "mat_input.csv")
        ]

        # Expected output
        t_p3_out = [
            os.path.join(test_dir, "mat_p3_output.csv")
        ]

        # actual program output
        t_dir = os.path.join(this_dir, "Problem_3")
        t_p3_get = [
            os.path.join(t_dir, "results.csv")
        ]
        t_p3_tim = [
            os.path.join(t_dir, "time.csv")
        ]

        # Generate the commands to run the tests
        c_p3 = []

        # Program names
        p3_names = [
            "convolution_CUDA"
        ]
        p3_dims = [
            2048,
            2048
        ]

        # Problem 3
        for file in range(len(self.test_names)):  # For input
            c_p3.append([
                p3_names[0],     # program name
                p3_dims[0],      # input dim
                p3_dims[1],      # input dim
                t_p3_in[0],      # input file
                t_p3_get[file],  # resulting output file
                t_p3_tim[file]   # resulting time file
            ])

        test_params = []
        for file in range(len(self.test_names)):  # For input
            test_params.append([
                os.path.join(this_dir, "Problem_3"),
                t_p3_out[file],
                t_p3_get[file],
                c_p3[file],
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
    print(f"{G}Autograding for Project 4 Problem 3:\n{W}")
    
    p3 = Autograder_4_3()
    res = p3.autograde()

    total   = len(res[0].columns)
    correct = int(res[0].sum(axis=1)[0])

    print(f"{Y}\nFinal Grades:{W}")
    res[0].to_csv("P4_3_grades.csv")
    print(res[0])

    print(f"{Y}\nFinal Timings:{W}")
    res[1].to_csv("P4_3_times.csv")
    print(res[1])

    print(f"\n --> {correct}/{total} problems correct\n")


if __name__ == "__main__":
    main()