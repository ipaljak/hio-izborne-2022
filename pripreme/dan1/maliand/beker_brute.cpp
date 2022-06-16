#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;

vi sorted(int len, int ones) {
  vi res(len);
  fill(res.begin() + len - ones, res.end(), 1);
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
  
  int ans = N + 1;
  vector <int> opt_a, opt_b;
  vector <int> a = sorted(N, K);
  do {
    vector <int> b = sorted(N, L);
    do {
      int mask_a = 0, mask_b = 0;
      for (int i = 0; i < N; i++) {
        mask_a |= a[i] << i;
        mask_b |= b[i] << i;
      }
      int maks = 0;
      for (int i = 0; i < N; i++) {
        maks = max(maks, __builtin_popcount(mask_a & mask_b));
        mask_b = ((mask_b & 1) << N - 1) | (mask_b >> 1);
      }
      if (maks < ans) {
        ans = maks;
        opt_a = a;
        opt_b = b;
      }
    } while (next_permutation(b.begin(), b.end()));
  } while (next_permutation(a.begin(), a.end()));
  
  printf("%d\n", ans);
  output(opt_a);
  output(opt_b);
  
  return 0;
}
     
