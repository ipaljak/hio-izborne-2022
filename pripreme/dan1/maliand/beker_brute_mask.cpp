#include <bits/stdc++.h>
using namespace std;

int N, K, L;

bool get_next(int &mask) {
  if (!mask)
    return false;
  int cpl = (mask | (mask & -mask) - 1) ^ (1 << N) - 1;
  if (!cpl)
    return false;
  int lobit = cpl & -cpl;
  int ones = __builtin_popcount(mask & (lobit >> 1) - 1);
  mask &= (lobit - 1) ^ (1 << N) - 1;
  mask |= (1 << ones) - 1 | lobit;
  return true;
}

void output(int mask) {
  for (int i = 0; i < N; i++)
    printf("%d", mask >> i & 1);
  puts("");
}

int main() {
  mt19937 rng;
  rng.seed(298301);

  scanf("%d%d%d", &N, &K, &L);
  
  int ans = N + 1;
  vector <pair <int, int>> opt;
  int mask_a = (1 << K) - 1;
  do {
    int mask_b = (1 << L) - 1;
    do {
      int maks = 0;
      for (int i = 0; i < N; i++) {
        maks = max(maks, __builtin_popcount(mask_a & mask_b));
        mask_b = ((mask_b & 1) << N - 1) | (mask_b >> 1);
      }
      if (maks <= ans) {
        if (maks < ans) {
          opt.clear();
          ans = maks;
        }
        opt.push_back({mask_a, mask_b});
      }
    } while (get_next(mask_b));
  } while (get_next(mask_a));
 
  printf("%d\n", ans);
  int pos = uniform_int_distribution <int> (0, (int)opt.size() - 1)(rng);
  output(opt[pos].first);
  output(opt[pos].second);
  return 0;
}
