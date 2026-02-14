from autograder_problem_2_1 import Autograder_2_1
from autograder_problem_2_2a import Autograder_2_2a
from autograder_problem_2_2b import Autograder_2_2b
from autograder_problem_2_3 import Autograder_2_3
from autograder_problem_2_4 import Autograder_2_4

# Colors
W = '\033[0m'  # white (normal)
R = '\033[31m'  # red
O = '\033[33m'  # orange
Y = '\033[93m'  # yellow
G = '\033[32m'  # green


def main():
    print(f"{G}Autograding for Project 2:\n{W}")

    # Grade Problem 1
    print(f"{G}Autograding for Project 2 Problem 1:\n{W}")
    p1 = Autograder_2_1()
    res1 = p1.autograde()
    total1 = str(len(res1[0].columns))
    correct1 = str(int(res1[0].sum(axis=1)[0]))

    # Grade Problem 2a
    print(f"{G}Autograding for Project 2 Problem 2a:\n{W}")
    p2a = Autograder_2_2a()
    res2a = p2a.autograde()
    total2a = str(len(res2a[0].columns))
    correct2a = str(int(res2a[0].sum(axis=1)[0]))

    # Grade Problem 2b
    print(f"{G}Autograding for Project 2 Problem 2b:\n{W}")
    p2b = Autograder_2_2b()
    res2b = p2b.autograde()
    total2b = str(len(res2b[0].columns))
    correct2b = str(int(res2b[0].sum(axis=1)[0]))

    # Grade Problem 3
    print(f"{G}Autograding for Project 2 Problem 3:\n{W}")
    p3 = Autograder_2_3()
    res3 = p3.autograde()
    total3 = str(len(res3[0].columns))
    correct3 = str(int(res3[0].sum(axis=1)[0]))

    # Grade Problem 4
    print(f"{G}Autograding for Project 2 Problem 4:\n{W}")
    p4 = Autograder_2_4()
    res4 = p4.autograde()
    total4 = str(len(res4[0].columns))
    correct4 = str(int(res4[0].sum(axis=1)[0]))
  
    # Print results
    print(f"{Y}\n Problem 1 Final Grades:{W}")
    print(res1[0])
    res1[0].to_csv("P2_1_grades.csv")
    res1[1].to_csv("P2_1_times.csv")

    print(f"{Y}\n Problem 2a Final Grades:{W}")
    print(res2a[0])
    res2a[0].to_csv("P2_2a_grades.csv")
    res2a[1].to_csv("P2_2a_times.csv")

    print(f"{Y}\n Problem 2b Final Grades:{W}")
    print(res2b[0])
    res2b[0].to_csv("P2_2b_grades.csv")
    res2b[1].to_csv("P2_2b_times.csv")

    print(f"{Y}\n Problem 3 Final Grades:{W}")
    print(res3[0])
    res3[0].to_csv("P2_3_grades.csv")
    res3[1].to_csv("P2_3_times.csv")

    print(f"{Y}\n Problem 4 Final Grades:{W}")
    print(res4[0])
    res4[0].to_csv("P2_4_grades.csv")
    res4[1].to_csv("P2_4_times.csv")

    correct = correct1 + correct2a + correct2b + correct3 + correct4
    total = total1 + total2a + total2b + total3 + total4 
    print(f"{R}\n --> {correct}/{total} problems correct\n{W}")

    return


if __name__ == "__main__":
    main()