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

set <pair <int, int> > se;
int sol[OFF];

void dfs(int x, int par) {
  int val = 0, la = 0;
  for (auto tr : se) {
    if (tr.first != la) {
      sol[x] += (tr.first - la) * (val > 0);
      la = tr.first;
    }
    if (tr.second == 0) val++;
    else                val--;
  }

  for (auto tr : ve[x]) {
    if (tr.y == par) continue;

    se.insert({tr.a, 0});
    se.insert({tr.b + 1, 1});

    dfs(tr.y, x);

    se.erase({tr.a, 0});
    se.erase({tr.b + 1, 1});
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