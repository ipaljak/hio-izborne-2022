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

const int MAXN = 5e5 + 10;

vector<int> comp[2][MAXN];
int dad[2][MAXN];
unordered_map<ll, int> cnt;

ll h(int x) { return (ll)dad[0][x] * MAXN + dad[1][x]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        comp[0][i] = comp[1][i] = {i};
        dad[0][i] = dad[1][i] = i;
        cnt[h(i)] = 1;
    }

    int sol = 0;
    while (q--) {
        int x, y, t;
        cin >> x >> y >> t;
        t--;

        x = dad[t][x];
        y = dad[t][y];
        if (x == y) continue;
        if (comp[t][x].size() < comp[t][y].size()) swap(x, y);

        for (int z : comp[t][y]) {
            cnt[h(z)]--;
            sol -= cnt[h(z)];

            dad[t][z] = x;
            comp[t][x].push_back(z);

            sol += cnt[h(z)];
            cnt[h(z)]++;
        }

        cout << sol << '\n';
    }

    return 0;
}

