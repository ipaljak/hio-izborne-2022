#!/usr/bin/python2

import math
import subprocess
import random
import os
import glob
import sys
doc = """
  Cenerate all test cases in test/:  gen.py
"""


PROBLEM = "mensza"


MAXL = 200
MAXQ = 1000000


n_dict = {200: 100, 75: 1000, 20: 500000}


class Test(object):
    def __init__(self, l, q, qs):
        self.l = l
        self.q = q
        self.qs = qs


    def validate(self):
        assert(self.l in [20, 75, 200])
        if self.l == 20:
            assert(1 <= self.q <= 10**6)
        if self.l == 75:
            assert(1 <= self.q <= 10**6)
        if self.l == 200:
            assert(1 <= self.q <= 10**4)

        assert(len(self.qs) == self.q)
        for qi in self.qs:
            line = qi.split()
            assert(line[0] in ['alojzije', 'benjamin', 'cecilija'])
            if line[0] in ['alojzije', 'benjamin']:
                assert(len(line) == 2)
                assert(int(line[1]) <= n_dict[self.l])
            else:
                cl = int(line[1])
                assert(len(line) == cl + 2)
                assert(0 <= cl <= n_dict[self.l])
                for i in range(cl):
                    assert(int(line[2 + i]) <= 2 * n_dict[self.l])


    def write(self, fd=sys.stdout):
        print>>fd, self.l
        print>>fd, self.q
        for qi in self.qs:
            print>>fd, qi


class Config(object):
    def __init__(self, n, q, qs):
        self.n = n
        self.q = q
        self.qs = qs


    def validate(self):
        assert(self.n in [100, 1000, 500000])
        if self.n == 100:
            assert(1 <= self.q <= 10000)
        else:
            assert(1 <= self.q <= 1000000)
        assert(len(self.qs) == self.q)
        for (i, j) in self.qs:
            assert(0 <= (i - 1) / 2 < self.n)
            assert(0 <= (j - 2) / 2 < self.n)
            assert((i - 1) / 2 != (j - 2) / 2)


    def write(self, fd=sys.stdout):
        print>>fd, self.q
        for (i, j) in self.qs:
            print>>fd, i, j


def remove_cases():
    cases = glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.config.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_test(n, l):
    q = 2 * n
    qs = []
    for i in range(n):
        qs.append("alojzije " + str(i + 1))
        qs.append("benjamin " + str(i + 1))
    return Test(l, q, qs)


def gen_conf(n):
    qs = []
    if n <= 1000:
        for i in range(n):
            for j in range(n):
                if i == j: continue
                qs.append((2 * i + 1, 2 * j + 2))
    else:
        for _ in range(50):
            l = random.randint(0, n - 110)
            r = l + 100
            for i in range(l, r):
                for j in range(l, r):
                    if i == j: continue
                    qs.append((2 * i + 1, 2 * j + 2))
        while len(qs) != 1000000:
            i = random.randint(0, n - 1)
            j = random.randint(0, n - 1)
            if i == j: continue
            qs.append((2 * i + 1, 2 * j + 2))
    return Config(n, len(qs), qs)


def gen_cases():
    remove_cases()

    # 1. subtask -- n = 100, l = 200, q <= 10 000
    subtask1 = [gen_test(100, 200)]
    conf1 = [gen_conf(100)]

    # 2. subtask -- n = 1 000, l = 75, q <= 1 000 000
    subtask2 = [gen_test(1000, 75)]
    conf2 = [gen_conf(1000)]

    # 3. subtask -- n = 500 000, l = 20, q <= 1 000 000
    subtask3 = [gen_test(500000, 20)]
    conf3 = [gen_conf(500000)]

    real = [subtask1, subtask2, subtask3]
    config = [conf1, conf2, conf3]

    for i, batch in enumerate(real):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.in.%d%c' \
                % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.in.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))

    for i, batch in enumerate(config):
        for j, test in enumerate(batch):
            test.validate()
            print>>sys.stderr, 'Generating test/%s.config.%d%c' \
                % (PROBLEM, i+1, chr(ord('a')+j))
            input = 'test/%s.config.%d%c' % (PROBLEM, i+1, chr(ord('a')+j))
            test.write(file(input, 'wt'))


def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()
