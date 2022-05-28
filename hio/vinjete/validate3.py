#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
from queue import Queue

import sys

sys.setrecursionlimit(500000)

MAXN = 10**5

edges = []
bio = []

def dfs(x):
    q = []
    q.append(0)
    bio[0] = 1

    while (len(q) > 0):
        x = q.pop(-1)
        for y in edges[x]:
            if (bio[y]):
                continue;
            q.append(y)
            bio[y] = 1
        

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending


    n= int(lines[0].strip())
    assert 1 <= n <= 100000, "n kriv"
    nl.append("{}{}".format(n, E));


    global edges
    edges = []
    for i in range(0, n):
        edges.append([])

    global bio
    bio = []
    for i in range(0, MAXN):
        bio.append(0)

    bridovi = set()
    max_cost = 0
    for i in range(1, n):
        x, y, a, b = map(int, lines[i].strip().split())
        nl.append("{} {} {} {}{}".format(x, y, a, b, E))

        assert 1 <= x <= n, "prvi cvor nije iz [1, n]"
        assert 1 <= y <= n, "drugi cvor nije iz [1, n]"
        assert 1 <= a <= 10**9, "krivi interval"
        assert 1 <= b <= 10**9, "krivi interval"
        assert a <= b, "krivi interval order"
        assert x != y, "isti cvorovi"

        #max_cost = max(max_cost, a)
        max_cost = max(max_cost, b)

        x, y = min(x, y), max(x, y)
        assert (x, y) not in bridovi, "dupli edge"
        bridovi.add((x, y))

        edges[x - 1].append(y - 1)
        edges[y - 1].append(x - 1)

    
    dfs(0)
    for i in range(0, n):
        assert bio[i] == 1, "nije povezano stablo"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'max_cost' : max_cost}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'n 1000, cost 1000' : 1, 'n 1000, cost 1e9': 1, 'n 50000, cost 50000' : 1, 'n 100000, cost 100000' : 1, 'normalni' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if (data['n'] <= 1000 and data['max_cost'] <= 1000):
        return 'n 1000, cost 1000'
    if (data['n'] <= 1000):
        return 'n 1000, cost 1e9'
    if (data['n'] <= 50000 and data['max_cost'] <= 50000):
        return 'n 50000, cost 50000'
    if (data['n'] <= 100000 and data['max_cost'] <= 100000):
        return 'n 100000, cost 100000'
    
    return 'normalni'

################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if f[-1].islower() and len(B) > 0 and f[:-1] == B[-1][-1][:-1]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

    clusters = {}
    for b in bc:
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
