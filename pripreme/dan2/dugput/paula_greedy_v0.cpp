// Svaki put se greedy pomakni u slobodno polje koje je najdalje od cilja.
// Ponekad zapne.

#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#define _ << " _ " <<

template<class> struct is_container : false_type {};
template<class... Ts> struct is_container<vector<Ts...>> : true_type {};
template<class... Ts> struct is_container<map<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template<class... Ts> struct is_container<set<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template<class... Ts> struct is_container<multiset<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_multiset<Ts...>> : true_type {};
template<class T, class = typename enable_if<is_container<T>::value>::type>
ostream& operator<<(ostream &o, T x) {
  int f = 1;
  o << "{";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "}";
}
template<class T, class U>
ostream& operator<<(ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const vector<pii> deltas = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, ax, ay, bx, by;
    cin >> n >> m >> ax >> ay >> bx >> by;
    ax--; ay--;
    bx--; by--;

    vector<vi> dist_to_b(n, vi(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist_to_b[i][j] = abs(i - bx) + abs(j - by);

    vector<vi> taken(n, vi(m));
    int x = ax, y = ay;
    vector<pii> sol;
    while (true) {
        sol.push_back({x, y});
        taken[x][y] = true;
        if (x == bx && y == by) break;

        int nx = -1, ny = -1;
        for (pii d : deltas) {
            int xx = x + d.fi, yy = y + d.se;
            if (!(0 <= xx && xx < n && 0 <= yy && yy < m)) continue;
            if (taken[xx][yy]) continue;
            if (nx == -1 || dist_to_b[xx][yy] > dist_to_b[nx][ny])
                nx = xx, ny = yy;
        }
        if (nx == -1) break;

        x = nx; y = ny;
    }

    assert(sol.back().fi == bx && sol.back().se == by);

    vector<string> sol_out(2 * n - 1, string(3 * m - 2, ' '));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sol_out[2 * i][3 * j] = 'o';
    sol_out[2 * ax][3 * ay] = '*';
    sol_out[2 * bx][3 * by] = '*';
    for (int i = 0; i + 1 < (int)sol.size(); i++) {
        int ex = min(sol[i].fi, sol[i+1].fi), ey = min(sol[i].se, sol[i+1].se);
        if (sol[i].fi == sol[i+1].fi) {
            sol_out[2 * ex][3 * ey + 1] = '-';
            sol_out[2 * ex][3 * ey + 2] = '-';
        } else {
            sol_out[2 * ex + 1][3 * ey] = '|';
        }
    }
    cout << sol.size() - 1 << '\n';
    for (auto& s : sol_out)
        cout << s << '\n';

    return 0;
}

