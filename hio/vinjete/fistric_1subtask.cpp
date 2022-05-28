#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long

using namespace std;

struct edge {
  int y;
  int a, b;
};

const int OFF = (1 << 17);
vector <edge> ve[OFF];

int bio[OFF], curr = 0;
int sol[OFF];

void dfs(int x, int par) {
  sol[x] = curr;

  for (auto tr : ve[x]) {
    if (tr.y == par) continue;

    vector <int> tmp;
    tmp.resize(tr.b - tr.a + 1);

    FOR(i, tr.a, tr.b + 1) {
      tmp[i - tr.a] = bio[i];
      if (bio[i] == 0) {
        bio[i] = 1;
        curr++;
      }
    }

    dfs(tr.y, x);

    FOR(i, tr.a, tr.b + 1) {
      if (tmp[i - tr.a] == 0) {
        bio[i] = 0;
        curr--;
      }
    }
  }

  return;
}

int main() {
  ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  REP(i, n - 1) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    x--, y--;
    ve[x].push_back({y, a, b});
    ve[y].push_back({x, a, b});
  }

  dfs(0, 0);
  REP(i, n) cout << sol[i] << " ";

  return 0;
}