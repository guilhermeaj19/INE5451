
"""
Since most computers are binary machines, both powers of two and problems that involve only two values are important to computer scientists. The following problem has to do with powers of two and the digits 1 and 2.

Some powers of two as decimal values, such as 29 = 512 and 289 = 618,970,019,642,690,137,449,562,112 end in a string of digits consisting only of 1's and 2's (12 for 29 and 2112 for 289). In fact, it can be proved that:

For every integer R, there exists a power of 2 such that 2K uses only the digits 1 and 2 in its last R digits.

Your job is to write a program that will determine, for given R, the smallest K such that 2K ends in a string of R digits containing only 1's and 2's.
Input
The first line of the input contains a single decimal integer, N, 1 <= N <= 50, the number of problem data sets to follow. Each data set consists of a single integer R, 1 <= R <= 20, for which we want a power of 2 ending in a string of R 1's and 2's.
Output
For each data set, you should generate one line of output with the following values: The data set number as a decimal integer (start counting at one), a space, the input value R, another space, and the smallest value K for which 2K ends in a string of R 1's and 2's.
"""


smallest_k = [1]
two_k = [2]

def precompute():
    for k in range(1, 10**6):
        two_k.append((two_k[-1] * 2) % (10 ** 20))
        if all(c in '12' for c in str(two_k[-1])):
            smallest_k.append(k)
            print(f"Found K={k} with 2^K={two_k[-1]}")

precompute()
for _ in range(int(input())):
    R = int(input())
    print(smallest_k[R - 1])