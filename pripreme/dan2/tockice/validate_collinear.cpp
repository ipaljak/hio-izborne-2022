#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 1e5 + 10;

int n;
int x[MAXN], y[MAXN];

void fail() {
  printf("Validation failed!");
  exit(0);
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d%d", &x[i], &y[i]);

  unordered_set<pair<double, double>> lines;
  unordered_set<int> vertical;

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (x[i] == x[j]) {
        if (vertical.find(x[i]) != vertical.end()) fail();
        vertical.insert(x[i]);
        continue;
      }

    }
  }

  printf("Validation successful!");
  return 0;
}
