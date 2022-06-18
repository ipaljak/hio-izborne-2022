#include <bits/stdc++.h>

using namespace std;

int n;

vector<pair<int, int>> Q;

bool ccw(const pair<int, int> &A, const pair<int, int> &B,
         const pair<int, int> &C) {
  return (long long)A.first * (B.second - C.second) + (long long)B.first * (C.second - A.second) +
         (long long)C.first * (A.second - B.second) > 0;
}

vector<pair<int, int>> chain(vector<pair<int, int>> &P) {
  vector<pair<int, int>> ret;
  for (int i = 0; i < n; ++i) {
    while ((int)ret.size() >= 2 &&
           !ccw(ret[ret.size() - 2], ret[ret.size() - 1], P[i]))
      ret.pop_back();
    ret.emplace_back(P[i]);
  }
  ret.pop_back();
  return ret;
}

vector<pair<int, int>> hull(vector<pair<int, int>> &P) {
  sort(P.begin(), P.end());
  auto L = chain(P);
  reverse(P.begin(), P.end());
  auto U = chain(P);
  auto hull = move(L);
  hull.insert(hull.end(), make_move_iterator(U.begin()),
              make_move_iterator(U.end()));
  return hull;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    Q.emplace_back(x, y);
  }

  auto H = hull(Q);
  int cnt = 3 * n - (int)H.size() - 3;

  if (cnt & 1)
    printf("Alice\n");
  else
    printf("Bob\n");

  return 0;
}
