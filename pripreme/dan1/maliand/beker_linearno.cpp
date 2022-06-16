#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector <int> vi;

int answer(int n, int k, int l) {
  return ((ll)k * l + n - 1) / n;
}

vi ones_first(int n, int m) {
  vi res(m, 1);
  res.resize(n);
  return res;
}

vi pos_to_str(int n, const vi &zeroes) {
  vi res(n, 1);
  for (auto it : zeroes)
    res[it] = 0;
  return res;
}

vi str_to_pos(const vi &v) {
  vi res;
  for (int i = 0; i < v.size(); i++)
    if (!v[i])
      res.push_back(i);
  return res;
}

vi solve(int n, int k, int l) {
  if (!k || !l || k == n || l == n) 
    return str_to_pos(ones_first(n, l));
  vi nxt = solve(l, answer(n, k, l), l - n % l);
  if (l > n / 2) {
    for (int i = 0; i < nxt.size(); i++) 
      nxt[i] += i + 1;
    return nxt;
  }
  int pref = 0;
  vi curr(n), arr = pos_to_str(l, nxt);
  for (auto it : arr) {
    curr[pref] = 1;
    pref += n / l + 1 - it;
  }
  return str_to_pos(curr);
}

void output(const vi &v) {
  for (auto it : v)
    printf("%d", it);
  puts("");
}

int main() {
  int N, K, L;
  scanf("%d%d%d", &N, &K, &L);
  printf("%d\n", answer(N, K, L));
  output(ones_first(N, K));
  output(pos_to_str(N, solve(N, K, L)));
  return 0;
}
