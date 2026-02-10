import sys

if len(sys.argv) <= 1:
    print("Use this file like this: sage hw3_inverse.sage 16")
    exit()

R = Integers(int(sys.argv[1])) 

units = [x for x in R if x.is_unit()]
zero_divisors = [y for y in R if y != 0 and not y.is_unit()]
print("Unit group:", units)
print("Zero divisors:", zero_divisors)
