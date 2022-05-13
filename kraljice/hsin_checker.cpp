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

void finish(double score) {
  cout << score << endl;
  exit(0);
}

void finish(llint points_awarded, llint points_max) {
  cout << points_awarded << "/" << points_max << endl;
  exit(0);
}

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream &fin, ifstream &foff, ifstream &fout) {
  // Read official input
  int n;
  if (!(fin >> n)) finish(0);

  // Read official output
  int off_k;
  if (!(foff >> off_k)) finish(0);

  // Read contestant's output
  int out_k;
  if (!(fout >> out_k)) finish(0);

  vector<pair<int, int>> out_sol(out_k);
  for (int i = 0; i < out_k; i++) {
    if (!(fout >> out_sol[i].first)) finish(0);
    if (!(fout >> out_sol[i].second)) finish(0);
  }
  string garbage;
  if (fout >> garbage) finish(0);

  // Check contestant's solution
  if (out_k != off_k) finish(0);

  vector<int> cnt_row(n), cnt_col(n), cnt_diag1(2 * n), cnt_diag2(2 * n);
  vector<vector<bool>> taken(n, vector<bool>(n));
  for (auto& [x, y] : out_sol) {
      if (!(1 <= x && x <= n && 1 <= y && y <= n)) finish(0);
      if (taken[x - 1][y - 1]) finish(0);

      int cnt = cnt_row[x - 1]
              + cnt_col[y - 1]
              + cnt_diag1[x + y - 1]
              + cnt_diag2[x - y + n];
      if (cnt % 2 != 0) finish(0);

      taken[x - 1][y - 1] = true;
      cnt_row[x - 1]++;
      cnt_col[y - 1]++;
      cnt_diag1[x + y - 1]++;
      cnt_diag2[x - y + n]++;
  }

  finish(1);

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
