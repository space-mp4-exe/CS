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
Project 2, Problem 2b Autograder

Autogrades a single student's code
"""
class Autograder_2_2b(Base_Autograder):

    """
    Initializes variables
    """
    def __init__(self, in_student_name="student", in_this_dir=".", in_test_files=["..", "test_data"]):
        super().__init__()

        # Student information
        self.student_name = in_student_name
        self.is_grad = True
        self.DEBUG = True

        # Directory information
        self.this_dir =         in_this_dir
        self.student_files =    "Problem_2B"
        self.test_in_files =    ""
        self.test_out_files =   ""

        for i in range(len(in_test_files)):
            self.test_in_files =    os.path.join(self.test_in_files, in_test_files[i])
            self.test_out_files =   os.path.join(self.test_out_files, in_test_files[i])

        self.test_in_files =    os.path.join(self.test_in_files, "Input_Matricies_Prob_1_And_2")
        self.test_out_files =   os.path.join(self.test_out_files, "Problem_2B")

        # Test information
        self.threads = [1, 2, 4, 8]
        self.test_names = [
            "P2b-T1", "P2b-T2", "P2b-T3", "P2b-T4"
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
    Autogrades Problem 2a
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
        for p in self.test_names:
            for t in self.threads:
                columns.append(f"{p}-{t}th")

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

        # Input matrix files
        t_mats_a = [
            os.path.join(test_in_dir, "test1_input_mat_a.csv"),
            os.path.join(test_in_dir, "test2_input_mat_a.csv"),
            os.path.join(test_in_dir, "test3_input_mat_a.csv"),
            os.path.join(test_in_dir, "test4_input_mat_a.csv")
        ]

        t_mats_b = [
            os.path.join(test_in_dir, "test1_input_mat_b.csv"),
            os.path.join(test_in_dir, "test2_input_mat_b.csv"),
            os.path.join(test_in_dir, "test3_input_mat_b.csv"),
            os.path.join(test_in_dir, "test4_input_mat_b.csv")      
        ]

        # Expected output files
        t_out = [
            os.path.join(test_out_dir, "test1_output_second_max.csv"),
            os.path.join(test_out_dir, "test2_output_second_max.csv"),
            os.path.join(test_out_dir, "test3_output_second_max.csv"),
            os.path.join(test_out_dir, "test4_output_second_max.csv")
        ]

        # The actual output from the student
        t_dir = os.path.join(this_dir, self.student_files)
        t_get = [[], [], [], []]
        t_tim = [[], [], [], []]

        for out in range(len(self.test_names)):
            for i in range(len(self.threads)):
                t_get[out].append(os.path.join(t_dir, f"test{out + 1}_output_mat_{self.threads[i]}p.csv"))
                t_tim[out].append(os.path.join(t_dir, f"test{out + 1}_time_{self.threads[i]}p.csv"))

        # Generate commands for the program
        # Command structure:
        #       parallel_mult_second_largest file_1.csv n_row_1 n_col_1 file_2.csv n_row5_2 n_col_2 result.csv time.csv num_threads
        test_data = [
            [t_mats_a[0], 1000, 1000, t_mats_b[0], 1000, 1000],
            [t_mats_a[1], 1000, 1000, t_mats_b[1], 1000, 2000],
            [t_mats_a[2], 2000, 1000, t_mats_b[2], 1000, 2000],
            [t_mats_a[3], 2000, 2000, t_mats_b[3], 2000, 2000]
        ]
        c_p2b = [
            [], [], [], []
        ]

        for file in range(len(self.test_names)):
            for t in range(len(self.threads)):
                c_p2b[file].append([
                    "parallel_mult_second_largest",
                    test_data[file][0],
                    test_data[file][1],
                    test_data[file][2],
                    test_data[file][3],
                    test_data[file][4],
                    test_data[file][5],
                    t_get[file][t],
                    t_tim[file][t],
                    self.threads[t]
                ])

        # Command references
        c_p2b_ref = {"r": 7, "t": 8}

        # Autograde with test parameters
        test_params = [
            [], [], [], []
        ]

        for file in range(len(self.test_names)):
            for t in range(len(self.threads)):
                test_params[file].append(
                    [t_dir, t_out[file], t_get[file][t], c_p2b[file][t], False, self.is_error_within_bound]
                )

        # List of grade results for each test/thread combination
        test_results = [None] * len(columns)
        time_results = [None] * len(columns)

        # Test every problem
        grade_index = 0
        for file in range(len(self.test_names)):
            for thread in range(len(self.threads)):
                params = test_params[file][thread]
                result = self.grade_problem(
                    params[0],                      # student directory
                    [params[1]],                    # test output
                    [params[2]],                    # test results
                    [params[3]],                    # commands
                    c_p2b_ref,                      # command references
                    params[4],                      # exact
                    params[5]                       # error function to be passed
                )

                # set results
                test_results[grade_index] = result[0]
                time_results[grade_index] = result[1]

                # add each result to the dataframes
                grade.loc[self.student_name, columns[grade_index]] = test_results[grade_index][0]
                time.loc [self.student_name, columns[grade_index]] = time_results[grade_index][0]
                grade_index = grade_index + 1


        return [grade, time]
        

"""
Start of Program Logic
"""
def main():
    print(f"{G}Autograding for Project 2 Problem 2b:\n{W}")
    
    p2 = Autograder_2_2b()
    res = p2.autograde()

    total   = len(res[0].columns)
    correct = int(res[0].sum(axis=1)[0])

    print(f"{Y}\nFinal Grades:{W}")
    res[0].to_csv("P2_2b_grades.csv")
    print(res[0])

    print(f"{Y}\nFinal Timings:{W}")
    res[1].to_csv("P2_2b_times.csv")
    print(res[1])

    print((f"\n --> {correct}/{total} problems correct\n"))


if __name__ == "__main__":
    main()