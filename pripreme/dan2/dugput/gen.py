#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "dugput"
sys.setrecursionlimit(1000010)

class Test(object):
    def __init__(self, q, qs):
        self.q = q
        self.qs = qs

    def validate(self):
        assert(1 <= self.q <= 100)
        assert(len(self.qs) == self.q)

        for (ni, mi, ai, bi, ci, di) in self.qs:
            assert(1 <= ni <= 5000)
            assert(1 <= mi <= 5000)
            assert(1 <= ni * mi <= 10**6)
            for c in [ai, ci]:
                assert(1 <= c <= ni)
            for c in [bi, di]:
                assert(1 <= c <= mi)
            assert(ai != ci or bi != di)


    def write(self, fd=sys.stdout):
        print>>fd, self.q
        for (ni, mi, ai, bi, ci, di) in self.qs:
            print>>fd, ni, mi, ai, bi, ci, di


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)

def gen_s(n_lo, n_hi, m_lo, m_hi, mul=10**6):
    qs = []
    while len(qs) < 100:
        n = random.randint(n_lo, n_hi)
        m = random.randint(m_lo, m_hi)
        if n * m > mul:
            if random.randint(1, 2) == 1:
                n = mul / m
            else:
                m = mul / n
        if m != 3 and random.randint(1, 4) == 1:
            m = random.randint(1, 3)
            n = mul / m
        n = min(n, 5000)
        m = min(m, 5000)
        corner = [(1, 1), (1, m), (n, 1), (n, m)]
        border = []

        for i in range(1, n + 1):
            if (i, 1) not in corner: border.append((i, 1))
            if (i, m) not in corner: border.append((i, m))

        for i in range(1, m + 1):
            if (1, i) not in corner: border.append((1, i))
            if (n, i) not in corner: border.append((n, i))

        while True:
            (a, b) = corner[random.randint(0, len(corner) - 1)]
            (c, d) = corner[random.randint(0, len(corner) - 1)]
            if a == c and b == d: continue
            qs.append((n, m, a, b, c, d))
            break

        for _ in range(2):
            while True:
                (a, b) = border[random.randint(0, len(border) - 1)]
                (c, d) = border[random.randint(0, len(border) - 1)]
                if a == c and b == d: continue
                qs.append((n, m, a, b, c, d))
                break

        for _ in range(2):
            (a, b) = corner[random.randint(0, len(corner) - 1)]
            (c, d) = border[random.randint(0, len(border) - 1)]
            qs.append((n, m, a, b, c, d))

        if min(n, m) < 3:
            for _ in range(4):
                while True:
                    (a, b) = border[random.randint(0, len(border) - 1)]
                    (c, d) = border[random.randint(0, len(border) - 1)]
                    if a == c and b == d: continue
                    qs.append((n, m, a, b, c, d))
                    break
            continue

        for l in [corner, border]:
            (a, b) = l[random.randint(0, len(l) - 1)]
            (c, d) = (random.randint(2, n - 1), random.randint(2, m - 1))
            qs.append((n, m, a, b, c, d))

        for _ in range(2):
            while True:
                (a, b) = (random.randint(2, n - 1), random.randint(2, m - 1))
                (c, d) = (random.randint(2, n - 1), random.randint(2, m - 1))
                if a == c and b == d: continue
                qs.append((n, m, a, b, c, d))
                while True:
                    da = random.randint(-1, 1)
                    db = random.randint(-1, 1)
                    if m != 3:
                        da = random.randint(-3, 3)
                        db = random.randint(-3, 3)
                    c = a + da
                    d = b + db
                    if (a == c and b == d) or c < 1 or c > n or d < 1 or d > m: continue
                    qs.append((n, m, a, b, c, d))
                    break
                break

    qs = qs[:100]
    return Test(100, qs)

def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1,
        [(5, 5, 1, 1, 5, 5)]
    ))

    dummy.append(Test(
        2,
        [(2, 3, 1, 1, 2, 2),
         (7, 9, 4, 4, 5, 5)]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 1. subtask nm <= 100, q = 100
    subtask1 = []
    for i in range(8):
        subtask1.append(gen_s(1, 50, 1, 50, 100))

    real.append(subtask1)

    # 2. subtask nm <= 1000, q = 100
    subtask2 = []
    for i in range(8):
        subtask2.append(gen_s(1, 1000, 1, 1000, 1000))

    real.append(subtask2)

    # 3. subtask -- n <= 5000, m = 3, q = 100
    subtask3 = []
    for i in range(8):
        if i < 7:
            subtask3.append(gen_s(100 * i, 5000, 3, 3, 15000))
        else:
            subtask3.append(gen_s(5000, 5000, 3, 3, 15000))

    real.append(subtask3)

    # 4. subtask nm <= 10**5, q = 100
    subtask4 = []
    for i in range(8):
        subtask4.append(gen_s(1, 5000, 1, 5000, 10**5))

    real.append(subtask4)

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                    % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))

def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()

