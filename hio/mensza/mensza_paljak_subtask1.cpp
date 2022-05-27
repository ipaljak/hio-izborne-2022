#include <bits/stdc++.h>

using namespace std;

int l, q;

void alojzije() {
  int a;
  scanf("%d", &a);

  vector<int> ret;
  for (int i = 0; i < a; ++i) ret.push_back(1);

  printf("%d", (int)ret.size());
  for (int x : ret) printf(" %d", x);
  printf("\n");
}

void benjamin() {
  int b;
  scanf("%d", &b);

  vector<int> ret;
  for (int i = 0; i < 100 + b; ++i) ret.push_back(2);

  printf("%d", (int)ret.size());
  for (int x : ret) printf(" %d", x);
  printf("\n");
}

void cecilija() {
  int l;
  scanf("%d", &l);
  assert(l == 2);

  int a, b;
  scanf("%d%d", &a, &b);
  b -= 100;

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
