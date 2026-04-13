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
Project 5, Problem 4 Autograder
"""
class Autograder_5_4(Base_Autograder):

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
        self.test_out_files =   ""

        for i in range(len(in_test_files)):
            self.test_out_files = os.path.join(self.test_out_files, in_test_files[i])

        self.test_out_files =   os.path.join(self.test_out_files, "Problem_4")

        # Test information
        self.threads = [2, 4, 8]
        self.test_names = [
            "P4"
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
            
            # Compare each value of pi and check if they are within 5% of each other
            student_val = result
            expected_val = expected

            err_margin = 0.05
            if (student_val > expected_val - (err_margin * expected_val)) and (student_val < expected_val + (err_margin * expected_val)):
                return True
        
            print(f"{Y}Student value ({student_val[0]}, {student_val[1]}) is not within {err_margin * 100}% range of expected value ({expected_val[0]}, {expected_val[1]}){W}")
            return False

        except Exception as err:
            print(f"{R}Error reading output file:{W}")
            print(f"{R}\t{err}{W}")

        return


    """
    Autogrades Problem 4
    Overrides Base_Autograder.autograde()

    Constructs a test by retrieving data about paths and data locations, then calls Base_Autograder.grade_problem()
    to test and grade the problem
    """

    def autograde(self):
        this_dir =      os.path.abspath(self.this_dir)
        test_out_dir =  os.path.abspath(self.test_out_files)

        # Print the test dir and project dir
        if self.DEBUG:
            print(f"{G} --> Test dir: {test_out_dir}{W}")
            print(f"{G} --> Project dir: {this_dir}{W}")

        # get num cols for threads
        columns = []
        for t in self.threads:
            for p in self.test_names:
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

        # Expected output files
        t_out = [
            os.path.join(test_out_dir, "pi_true_value.csv")
        ]

        # The actual output from the student
        t_dir = os.path.join(this_dir, self.student_files)
        t_get = [
            []
        ]
        t_tim = [
            []
        ]

        for out in range(len(t_out)):
            for i in range(len(self.threads)):
                t_get[out].append(os.path.join(t_dir, f"result_{self.threads[i]}p.csv"))
                t_tim[out].append(os.path.join(t_dir, f"time_{self.threads[i]}p.csv"))

        # Generate the commands for the program
        # Command structure:
        #   dot_product_MPI vector_size vec_1.csv vec_2.csv result.csv time.csv
        c_p2 = [
            []
        ]
        for file in range(len(self.test_names)):
            for t in range(len(self.threads)):
                c_p2[file].append([
                    "pi_MPI",
                    t_get[file][t],
                    t_tim[file][t]
                ])

        # Reference dictionary
        c_p4_ref = {"r": 1, "t": 2}

        test_params = [
            []
        ]
        for t in range(len(self.threads)):
            test_params[file].append(
                [t_dir, t_out[file], t_get[file][t], c_p2[file][t], False, self.is_error_within_bound]
            )

        # Get the grades
        # student_dir, t_output, t_res, commands, exact
        # testing results
        test_results = [None] * len(columns)
        time_results = [None] * len(columns)

        # test every problem in a loop
        grade_index = 0
        for file in range(len(self.test_names)):
            for thread in range(len(self.threads)):
                params = test_params[file][thread]
                result = self.grade_problem(
                    params[0],  # Problem dir
                    [params[1]],  # Expected outputs of test i
                    [params[2]],  # Output file names
                    [params[3]],  # Command for getting test i results
                    c_p4_ref,    # Reference dictionary
                    params[4],   # Whether to let the differences have an error range
                    params[5]    # Error check function
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
    print(f"{G}Autograding for Project 5 Problem 4:\n{W}")
    
    p4 = Autograder_5_4()
    res = p4.autograde()

    total   = len(res[0].columns)
    correct = int(res[0].sum(axis=1)[0])

    print(f"{Y}\nFinal Grades:{W}")
    res[0].to_csv("P5_4_grades.csv")
    print(res[0])

    print(f"{Y}\nFinal Timings:{W}")
    res[1].to_csv("P5_4_times.csv")
    print(res[1])

    print((f"\n --> {correct}/{total} problems correct\n"))


if __name__ == "__main__":
    main()