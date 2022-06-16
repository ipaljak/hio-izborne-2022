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

vi solve(int n, int k, int l) {
  if (!k || !l || k == n || l == n)
    return ones_first(n, l);
  int pref = 0;
  vi res(n), nxt = solve(l, answer(n, k, l), l - n % l);
  for (auto it : nxt) {
    res[pref] = 1;
    pref += n / l + 1 - it;
  }
  return res;
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
  output(solve(N, K, L));
  return 0;
}
