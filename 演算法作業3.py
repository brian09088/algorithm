# Uses python3

import math
import re
def addPar(S):
    parts  = re.split("([\+\-\*])",S)  # split on operators (keep separators)
    if len(parts)==1: yield S;return   # no operation -> string itself
    for i in range(1,len(parts)-1,2):  # for each operation
        ls = "".join(parts[:i])        # left side operand
        rs = "".join(parts[i+1:])      # right side operand
        # recursively add parentheses...
        yield from (f"({L}{parts[i]}{R})" for L in addPar(ls) for R in addPar(rs))

string = input()
array = sorted(map(eval,addPar(string)))
length = len(array)
print(array[length-1])
for i in addPar(string):
    if(eval(i)==array[length-1]):
        print(i)