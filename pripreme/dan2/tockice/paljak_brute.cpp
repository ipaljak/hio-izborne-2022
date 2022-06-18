#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;

int n, m;
int x[MAXN], y[MAXN];
int memo[1 << 21];

vector<pair<int, int>> E;

vector<int> v[MAXN * MAXN];

bool ccw(int xa, int ya, int xb, int yb, int xc, int yc) {
  return (long long)xa * (yb - yc) + (long long)xb * (yc - ya) + (long long)xc * (ya - yb) > 0;
}

bool intersect(int i, int j) {
  int a = E[i].first, b = E[i].second, c = E[j].first, d = E[j].second;
  if (a == c || a == d || b == c || b == d) return false;
  return ccw(x[a], y[a], x[b], y[b], x[c], y[c]) !=
             ccw(x[a], y[a], x[b], y[b], x[d], y[d]) &&
         ccw(x[c], y[c], x[d], y[d], x[a], y[a]) !=
             ccw(x[c], y[c], x[d], y[d], x[b], y[b]);
}

bool rek(int mask) {
  if (memo[mask] != -1) return memo[mask];
  if (__builtin_popcount(mask) == m) return memo[mask] = false;
  for (int i = 0; i < m; ++i) {
    if ((mask & (1 << i))) continue;
    int _mask = mask | (1 << i);
    for (int j : v[i]) _mask |= (1 << j);
    if (!rek(_mask)) return memo[mask] = true;
  }
  return memo[mask] = false;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);

  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      E.emplace_back(i, j);

  m = (int)E.size();
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      if (intersect(i, j)) {
        v[i].push_back(j);
        v[j].push_back(i);
      }
    }
  }

  memset(memo, -1, sizeof memo);
  if (rek(0))
    printf("Alenka\n");
  else
    printf("Bara\n");

  return 0;
}
