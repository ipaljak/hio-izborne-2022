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

const int MAXN = 5010;
int dir[MAXN][MAXN];

void debug() {
  REP(j, 5) {
    REP(i, 6) {
      cout << dir[i + 1][j + 1] << " ";
    } cout << endl;
  }
}

void solve(int n, int m, point s, point t, int xoff = 0, int yoff = 0) {
  //cout << n << " " << m << " " << s.x << " " << s.y << " " << t.x << " " << t.y << endl;
  if (n == 1) {
    int d = 0;
    if (s.x > t.x) d = 2;
    while (s.x != t.x) {
      dir[s.x + xoff][s.y + yoff] = d;
      if (d == 0) s.x++;
      else        s.x--;
    }
    return;
  }
  if (m == 1) {
    int d = 1;
    if (s.y > t.y) d = 3;
    while (s.y != t.y) {
      dir[s.x + xoff][s.y + yoff] = d;
      if (d == 1) s.y++;
      else        s.y--;
    }
    return;
  }
  if (n == 2) {
    if (s.y != t.y && (s.x == t.x || s.x == t.x - 1 || s.x == t.x + 1)) {
      if (s.x + t.x > (2*m - t.x - s.x + 2)) {
        while (s.x != 1) {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        if (s.y == 1) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        while (s.x != t.x) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        }
      } else {
        while (s.x != m) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        }
        if (s.y == 1) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        while (s.x != t.x) {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
      }
    } else {
      int ss = s.x, tt = t.x;
      if (s.x < t.x) {
        while (s.x != 1) {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        if (s.y == 1) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        while (s.x != ss) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        }

        if (s.y == t.y) {
          while (s.x + 3 < t.x) {
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
          if (s.y == 1) {
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
          } else {
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
          }
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
          if (s.x != t.x) {
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
          }
        } else {
          while (s.x + 3 <= t.x) {
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
          if (s.x != t.x) {
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
          }
        }

        while (s.x != m) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        }
        if (s.y == 1) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        while (s.x != t.x) {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
      } else {
        while (s.x != m) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        }
        if (s.y == 1) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        while (s.x != ss) {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }

        if (s.y == t.y) {
          while (s.x - 3 > t.x) {
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
          if (s.y == 1) {
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
          } else {
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
          }
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
          if (s.x != t.x) {
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
          }
        } else {
          while (s.x - 3 >= t.x) {
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
            if (s.y == 1) {
              dir[s.x + xoff][s.y + yoff] = 1;
              s.y++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 3;
              s.y--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
          if (s.x != t.x) {
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
          }
        }

        while (s.x != 1) {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        if (s.y == 1) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        while (s.x != t.x) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        }
      }
    }
    return;
  }
  if (m == 2) {
    if (s.x != t.x && (s.y == t.y || s.y == t.y - 1 || s.y == t.y + 1)) {
      if (s.y + t.y > (2*n - t.y - s.y + 2)) {
        while (s.y != 1) {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        if (s.x == 1) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        while (s.y != t.y) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        }
      } else {
        while (s.y != n) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        }
        if (s.x == 1) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        while (s.y != t.y) {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
      }
    } else {
      int ss = s.y, tt = t.y;
      if (s.y < t.y) {
        while (s.y != 1) {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        if (s.x == 1) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        while (s.y != ss) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        }

        if (s.x == t.x) {
          while (s.y + 3 < t.y) {
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
          if (s.x == 1) {
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
          } else {
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
          }
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
          if (s.y != t.y) {
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
          }
        } else {
          while (s.y + 3 <= t.y) {
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
          if (s.y != t.y) {
            dir[s.x + xoff][s.y + yoff] = 1;
            s.y++;
          }
        }

        while (s.y != n) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        }
        if (s.x == 1) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        while (s.y != t.y) {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
      } else {
        while (s.y != n) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        }
        if (s.x == 1) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        while (s.y != ss) {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }

        if (s.x == t.x) {
          while (s.y - 3 > t.y) {
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
          if (s.x == 1) {
            dir[s.x + xoff][s.y + yoff] = 0;
            s.x++;
          } else {
            dir[s.x + xoff][s.y + yoff] = 2;
            s.x--;
          }
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
          if (s.y != t.y) {
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
          }
        } else {
          while (s.y - 3 >= t.y) {
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
            if (s.x == 1) {
              dir[s.x + xoff][s.y + yoff] = 0;
              s.x++;
            } else {
              dir[s.x + xoff][s.y + yoff] = 2;
              s.x--;
            }
          }

          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
          if (s.y != t.y) {
            dir[s.x + xoff][s.y + yoff] = 3;
            s.y--;
          }
        }

        while (s.y != 1) {
          dir[s.x + xoff][s.y + yoff] = 3;
          s.y--;
        }
        if (s.x == 1) {
          dir[s.x + xoff][s.y + yoff] = 0;
          s.x++;
        } else {
          dir[s.x + xoff][s.y + yoff] = 2;
          s.x--;
        }
        while (s.y != t.y) {
          dir[s.x + xoff][s.y + yoff] = 1;
          s.y++;
        }
      }
    }
    return;
  }

  for (int i = 2; i < min(s.x, t.x); i += 2) {
    if (U(n, i, {i, 1}, {i, 2}) + U(n, m - i, {s.x - i, s.y}, {t.x - i, t.y}) == U(n, m, s, t)) {
      solve(n, m - i, {s.x - i, s.y}, {t.x - i, t.y}, xoff + i, yoff);
      FOR(j, 1, n + 1) {
        if (dir[i + 1 + xoff][j + yoff] == 1) {
          solve(n, i, {i, j}, {i, j + 1}, xoff, yoff);
          dir[i + 1 + xoff][j + yoff] = 2;
          dir[i + xoff][j + 1 + yoff] = 0;
          return;
        }
      }

      FOR(j, 2, n + 1) {
        if (dir[i + 1 + xoff][j + yoff] == 3) {
          solve(n, i, {i, j}, {i, j - 1}, xoff, yoff);
          dir[i + 1 + xoff][j + yoff] = 2;
          dir[i + xoff][j - 1 + yoff] = 0;
          return;
        }
      }

      FOR(j, 1, n + 1) {
        if (dir[i + 1 + xoff][j + yoff] == 0 && dir[i + 2 + xoff][j + yoff] == 1 && dir[i + 1 + xoff][j + 1 + yoff] == -1) {
          solve(n, i, {i, j}, {i, j + 1}, xoff, yoff);
          dir[i + 1 + xoff][j + 1 + yoff] = 0;
          dir[i + 2 + xoff][j + yoff] = -1;

          dir[i + 1 + xoff][j + yoff] = 2;
          dir[i + xoff][j + 1 + yoff] = 0;
          return;
        }
      }

      FOR(j, 2, n + 1) {
        if (dir[i + 1 + xoff][j + yoff] == 0 && dir[i + 2 + xoff][j + yoff] == 3 && dir[i + 1 + xoff][j - 1 + yoff] == -1) {
          solve(n, i, {i, j}, {i, j + 1}, xoff, yoff);
          dir[i + 1 + xoff][j - 1 + yoff] = 0;
          dir[i + 2 + xoff][j + yoff] = -1;

          dir[i + 1 + xoff][j + yoff] = 2;
          dir[i + xoff][j - 1 + yoff] = 0;
          return;
        }
      }
    }
  }

  for (int i = m - 2; i >= max(s.x, t.x); i -= 2) {
    if (U(n, i, s, t) + U(n, m - i, {1, 1}, {1, 2}) == U(n, m, s, t)) {
      solve(n, i, s, t, xoff, yoff);
      FOR(j, 1, n + 1) {
        if (dir[i + xoff][j + yoff] == 1) {
          solve(n, m - i, {1, j}, {1, j + 1}, xoff + i, yoff);
          dir[i + xoff][j + yoff] = 0;
          dir[i + 1 + xoff][j + 1 + yoff] = 2;
          return;
        }
      }
      FOR(j, 2, n + 1) {
        if (dir[i + xoff][j + yoff] == 3) {
          solve(n, m - i, {1, j}, {1, j - 1}, xoff + i, yoff);
          dir[i + xoff][j + yoff] = 0;
          dir[i + 1 + xoff][j - 1 + yoff] = 2;
          return;
        }
      }

      FOR(j, 1, n + 1) {
        if (dir[i + xoff][j + yoff] == 2 && dir[i - 1 + xoff][j + yoff] == 1 && dir[i + xoff][j + 1 + yoff] == -1) {
          solve(n, m - i, {1, j}, {1, j + 1}, xoff + i, yoff);
          dir[i + xoff][j + 1 + yoff] = 2;
          dir[i - 1 + xoff][j + yoff] = -1;

          dir[i + xoff][j + yoff] = 0;
          dir[i + 1 + xoff][j + 1 + yoff] = 2;
          return;
        }
      }

      FOR(j, 2, n + 1) {
        if (dir[i + xoff][j + yoff] == 2 && dir[i - 1 + xoff][j + yoff] == 3 && dir[i + xoff][j - 1 + yoff] == -1) {
          solve(n, m - i, {1, j}, {1, j - 1}, xoff + i, yoff);
          dir[i + xoff][j - 1 + yoff] = 2;
          dir[i - 1 + xoff][j + yoff] = -1;

          dir[i + xoff][j + yoff] = 0;
          dir[i + 1 + xoff][j - 1 + yoff] = 2;
          return;
        }
      }
    }
  }

  if (s.x < t.x) {
    for (int i = s.x; i < t.x; i++) {
      FOR(j, 1, n + 1) {
        if (s.x == i && s.y == j) continue;
        if (t.x == i + 1 && t.y == j) continue;
        if (U(n, m, s, t) == U(n, i, s, {i, j}) + U(n, m - i, {i + 1, j}, t)) {
          solve(n, i, s, {i, j}, xoff, yoff);
          solve(n, m - i, {1, j}, {t.x - i, t.y}, xoff + i, yoff);
          dir[i + xoff][j + yoff] = 0;
          return;
        }
      }
    }
  } else {
    for (int i = t.x; i < s.x; i++) {
      FOR(j, 1, n + 1) {
        if (t.x == i && t.y == j) continue;
        if (s.x == i + 1 && s.y == j) continue;
        if (U(n, m, s, t) == U(n, i, t, {i, j}) + U(n, m - i, {i + 1, j}, s)) {
          solve(n, i, t, {i, j}, xoff, yoff);
          solve(n, m - i, {1, j}, {s.x - i, s.y}, xoff + i, yoff);
          dir[i + xoff][j + yoff] = 0;
          return;
        }
      }
    }
  }

  return;
}

char out[2 * MAXN][3 * MAXN];

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

    /*bool flip = true;
    if (n > m) {
      swap(n, m);
      swap(t.x, t.y);
      swap(s.x, s.y);
      flip = false;
    }*/

    /*bool reverse = false;
    if (s.x > t.x) {
      swap(s, t);
      reverse = true;
    }*/

    REP(i, n + 1) {
      REP(j, m + 1) {
        dir[j][i] = -1;
      }
    }
    solve(n, m, s, t);

    REP(i, 2 * n) {
      REP(j, 3 * m) {
        out[i][j] = ' ';
      }
    }

    FOR(i, 0, n) {
      FOR(j, 0, m) {
        out[i * 2][j * 3] = 'o';
        if (dir[j + 1][i + 1] == 0) {
          out[i * 2][j * 3 + 1] = '-';
          out[i * 2][j * 3 + 2] = '-';
        }
        if (dir[j + 1][i + 1] == 2) {
          out[i * 2][j * 3 - 1] = '-';
          out[i * 2][j * 3 - 2] = '-';
        }
        if (dir[j + 1][i + 1] == 1) {
          out[i * 2 + 1][j * 3] = '|';
        }
        if (dir[j + 1][i + 1] == 3) {
          out[i * 2 - 1][j * 3] = '|';
        }
      }
    }

    out[(s.y - 1) * 2][(s.x - 1) * 3] = '*';
    out[(t.y - 1) * 2][(t.x - 1) * 3] = '*';

    cout << U(n, m, s, t) << "\n";
    /*REP(i, 2 * n) {
      REP(j, 3 * m) {
        cout << out[i][j];
      }
      cout << "\n";
    }*/
  }

  return 0;
}