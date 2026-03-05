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


"""
Project 3, Problem 3 Autograder

Autogrades a single student's code
"""
class Autograder_3_3(Base_Autograder):

    def __init__(self, in_student_name="student", in_this_dir=".", in_test_files=["..", "test_data"]):
        super().__init__()

        # Student information
        self.student_name = in_student_name
        self.is_grad = True

        # Directory information
        self.this_dir =          in_this_dir
        self.student_files =     "Problem_3"
        self.test_in_files =     ""
        self.test_out_files=     ""

        for i in range(len(in_test_files)):
            self.test_in_files = os.path.join(self.test_in_files, in_test_files[i])
            self.test_out_files = os.path.join(self.test_out_files, in_test_files[i])

        self.test_in_files =     os.path.join(self.test_in_files, "DNA_Files")
        self.test_out_files =    os.path.join(self.test_out_files, "Problem_3")

        # Test information
        self.threads = [1, 2, 4, 8]

        self.test_names = [
            # 50 items
            [
                ["p3-50-baseline"],  # baseline
                ["p3-50-mapreduce"]  # mapreduce
            ],

            # Reduced items
            [
                ["p3-Reduced-baseline"],  # baseline
                ["p3-Reduced-mapreduce"], # mapreduce
            ]
        ]


    """
    Check if the student's answer is within a reasonable bound of the actual answer
    Error Bound:
        - Check that student's answer is within 1% of actual answer

    Parameters:
        - expected  (ndarray):  The actual answer read from test_data/
        - result    (ndarray):  The student's answer
    """
    def is_error_within_bound(self, expected, result):

        try:
            # Make sure the shapes of the 
            if expected.shape != result.shape:
                raise Exception("Shapes of expected output and student output do not match")
            
            # Compare the two arrays
            return np.array_equal(expected, result, equal_nan=True)

        except Exception as err:
            print(f"{R}Error reading output file:{W}")
            print(f"{R}\t{err}{W}")

        return


    """
    Autogrades Problem 3
    Overrides Base_Autograder.autograde()

    Constructs a test by retrieving data about paths and data locations, then calls Base_Autograder.grade_problem()
    to test and grade the problem
    """
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
        for file in self.test_names:
            for program in file:
                for i in range(len(self.threads)):
                    columns.append(f"{program[0]}-T{self.threads[i]}")

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

        # Input RNA files
        t_rna = [
            os.path.join(test_in_dir, "GRCh38_50_rna.fna"),
            os.path.join(test_in_dir, "GRCh38_reduced_rna.fna")
        ]

        # The expected output files
        t_out = [
            os.path.join(test_out_dir, "p3_output_50.csv"),
            os.path.join(test_out_dir, "p3_output_reduced.csv")
        ]

        # The actual output from the student
        t_dir = os.path.join(this_dir, self.student_files)
        t_p3_prefix = ["baseline", "mapreduce"]
        t_p3_get = [
            [[], []],  # 50
            [[], []]   # reduced
        ]
        t_p3_tim = [
            [[], []],  # 50
            [[], []]   # reduced
        ]
        rna = ["50", "reduced"]
        for out in range(len(t_out)):
            for pre in range(len(t_p3_prefix)):
                for t in self.threads:
                    t_p3_get[out][pre].append(
                        os.path.join(t_dir, f"res_{t_p3_prefix[pre]}_{rna[out]}_{t}th.csv")
                    )
                    t_p3_tim[out][pre].append(
                        os.path.join(t_dir, f"tim_{t_p3_prefix[pre]}_{rna[out]}_{t}th.csv")
                    )

        #   generate the commands to run the tests here
        c_p3 = [
            [[], []],  # 50
            [[], []]   # reduced
        ]

        # TA) TODO: alternate program names, if needed
        p3_names = [
            "compute_median_TF_Exp1_baseline",
            "compute_median_TF_Exp2_mapreduce"
        ]

        # TA) TODO: generate the problems' command-variables
        # Problem 3
        for file in range(len(t_rna)):            # For RNA input
            for program in range(len(p3_names)):  # For program
                for t in range(len(self.threads)):     # For num thread counts
                    c_p3[file][program].append([
                        p3_names[program],           # program type, like locks or sharing
                        t_rna[file],                 # input file
                        t_p3_get[file][program][t],  # resulting output file
                        t_p3_tim[file][program][t],  # resulting time file
                        self.threads[t]                   # num threads
                    ])

        # Create the "reference" dictionary that will tell the base autograder where each parameter is located
        c_p3_ref = {"r": 2, "t": 3}

        #  we have everything we need to test a problem now
        #   grade each individual problem here!
        # TA) TODO: specify each problem's test parameters
        # Problem 3
        test_params = [
            [[], []],  # 50
            [[], []]   # reduced
        ]
        for file in range(len(t_rna)):            # For RNA input
            for program in range(len(p3_names)):  # For program names
                for t in range(len(self.threads)):     # For num thread counts
                    test_params[file][program].append(
                        [t_dir, t_out[file], t_p3_get[file][program][t], c_p3[file][program][t], False, self.is_error_within_bound]
                    )

        # testing results
        test_results = [None] * len(columns)
        time_results = [None] * len(columns)

        # test every problem in a loop
        grade_index = 0
        for file in range(len(self.test_names)):
            for program in range(len(self.test_names[file])):
                for thread in range(len(self.threads)):
                    params = test_params[file][program][thread]
                    result = self.grade_problem(
                        params[0],      # Problem dir
                        [params[1]],    # Expected outputs of test i
                        [params[2]],    # Output file names
                        [params[3]],    # Command for getting test i results
                        c_p3_ref,       # The reference dictionary
                        params[4],      # Whether to let the differences have an error range
                        params[5]       # The error check function
                    )

                    # set results
                    test_results[grade_index] = result[0]
                    time_results[grade_index] = result[1]

                    # add each result to the dataframes
                    grade.loc[self.student_name, columns[grade_index]] = test_results[grade_index][0]
                    time.loc[self.student_name,  columns[grade_index]] = time_results[grade_index][0]
                    grade_index = grade_index + 1

        return [grade, time]


"""
Start of Program Logic
"""
def main():
    print(f"{G}Autograding for Project 3 Problem 3:\n{W}")
    
    p3 = Autograder_3_3()
    res = p3.autograde()
    total = str(len(res[0].columns))
    correct = str(int(res[0].sum(axis=1)[0]))

    print(f"{Y}\n Final grades:{W}")
    res[0].to_csv("P3_3_grades.csv")
    print(res[0])

    print(f"{Y}\n Final timings:{W}")
    res[1].to_csv("P3_3_times.csv")
    print(res[1])

    print(f"{R}\n --> {correct}/{total} problems correct\n{W}")


if __name__ == "__main__":
    main()