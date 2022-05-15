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

const char CHAR_0 = 'A', CHAR_1 = 'B';
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

  // Read contestant's output
  vector<vector<int>> cnt(1 << n, vector<int>(2));
  for (int i = 0; i < n; i++) {
      string s;
      if (!(fout >> s)) finish(0);
      if ((int)s.size() != (1 << n - 1)) finish(0);

      int mask_A = (1 << n - 1 - i) - 1, mask_B = ((1 << i) - 1) << n - 1 - i;
      for (int j = 0; j < (1 << n - 1); j++) {
          if (s[j] != CHAR_0 && s[j] != CHAR_1) finish(0);

          int hat = s[j] == CHAR_1;
          int scene = (j & mask_A) ^ (hat << n - 1 - i) ^ ((j & mask_B) << 1);
          cnt[scene][hat]++;
      }
  }
  string garbage;
  if (fout >> garbage) finish(0);

  // Check contestant's solution
  for (int i = 0; i < (1 << n); i++) {
      int total_1 = __builtin_popcount(i), total_0 = n - total_1;
      if (cnt[i][0] < total_0 / 2) finish(0);
      if (cnt[i][1] < total_1 / 2) finish(0);
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
