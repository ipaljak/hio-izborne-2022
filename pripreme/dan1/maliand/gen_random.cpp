#include <bits/stdc++.h>
using namespace std;

mt19937 rng;

int get_rand(int a, int b) { // [a, b]
  return uniform_int_distribution <int> (a, b)(rng);
}

int main(int argc, char *argv[]) {
  int param = atoi(argv[1]);
  int MAXN = atoi(argv[2]);
  rng.seed(param == -1 ? chrono::steady_clock::now().time_since_epoch().count() : param);
  int N = get_rand(1, MAXN);
  int K = get_rand(0, N);
  int L = get_rand(0, N);
  printf("%d %d %d\n", N, K, L);
  return 0;
}
