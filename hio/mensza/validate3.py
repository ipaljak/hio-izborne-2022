#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
from queue import Queue

import sys

sys.setrecursionlimit(500000)

def check(lines, lines_config):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending


    l = int(lines[0])
    q = int(lines[1])
    nl.append("{}{}".format(l, E));
    nl.append("{}{}".format(q, E));

    n = 0
    names = []
    nums = []
    for i in range(2, q + 2):
        name, num = lines[i].split()
        num = int(num)
        nl.append("{} {}{}".format(name, num, E))

        assert name == 'alojzije' or name == 'benjamin', 'ime je krivo' 
        assert num >= 1, 'broj nije prirodan'

        n = max(n, num)
        names.append(name)
        nums.append(num)

    q_config = int(lines_config[0])
    for i in range(1, q_config + 1):
        a, b = map(int, lines_config[i].split())

        assert names[a - 1] != names[b - 1], 'imena su ista'
        assert nums[a - 1] != nums[b - 1], 'brojevi su isti'

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'l': l, 'q': q, 'q_config': q_config}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'subtask 1': 1, 'subtask 2': 1, 'subtask 3': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if (data['n'] == 100 and data['l'] == 200 and 1 <= data['q'] <= 10000 and 1 <= data['q_config'] <= 10000):
        return 'subtask 1'
    if (data['n'] == 1000 and data['l'] == 110 and 1 <= data['q'] <= 1000000 and 1 <= data['q_config'] <= 1000000):
        return 'subtask 2'
    if (data['n'] == 500000 and data['l'] == 20 and 1 <= data['q'] <= 1000000 and 1 <= data['q_config'] <= 1000000):
        return 'subtask 3'
    return 'nije subtask'

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
            filename_config = filename.replace('.in.', '.config.')
            print("{}, {}: ".format(filename, filename_config), end="")
            try:
                lines = open(filename).readlines()
                lines_config = open(filename_config).readlines()
                summary = check(lines, lines_config)
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
