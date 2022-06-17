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

int n;
vector<pii> sol;
vector<int> cnt_row, cnt_col, cnt_d1, cnt_d2;
vector<vi> ind;
vector<vi> cnt;

set<pair<int, pii>> avail;

void update_cell(int x, int y, int d) {
    cnt[x][y] += d;
    if (cnt[x][y] & 1) avail.erase({cnt[x][y] - d, {x, y}});
    else if (ind[x][y] == 0) avail.insert({cnt[x][y], {x, y}});
}

void add_queen(int x, int y, int k) {
    sol.push_back({x + 1, y + 1});
    ind[x][y] = k;
    //cnt_row[x]++;
    //cnt_col[y]++;
    //cnt_d1[x + y]++;
    //cnt_d2[x - y + n]++;
    for (int i = 0; i < n; i++) {
        update_cell(i, y, 1);
        update_cell(x, i, 1);
        if (0 <= x + y - i && x + y - i < n) update_cell(i, x + y - i, 1);
        if (0 <= y - x + i && y - x + i < n) update_cell(i, y - x + i, 1);
    }
}
void remove_queen(int x, int y) {
    sol.pop_back();
    ind[x][y] = 0;
    //cnt_row[x]--;
    //cnt_col[y]--;
    //cnt_d1[x + y]--;
    //cnt_d2[x - y + n]--;
    for (int i = 0; i < n; i++) {
        update_cell(i, y, -1);
        update_cell(x, i, -1);
        if (0 <= x + y - i && x + y - i < n) update_cell(i, x + y - i, -1);
        if (0 <= y - x + i && y - x + i < n) update_cell(i, y - x + i, -1);
    }
}

vector<pair<int, pii>> take_first(const set<pair<int, pii>> S, int k) {
    vector<pair<int, pii>> V;
    auto it = S.begin();
    for (int i = 0; i < k; i++) {
        if (it == S.end()) return V;
        V.push_back(*(it++));
    }
    return V;
}

void dfs(int k) {
    vector<pair<int, pii>> places = take_first(avail, 5);

    if (places.empty()) {
        if ((n <= 2 && sol.size() == 1) || (n % 2 == 1 && sol.size() == n * n) || (n % 2 == 0 && sol.size() == n * n - 2)) {
            cout << sol.size() << '\n';
            for (auto& it : sol) cout << it.fi << ' ' << it.se << '\n';
            exit(0);
        } else {
            return;
        }
    }

    random_shuffle(places.begin(), places.end());
    //sort(places.begin(), places.end());
    //sort(places.rbegin(), places.rend());
    for (auto& [c, it] : places) {
        auto& [x, y] = it;
        assert(c % 2 == 0);

        add_queen(x, y, k);

        dfs(k + 1);

        remove_queen(x, y);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));

    cin >> n;

    cnt_row.resize(n); cnt_col.resize(n);
    cnt_d1.resize(2 * n); cnt_d2.resize(2 * n);
    ind = vector<vi>(n, vi(n));
    cnt = vector<vi>(n, vi(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            avail.insert({0, {i, j}});
    dfs(1);

    return 0;
}

