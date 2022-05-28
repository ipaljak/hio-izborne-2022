#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long

using namespace std;

struct edge {
  int y;
  int a, b;
};

const int MAXN = 50000;
vector <edge> ve[MAXN];
int sol[MAXN];
bitset <MAXN> bs[MAXN];

void dfs(int x, int par) {
  sol[x] = bs[x].count();

  for (auto tr : ve[x]) {
    if (tr.y == par) continue;

    bitset <MAXN> tmp;
    tmp.set();
    tmp <<= tr.a;
    tmp >>= tr.a;
    tmp >>= (MAXN - tr.b - 1);
    tmp <<= (MAXN - tr.b - 1);

    bs[tr.y] = (bs[x] | tmp);

    dfs(tr.y, x);
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