// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <math.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);

int ceil(int a, int b) { return (a - 1) / b + 1; }

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream& fin, ifstream& foff, ifstream& fout)
{
  const string WRONG_OUTPUT_FORMAT = "Krivo formatiran izlaz.";
  const string TEST_DATA_ERROR = "Greška u službenom ulazu ili izlazu.";
  const string WRONG = "Netočno.";
  const string CORRECT = "Točno.";
  const string PARTIAL = "Suboptimalno rješenje.";

  int T;
  if (!(fin >> T)) finish(0, TEST_DATA_ERROR);

  double score = 0.0;
  REP(bla, T) {
    // Read official input
    int n, m;
    if (!(fin >> n >> m)) finish(0, TEST_DATA_ERROR);
    int sx, sy;
    if (!(fin >> sx >> sy)) finish(0, TEST_DATA_ERROR);
    sx--, sy--;
    int tx, ty;
    if (!(fin >> tx >> ty)) finish(0, TEST_DATA_ERROR);
    tx--, ty--;

    // Read contestant's output
    int N = 2 * n - 1, M = 3 * m - 2;
    vector<string> G(N);
    for (auto& row : G) {
        getline(fout, row);
        if ((int)row.size() != M) finish(0, WRONG_OUTPUT_FORMAT);
    }

    // Check if output is a valid graph
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i % 2 == 0) {
                if (j % 3 == 0 && G[i][j] != 'o'&& G[i][j] != '*') finish(0, WRONG);
                if (j % 3 == 1 && G[i][j] != G[i][j + 1]) finish(0, WRONG);
                if (j % 3 != 0 && G[i][j] != '-' && G[i][j] != ' ') finish(0, WRONG);
            } else {
                if (j % 3 == 0 && G[i][j] != '|' && G[i][j] != ' ') finish(0, WRONG);
                if (j % 3 != 0 && G[i][j] != ' ') finish(0, WRONG);
            }
        }
    }

    //cout << "valid graph\n";

    // Check if output is a valid graph
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int cnt = 0;
        if (i < n - 1 && G[i * 2 + 1][j * 3] == '|') cnt++;
        if (i > 0 && G[i * 2 - 1][j * 3] == '|') cnt++;
        if (j < m - 1 && G[i * 2][j * 3 + 1] == '-') cnt++;
        if (j > 0 && G[i * 2][j * 3 - 1] == '-') cnt++;

        if (G[i * 2][j * 3] == '*') {
          if (cnt != 1) finish(0, WRONG);
        } else {
          if (cnt == 1) finish(0, WRONG);
          if (cnt == 3) finish(0, WRONG);
        }
      }
    }

   ///cout << "valid graph2\n";
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
    if (vis[tx][ty] == 0) finish(0, WRONG);

    int sol;
    if (!(foff >> sol)) finish(0, TEST_DATA_ERROR);

    if (sol == vis[tx][ty]) score += 2;
    if (sol * 0.9 <= vis[tx][ty]) score += 1;

  }
  string garbage;
  fout >> garbage;
  if (fout >> garbage) finish(0, WRONG_OUTPUT_FORMAT);

  if (score == 2 * T) finish(1, CORRECT);
  finish((double) score / (2 * T), PARTIAL);
  // The function MUST terminate before this line via finish()!
}

void finish(double p, const string& m) {
  cout << p << endl;
  cout << m << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  assert(argc == 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);
  assert(false); // checker must terminate via finish() before exiting!

  return 0;
}
