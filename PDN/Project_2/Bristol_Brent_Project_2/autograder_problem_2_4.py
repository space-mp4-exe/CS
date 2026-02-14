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
Autograder for Project 2, Problem 4
"""
class Autograder_2_4(Base_Autograder):


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
        self.student_files =    "Problem_4"
        self.test_files =       ""

        for i in range(len(in_test_files)):
            self.test_files =    os.path.join(self.test_files, in_test_files[i])

        self.test_files =    os.path.join(self.test_files, "Problem_4")

        # Test information
        self.threads = [1, 2, 4, 8]
        self.test_names = [
            "P4-1"
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
    Autogrades Problem 1
    Overrides Base_Autograder.autograde()

    Constructs a test by retrieving data about paths and data locations, then calls Base_Autograder.grade_problem()
    to test and grade the problem
    """
    def autograde(self):
        this_dir = os.path.abspath(self.this_dir)
        test_dir = os.path.abspath(self.test_files)

        # Print the test dir and project dir
        if self.DEBUG:
            print(f"{G} --> Test dir: {test_dir}{W}")
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

        # Input files
        t_in = [
            os.path.join(test_dir, "test1_text_to_decrypt_input.txt")
        ]

        # Expected output files
        t_out = [
            os.path.join(test_dir, "test1_text_to_decrypt_output.txt")
        ]

        # The actual output from the student
        t_dir = os.path.join(this_dir, self.student_files)
        t_get = [[]]
        t_tim = [[]]

        for out in range(len(t_out)):
            for i in range(len(self.threads)):
                t_get[out].append(os.path.join(t_dir, f"test{out + 1}_output_{self.threads[i]}p.txt"))
                t_tim[out].append(os.path.join(t_dir, f"test{out + 1}_time_{self.threads[i]}p.csv"))

        # Generate commands for the program
        # Command structure:
        #       decrypt_parallel input_text.txt key.txt time.txt num_threads 
        c_p4 = [
            []
        ]

        for file in range(len(self.test_names)):
            for t in range(len(self.threads)):
                c_p4[file].append([
                    "decrypt_parallel",
                    t_in[file],
                    t_get[file][t],
                    t_tim[file][t],
                    self.threads[t]
                ])

        # Command references
        c_p4_ref = {"r": 2, "t": 3}

        # Autograde with test parameters
        test_params = [
            []
        ]

        for file in range(len(self.test_names)):
            for t in range(len(self.threads)):
                test_params[file].append(
                    [t_dir, t_out[file], t_get[file][t], c_p4[file][t], False, self.is_error_within_bound]
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
                    c_p4_ref,                       # command references
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
        

def main():
    print(f"{G}Autograding for Project 2 Problem 4:\n{W}")
    
    p4 = Autograder_2_4()
    res = p4.autograde()

    total   = len(res[0].columns)
    correct = int(res[0].sum(axis=1)[0])

    print(f"{Y}\nFinal Grades:{W}")
    res[0].to_csv("P2_4_grades.csv")
    print(res[0])

    print(f"{Y}\nFinal Timings:{W}")
    res[1].to_csv("P2_4_times.csv")
    print(res[1])

    print((f"\n --> {correct}/{total} problems correct\n"))


if __name__ == "__main__":
    main()