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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));

    int n;
    cin >> n;

    while (true) {
        vector<pii> sol;
        vector<vi> cnt(n, vi(n));
        vector<vi> ind(n, vi(n));
        for (int k = 1; k <= n * n; k++) {
            vector<pii> places;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (ind[i][j] == 0 && cnt[i][j] % 2 == 0)
                        places.push_back({i, j});
            if (places.empty()) break;
            auto [x, y] = places[rand() % places.size()];
            sol.push_back({x + 1, y + 1});
            ind[x][y] = k;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (i == x || j == y || i + j == x + y || i - j == x - y)
                        cnt[i][j]++;
        }

        if ((n <= 2 && sol.size() == 1) || (n % 2 == 1 && sol.size() == n * n) || (n % 2 == 0 && sol.size() == n * n - 2)) {
            cout << sol.size() << '\n';
            for (auto& it : sol) cout << it.fi << ' ' << it.se << '\n';
            break;
        }
    }

    return 0;
}

