#include <bits/stdc++.h>

using namespace std;

int l, q;

void alojzije() {
  int a;
  scanf("%d", &a);

  vector<int> ret;
  for (int i = 0; i < 20; ++i) {
    if ((a & (1 << i)) == 0) continue;
    for (int j = 0; j < 2 * i + 2; ++j)
      ret.push_back(2 * i + 2);
  }

  printf("%d", (int)ret.size());
  for (int x : ret) printf(" %d", x);
  printf("\n");
}

void benjamin() {
  int b;
  scanf("%d", &b);

  vector<int> ret;
  for (int i = 0; i < 20; ++i) {
    if ((b & (1 << i)) == 0) continue;
    for (int j = 0; j < 2 * i + 1; ++j)
      ret.push_back(2 * i + 1);
  }

  printf("%d", (int)ret.size());
  for (int x : ret) printf(" %d", x);
  printf("\n");
}

void cecilija() {
  int l;
  scanf("%d", &l);

  int a = 0, b = 0;
  for (int i = 0; i < l; ++i) {
    int x;
    scanf("%d", &x);
    if (x & 1)
      b |= 1 << ((x - 1) / 2);
    else
      a |= 1 << ((x / 2) - 1);
  }

  assert(a != b);

  if (a > b)
    printf("A\n");
  else
    printf("B\n");
}

int main(void) {
  scanf("%d%d", &l, &q);
  while (q--) {
    char t[10];
    scanf("%s", t);
    if (t[0] == 'a') alojzije();
    if (t[0] == 'b') benjamin();
    if (t[0] == 'c') cecilija();
  }
  return 0;
}
