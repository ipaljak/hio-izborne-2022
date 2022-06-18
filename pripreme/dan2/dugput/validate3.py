#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    q = int(lines[0].strip())
    assert 1 <= q <= 100, "q kriv"
    nl.append("{}{}".format(q, E));

    max_nm = 0
    max_m = 0
    for i in range(q):
        n, m, a, b, c, d = map(int, lines[i+1].split())
        assert 1 <= n <= 5000, "n kriv" 
        assert 1 <= m <= 5000, "m kriv" 
        assert 1 <= a <= n, "a kriv"
        assert 1 <= b <= m, "b kriv"
        assert 1 <= c <= n, "c kriv"
        assert 1 <= d <= m, "d kriv"
        assert (a, b) != (c, d), "(a,b) = (c,d)"

        max_nm = max(max_nm, n*m)
        max_m = max(max_m, m)

        nl.append("{} {} {} {} {} {}{}".format(n, m, a, b, c, d, E))

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'nm': max_nm, 'm': max_m}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2': 1, 's3': 1, 's4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if 2 <= data['nm'] <= 100: return 's1'
    if 2 <= data['nm'] <= 1000: return 's2'
    if 2 <= data['nm'] <= 1000000 and data['m'] <= 3: return 's3'
    if 2 <= data['nm'] <= 1000000: return 's4'
    assert False, "nijedan cluster"


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
