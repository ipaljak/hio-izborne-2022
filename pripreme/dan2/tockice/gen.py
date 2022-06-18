#!/usr/bin/python2

import itertools
import math
import subprocess
import random
import os
import glob
import sys
import collections

doc = """
  Cenerate all test cases in test/:  gen.py
"""

PROBLEM = "tockice"
sys.setrecursionlimit(1000010)

MAXN = 3*10**5


class Test(object):
    def __init__(self, n, xs, ys):
        self.n = n    # number of points
        self.xs = xs  # x coordinates
        self.ys = ys  # y coordinates

    def validate_colinear(self):
        if self.n > 1000:
            print("Validation skipped!")
            return True
        lines = set()
        vertical = set()
        for i in range(self.n):
            for j in range(i + 1, self.n):
                if self.xs[i] == self.xs[j]:
                    if self.xs[i] in vertical:
                        return False
                    vertical.add(self.xs[i])
                    continue
                a = float(self.ys[j] - self.ys[i]) / \
                    float(self.xs[j] - self.xs[i])
                b = float(self.ys[i]) - a * float(self.xs[i])
                if (a, b) in lines:
                    return False
                lines.add((a, b))

        return True

    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(len(self.xs) == self.n)
        assert(len(self.ys) == self.n)
        for x in self.xs:
            assert(abs(x) <= 10**6)
        for y in self.ys:
            assert(abs(y) <= 10**6)
        P = set()
        for i in range(self.n):
            P.add((self.xs[i], self.ys[i]))
        assert(len(P) == self.n)
        assert(self.validate_colinear())

    def write(self, fd=sys.stdout):
        print>>fd, self.n
        for i in range(self.n):
            print>>fd, "{} {}".format(self.xs[i], self.ys[i])


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_rand(n, max_c):
    xs = []
    ys = []
    for i in range(n):
        xs.append(random.randint(-max_c, max_c))
        ys.append(random.randint(-max_c, max_c))
    return Test(n, xs, ys)


def gen_large(n):
    xs = []
    ys = []
    a = random.randint(1, n - 1)
    b = random.randint(1, n - 1)
    for i in range(n):
        xs.append(i)
        ys.append((a * i * i + b * i) % n)
    return Test(n, xs, ys)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4,
        [0, 0, 10, 10],
        [0, 10, 0, 10],
    ))

    dummy.append(Test(
        5,
        [2, 1, 6, 3, 5],
        [1, 3, 4, 5, 2],
    ))

    dummy.append(Test(
        4,
        [4, 2, 2, 1],
        [2, 4, 2, 1],
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1 <= n <= 7
    subtask1 = []
    for i in range(1, 8):
        for j in range(10):
            subtask1.append(gen_rand(i, 100))
            if i <= 3:
                break
            if i <= 5 and j == 5:
                break

    real.append(subtask1)

    # 1 <= n <= 300
    subtask2 = []
    for i in range(30):
        subtask2.append(gen_rand(300, 1000000))

    real.append(subtask2)

    # 1 <= n <= 1000
    subtask3 = []
    for i in range(30):
        subtask3.append(gen_rand(1000, 1000000))

    real.append(subtask3)

    # 1 <= n <= 100 000
    subtask4 = []
    for n in [99793, 99809, 99817, 99823, 99829, 99833, 99839, 99859, 99871, 99877, 99881, 99901, 99907, 99923, 99929, 99961, 99971, 99989, 99991]:
        for _ in range(2):
            subtask4.append(gen_large(n))

    real.append(subtask4)

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c%c' \
                % (PROBLEM, i+1, chr(ord('a')+(j/26)), chr(ord('a')+(j % 26)))
            input = 'test/%s.in.%d%c%c' % (PROBLEM, i+1,
                                           chr(ord('a')+(j/26)), chr(ord('a')+(j % 26)))
            test.write(file(input, 'wt'))


def main():
    random.seed(293489)
    gen_cases()


if __name__ == "__main__":
    main()
