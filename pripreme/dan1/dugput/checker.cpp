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
#include <queue>

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

void finish(double score, string message) {
  cout << score << endl;
  cout << message << endl;
  exit(0);
}

void finish(llint points_awarded, llint points_max) {
  cout << points_awarded << "/" << points_max << endl;
  exit(0);
}

void checker(ifstream& fin, ifstream& foff, ifstream& fout, ifstream& fconf)
{
  const string PANIC = "Correct.";
  bool panic = false;

  int T;
  if (!(fin >> T)) finish(0);

  double score = 1;
  REP(bla, T) {
    // Read official input
    int n, m;
    if (!(fin >> n >> m)) finish(0);
    int sx, sy;
    if (!(fin >> sx >> sy)) finish(0);
    sx--, sy--;
    int tx, ty;
    if (!(fin >> tx >> ty)) finish(0);
    tx--, ty--;
    //cout << "procitalo input\n";

    // Read contestant's output
    int N = 2 * n - 1, M = 3 * m - 2;
    vector<string> G(N);
    for (auto& row : G) {
        getline(fout, row);
        if ((int)row.size() != M) finish(0);
    }
    //cout << "procitalo output\n";

    // Check if output is a valid graph
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i % 2 == 0) {
                if (j % 3 == 0 && G[i][j] != 'o'&& G[i][j] != '*') finish(0);
                if (j % 3 == 1 && G[i][j] != G[i][j + 1]) finish(0);
                if (j % 3 != 0 && G[i][j] != '-' && G[i][j] != ' ') finish(0);
            } else {
                if (j % 3 == 0 && G[i][j] != '|' && G[i][j] != ' ') finish(0);
                if (j % 3 != 0 && G[i][j] != ' ') finish(0);
            }
        }
    }

    //cout << "valid graph\n";

    // Check if output is a valid graph
    vector<vector<int>> deg(N, vector<int>(M, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int cnt = 0;
        if (i < n - 1 && G[i * 2 + 1][j * 3] == '|') cnt++;
        if (i > 0 && G[i * 2 - 1][j * 3] == '|') cnt++;
        if (j < m - 1 && G[i * 2][j * 3 + 1] == '-') cnt++;
        if (j > 0 && G[i * 2][j * 3 - 1] == '-') cnt++;

        // ovdje provjeravamo:
        // * ima deg 1 i o ima deg 0 ili 2
        // pocetak i kraj su * a ostali o
        if (G[i * 2][j * 3] == '*') {
          if (cnt != 1) finish(0);
          if ((i != sx || j != sy) && (i != tx || j != ty)) finish(0);
        } else {
          if (cnt != 0 && cnt != 2) finish(0);
          if ((i == sx && j == sy) || (i == tx && j == ty)) finish(0);
        }

        deg[i][j] = cnt;
      }
    }

   //cout << "valid graph2\n";
    // Find path length
    vector<vector<int>> vis(N, vector<int>(M, 0));
    queue<pair<int, int>> Q;
    Q.push({sx, sy});
    vis[sx][sy] = 1;
    while (!Q.empty()) {
      int i = Q.front().first, j = Q.front().second;
      Q.pop();

      if (i > 0) {
        if (G[i * 2 - 1][j * 3] == '|' && vis[i - 1][j] == 0) {
          vis[i - 1][j] = vis[i][j] + 1;
          Q.push({i - 1, j});
        }
      }
      if (i < n - 1) {
        if (G[i * 2 + 1][j * 3] == '|' && vis[i + 1][j] == 0) {
          vis[i + 1][j] = vis[i][j] + 1;
          Q.push({i + 1, j});
        }
      }
      if (j > 0) {
        if (G[i * 2][j * 3 - 1] == '-' && vis[i][j - 1] == 0) {
          vis[i][j - 1] = vis[i][j] + 1;
          Q.push({i, j - 1});
        }
      }
      if (j < m - 1) {
        if (G[i * 2][j * 3 + 1] == '-' && vis[i][j + 1] == 0) {
          vis[i][j + 1] = vis[i][j] + 1;
          Q.push({i, j + 1});
        }
      }
    }
    //cout << vis[tx][ty] << endl;
    if (vis[tx][ty] == 0) finish(0);

    // treba provjeriti da nije ispisan jos neki ciklus uz put
    // drugim rijecima, svi cvorovi s deg > 0 moraju biti posjeceni
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (deg[i][j] > 0 && vis[i][j] == 0) finish(0);

    int sol;
    if (!(fconf >> sol)) finish(0);

    if (sol < vis[tx][ty]) score = min(score, 1.0), panic = true;
    else if (sol == vis[tx][ty]) score = min(score, 1.0);
    else if (0.9 * sol <= vis[tx][ty]) score = min(score, 0.35);
    else score = 0;
  }
  string garbage;
  fout >> garbage;
  if (fout >> garbage) finish(0);

  if (score == 1 && panic) finish(1, PANIC);
  finish(score);
  // The function MUST terminate before this line via finish()!
}

int main(int argc, char *argv[]) {
  assert(argc >= 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  // Optional, uncomment when using the configuration file for additional
  // information about the testcase.
  ifstream fconf(argv[4]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout, fconf);

  // Checker must terminate via finish() before exiting!
  assert(false);

  return 0;
}
