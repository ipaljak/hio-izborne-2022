// Checker to be used by HSIN evaluator.
//
// This should *not* be used for CMS!
//
// Usage: [checker] [input] [official_output] [contestant_output] [configuration_file (optional)]
//
// Output (stdout):
//     Score.
//     Textual description (optional).
//
// Score should be output as an integer (0 or 1), or a real (between 0.0 and
// 1.0) or a fraction (between `0/1` and `1/1`, you don't have to
// simplify/reduce the fraction).

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

// Use one of the following functions to output the points to the contestant.
// The first accepts a double and outputs it.
// The second accepts a fraction and outputs it.

void finish(double score, string feedback){
  cout << score << endl << feedback << endl;
  exit(0);
}

void finish(llint points_awarded, llint points_max) {
  cout << points_awarded << "/" << points_max << endl;
  exit(0);
}

// Helper functions.

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */

void checker(ifstream &fin, ifstream &foff, ifstream &fout) {
    // Read official input

    int n, m;

    if (!(fin >> n)) finish(0, "Bad official input");
    if (!(fin >> m)) finish(0, "Bad official input");

    vector < pair <int, int> > v;

    for (int i = 0; i < m; i++) {
        int a, b;
        if (!(fin >> a)) finish(0, "Bad official input");
        if (!(fin >> b)) finish(0, "Bad official input");
        v.push_back({a, b});
    }

    // Read official output

    // Read contestant output

    int k;
    if (!(fout >> k)) finish(0, "Bad contestant output - not enough output");
    if (!(1 <= k && k <= n)) finish(0, "Bad contestant output - size not in range");

    vector <int> boja(n + 1), ima(n + 1);
    for (int i = 0; i < k; i++) {
        int idx;
        if (!(fout >> idx)) finish(0, "Bad contestant output - not enough output");
        if (!(1 <= idx && idx <= n)) finish(0, "Bad contestant output - node not in range");
        if (!(boja[idx] == 0)) finish(0, "Bad contestant output - repeated value");
        boja[idx] = 1;
    }

    int trash;
    if (fout >> trash) finish(0, "Bad contestant output - too many numbers");

    //Check if actually valid

    for (int i = 0; i < m; i++) {
        int a = v[i].first;
        int b = v[i].second;
        if (boja[a] == 1 && boja[b] == 1) finish(0, "Bad contestant output - wrong construction");
        if (boja[a] == 0 && boja[b] == 1) ima[a] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (boja[i] == 0 && ima[i] == 0) finish(0, "Bad contestant output - wrong construction");
    }

    finish(1, "AC");

    // The function MUST terminate before this line via finish()!
}

int main(int argc, char *argv[]) {
    assert(argc >= 4);

    ifstream fin(argv[1]);
    ifstream foff(argv[2]);
    ifstream fout(argv[3]);

    // Optional, uncomment when using the configuration file for additional
    // information about the testcase.
    // ifstream fconf(argv[4]);

    assert(!fin.fail() && !fout.fail());
    checker(fin, foff, fout);

    // Checker must terminate via finish() before exiting!
    assert(false);

    return 0;
}
