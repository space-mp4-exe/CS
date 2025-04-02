def extendGCD(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd, x1, y1 = extendGCD(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return gcd, x, y

num1 = 381723029127918237717233210002
num2 = 23812188332813212739187261
result = extendGCD(num1, num2)
print(result)