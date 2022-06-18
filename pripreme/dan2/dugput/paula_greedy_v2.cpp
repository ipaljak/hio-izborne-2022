// Svaki put se greedy pomakni u slobodno polje iz kojeg se moze doci do cilja,
// i to ono koje je najdalje od cilja.
// Nakon svakog koraka updatea udaljenosti svih polja do cilja (iako mislim da
// taj dio nije skroz tocan. ali radi).
// Nikad ne zapne i brzo je.
// Za n=m=1000, vecinu vremena da ~99%-optimalno rjesenje. Ponekad bude ~70% 
// optimalno.

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
const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    while (q--) {

    int n, m, ax, ay, bx, by;
    cin >> n >> m >> ax >> ay >> bx >> by;
    ax--; ay--;
    bx--; by--;

    vector<vi> dist_to_b(n, vi(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist_to_b[i][j] = abs(i - bx) + abs(j - by);

    vector<vi> last_vis(n, vi(m));
    int vis_time = 0;

    vector<vi> taken(n, vi(m));
    int x = ax, y = ay;
    vector<pii> sol;
    while (true) {
        sol.push_back({x, y});
        taken[x][y] = 1;
        if (x == bx && y == by) break;

        vis_time++;
        queue<pii> Q({{x, y}});
        while (!Q.empty()) {
            int qx = Q.front().fi, qy = Q.front().se;
            Q.pop();

            if (last_vis[qx][qy] == vis_time) {
                dist_to_b[qx][qy] = INF;
                continue;
            }
            last_vis[qx][qy] = vis_time;

            if (qx == bx && qy == by) continue;

            int min_d = INF;
            if (!taken[qx][qy]) {
                for (pii d : deltas) {
                    int xx = qx + d.fi, yy = qy + d.se;
                    if (!(0 <= xx && xx < n && 0 <= yy && yy < m)) continue;
                    //TRACE(xx _ yy);
                    min_d = min(min_d, dist_to_b[xx][yy] + 1);
                }
            }

            //TRACE(qx _ qy _ dist_to_b[qx][qy] _ min_d _ taken[qx][qy]);
            if (dist_to_b[qx][qy] == min_d) continue;

            dist_to_b[qx][qy] = min_d;

            for (pii d : deltas) {
                int xx = qx + d.fi, yy = qy + d.se;
                if (!(0 <= xx && xx < n && 0 <= yy && yy < m)) continue;
                Q.push({xx, yy});
            }
        }
        //TRACE(x _ y);
        //TRACE(dist_to_b);


        int nx = -1, ny = -1;
        for (pii d : deltas) {
            int xx = x + d.fi, yy = y + d.se;
            if (!(0 <= xx && xx < n && 0 <= yy && yy < m)) continue;
            if (taken[xx][yy] || dist_to_b[xx][yy] == INF) continue;
            if (nx == -1 || dist_to_b[xx][yy] > dist_to_b[nx][ny])
                nx = xx, ny = yy;
        }
        if (nx == -1) break;

        x = nx; y = ny;
    }

    if (!(sol.back().fi == bx && sol.back().se == by)) {
        sol.clear();
        sol.push_back({ax, ay});
        while (sol.back() != pii(bx, by)) {
            sol.push_back(sol.back());
            if (sol.back().fi < bx) sol.back().fi++;
            else if (sol.back().fi > bx) sol.back().fi--;
            else if (sol.back().se > by) sol.back().se--;
            else sol.back().se++;
        }
    }

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
    //cout << sol.size() - 1 << '\n';
    for (auto& s : sol_out)
        cout << s << '\n';

    }

    return 0;
}

