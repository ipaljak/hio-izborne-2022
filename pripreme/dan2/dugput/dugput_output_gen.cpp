#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long

using namespace std;

struct point {
  int x, y;
};

int color(point a) {
  return (a.x + a.y) % 2;
}

bool f1(int n, int m, point s, point t) {
  if (n != 1) return false;
  if (s.x != 1 && s.x != m) return true;
  if (t.x != 1 && t.x != m) return true;
  return false;
}

bool f2(int n, int m, point s, point t) {
  if (n != 2) return false;
  if (s.x != t.x) return false;
  return true;
}

bool f2_star(int n, int m, point s, point t) {
  if (n != 2) return false;
  if (s.x == t.x) return true;
  if (s.x == t.x - 1 && s.y != t.y) return true;
  return false;
}

bool f3(int n, int m, point s, point t) {
  if (n != 3) return false;
  if (m % 2 != 0) return false;
  if (color(s) == color(t)) return false;
  if (color(s) == 0) {
    s.x = m - s.x;
    t.x = m - t.x;
  }
  if (s.y == 2 && s.x < t.x) return true;
  if (s.y != 2 && s.x < t.x - 1) return true;
  return false;
}

bool color_compatible(int n, int m, point s, point t) {
  int grid = (n * m) % 2;
  int colors = (color(s) + color(t)) % 2;
  if (grid == 0) return (colors == 1);
  if (color(s) == 1) return false;
  if (color(t) == 1) return false;
  return true;
}

bool c0(int n, int m, point s, point t) {
  if (!color_compatible(n, m, s, t)) return false;
  if (f1(n, m, s, t)) return false;
  if (f2(n, m, s, t)) return false;
  if (f3(n, m, s, t)) return false;
  return true;
}

bool c1(int n, int m, point s, point t) {
  if (f1(n, m, s, t)) return false;
  if (f2_star(n, m, s, t)) return false;
  if (((n * m) % 2) == 0 && color(s) == color(t)) return true;
  if (((n * m) % 2) == 1 && color(s) != color(t)) return true;
  return false;
}

bool c2(int n, int m, point s, point t) {
  if (color_compatible(n, m, s, t) && f3(n, m, s, t)) return true;

  if ((n * m) % 2 == 0) return false;
  if (color(s) != 1) return false;
  if (color(t) != 1) return false;
  if (f1(n, m, s, t)) return false;
  if (f2_star(n, m, s, t)) return false;
  return true;
}

int U(int n, int m, point s, point t) {
  if (n > m) {
    swap(n, m);
    swap(t.x, t.y);
    swap(s.x, s.y);
  }

  if (s.x > t.x) {
    swap(s, t);
  }

  if (f1(n, m, s, t)) return t.x - s.x + 1;
  if (f2_star(n, m, s, t)) return max(t.x + s.x, 2*m - t.x - s.x + 2);
  if (c0(n, m, s, t)) return n * m;
  if (c1(n, m, s, t)) return n * m - 1;
  if (c2(n, m, s, t)) return n * m - 2;

  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  while (T--) {

    int n, m;
    point s, t;
    cin >> n >> m;
    cin >> s.y >> s.x;
    cin >> t.y >> t.x;

    cout << U(n, m, s, t) << "\n";
  }

  return 0;
}