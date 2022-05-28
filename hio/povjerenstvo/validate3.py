#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
from queue import Queue

import sys

sys.setrecursionlimit(50000000)

MAXN = 5 * 10**5
MAXM = 5 * 10**5

def scc(e):
    n = len(e)
    vis = [False for _ in range(n)]
    rev_e = [[] for _ in range(n)]
    for x in range(n):
        for y in e[x]:
            rev_e[y].append(x)
    order = []

    def dfs1(x):
        vis[x] = True
        for y in e[x]:
            if not vis[y]:
                dfs1(y)
        order.append(x)

    for x in range(n):
        if not vis[x]:
            dfs1(x)

    vis = [False for _ in range(n)]
    order = order[::-1]
    component = [None for _ in range(n)]
    cur_component = 0

    def dfs2(x):
        vis[x] = True
        component[x] = cur_component
        for y in rev_e[x]:
            if not vis[y]:
                dfs2(y)

    for x in order:
        if not vis[x]:
            dfs2(x)
            cur_component += 1

    return component

def is_dag(e):
    return len(set(scc(e))) == len(e)

def is_bipartite(e):
    n = len(e)
    color = [0 for _ in range(n)]
    bipartite = True

    def dfs(x):
        for y in e[x]:
            if color[y] == 0:
                color[y] = -color[x]
                dfs(y)
            elif color[y] == color[x]:
                nonlocal bipartite
                bipartite = False

    for x in range(n):
        if color[x] == 0:
            color[x] = 1
            dfs(x)

    return bipartite

def has_odd_dir_cycle(e):
    n = len(e) // 2
    component = scc(e)
    for i in range(n):
        if component[i] == component[i + n]:
            return True
    return False

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending


    n, m = map(int, lines[0].split())
    assert 1 <= n <= MAXN, "n kriv"
    assert 0 <= m <= MAXM, "m kriv"
    nl.append("{} {}{}".format(n, m, E));


    edges = [[] for _ in range(n)]
    undir_edges = [[] for _  in range(n)]
    double_edges = [[] for _  in range(2 * n)]

    bridovi = set()
    for i in range(1, m + 1):
        a, b = map(int, lines[i].strip().split())
        nl.append("{} {}{}".format(a, b, E))

        assert 1 <= a <= n, "prvi cvor nije iz [1, n]"
        assert 1 <= b <= n, "drugi cvor nije iz [1, n]"
        assert a != b, "isti cvorovi"

        assert (a, b) not in bridovi, "dupli edge"
        bridovi.add((a, b))

        a -= 1
        b -= 1
        edges[a].append(b)
        undir_edges[a].append(b)
        undir_edges[b].append(a)
        double_edges[a].append(b + n)
        double_edges[a + n].append(b)

    assert not has_odd_dir_cycle(double_edges), "neparni krug"

    dag = is_dag(edges)
    bipartite = is_bipartite(undir_edges)

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'm' : m, 'dag': dag, 'bipartite': bipartite}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'subtask 1': 1, 'subtask 2': 1, 'subtask 3': 1, 'subtask 4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 5000 and data['m'] <= 5000:
        return 'subtask 3'
    if data['dag']:
        return 'subtask 1'
    if data['bipartite']:
        return 'subtask 2'
    return 'subtask 4'


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
            #assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
            pass
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    #assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    #assert len(hashes) == len(f), "Ima duplikata!"
