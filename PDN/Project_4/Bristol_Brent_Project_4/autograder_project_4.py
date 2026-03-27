from autograder_problem_4_1 import Autograder_4_1
from autograder_problem_4_2 import Autograder_4_2
from autograder_problem_4_3 import Autograder_4_3
from autograder_problem_4_4 import Autograder_4_4

# Colors
W = '\033[0m'  # white (normal)
R = '\033[31m'  # red
O = '\033[33m'  # orange
Y = '\033[93m'  # yellow
G = '\033[32m'  # green


def main():
    print(f"{G}Autograding for Project 4:\n{W}")

    # Grade Problem 1
    print(f"{G}Autograding for Project 4 Problem 1:\n{W}")
    p1 = Autograder_4_1()
    res1 = p1.autograde()
    total1 = str(len(res1[0].columns))
    correct1 = str(int(res1[0].sum(axis=1)[0]))

    # Grade Problem 2
    print(f"{G}Autograding for Project 4 Problem 2:\n{W}")
    p2 = Autograder_4_2()
    res2 = p2.autograde()
    total2 = str(len(res2[0].columns))
    correct2 = str(int(res2[0].sum(axis=1)[0]))

    # Grade Problem 3
    print(f"{G}Autograding for Project 4 Problem 3:\n{W}")
    p3 = Autograder_4_3()
    res3 = p3.autograde()
    total3 = str(len(res3[0].columns))
    correct3 = str(int(res3[0].sum(axis=1)[0]))

    # Grade Problem 4
    print(f"{G}Autograding for Project 4 Problem 4:\n{W}")
    p4 = Autograder_4_4()
    res4 = p4.autograde()
    total4 = str(len(res4[0].columns))
    correct4 = str(int(res4[0].sum(axis=1)[0]))
  
    # Print results
    print(f"{Y}\n Problem 1 Final Grades:{W}")
    print(res2[0])
    res2[0].to_csv("P4_1_grades.csv")
    res2[1].to_csv("P4_1_times.csv")

    print(f"{Y}\n Problem 2 Final Grades:{W}")
    print(res2[0])
    res2[0].to_csv("P4_2_grades.csv")
    res2[1].to_csv("P4_2_times.csv")

    print(f"{Y}\n Problem 3 Final Grades:{W}")
    print(res3[0])
    res3[0].to_csv("P4_3_grades.csv")
    res3[1].to_csv("P4_3_times.csv")

    print(f"{Y}\n Problem 4 Final Grades:{W}")
    print(res4[0])
    res4[0].to_csv("P4_4_grades.csv")
    res4[1].to_csv("P4_4_times.csv")

    correct = correct2 + correct3 + correct4
    total = total2 + total3 + total4 
    print(f"{R}\n --> {correct}/{total} problems correct\n{W}")

    return


if __name__ == "__main__":
    main()