#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m = map(int, lines[0].split())
    assert 2 <= n <= 300000, "n kriv"
    assert 0 <= m <= 300000, "m kriv"
    nl.append("{} {}{}".format(n, m, E));

    e = []
    for i in range(m):
        xi, yi = map(int, lines[i + 1].split())
        assert 1 <= xi <= n, "xi kriv"
        assert 1 <= yi <= n, "yi kriv"
        assert xi != yi, "xi == yi"
        e.append((xi, yi))
        nl.append("{} {}{}".format(xi, yi, E))

    q = int(lines[m + 1].strip())
    assert 1 <= q <= 300000, "q kriv"
    nl.append("{}{}".format(q, E))
    for i in range(q):
        ai, bi = map(int, lines[m + 2 + i].split())
        assert 1 <= ai <= n, "ai kriv"
        assert 1 <= bi <= n, "bi kriv"
        assert ai != bi, "ai == bi"
        nl.append("{} {}{}".format(ai, bi, E))

    dupli = m % 2 == 0
    for i in range(1, m, 2):
        dupli &= e[i] == e[i - 1]

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'm': m, 'q': q, 'dupli': dupli}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2': 1, 's3': 1, 's4': 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['q'] == 1: return 's1'
    if data['dupli']: return 's2'
    if data['n'] <= 5000 and data['m'] <= 5000: return 's3'
    return 's4'


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
