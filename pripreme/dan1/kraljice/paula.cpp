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

const vector<pii> A = {
    {1, 1},
    {2, 3},
    {1, 3},
    {3, 1},
    {2, 2},
    {1, 2},
    {3, 2},
    {2, 1}
};

const vector<pii> B = {
    {2, 2}, 
    {3, 4},
    {3, 2},
    {4, 3},
    {1, 4},
    {3, 3},
    {1, 3},
    {1, 1},
    {4, 2},
    {2, 4},
    {2, 3},
    {1, 2},
    {4, 1},
    {3, 1}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    if (n <= 2) cout << "1\n1 1\n";
    else {
        vector<pii> sol;
        for (int i = 0; (n % 2 == 0 && i < n - 4) || (n % 2 == 1 && i < n - 1); i += 2) {
            for (auto& it : A)
                sol.push_back({it.fi + i, it.se + i});
            
            for (int j = i + 3; j < n; j++) {
                /* x x x 2    x x x x 1
                   x x x 1    x x x x 2
                   x x        x x
                   3 4        x x 
                              4 3 */
                if (j % 2 == 1) {
                    sol.push_back({i + 2, j + 1});
                    sol.push_back({i + 1, j + 1});
                    sol.push_back({j + 1, i + 1});
                    sol.push_back({j + 1, i + 2});
                } else {
                    sol.push_back({i + 1, j + 1});
                    sol.push_back({i + 2, j + 1});
                    sol.push_back({j + 1, i + 2});
                    sol.push_back({j + 1, i + 1});
                }
            }
        }

        if (n % 2 == 1) sol.push_back({n, n});
        else {
            for (auto& it : B)
                sol.push_back({it.fi + n - 4, it.se + n - 4});
        }

        cout << sol.size() << '\n';
        for (auto& it : sol) cout << it.fi << ' ' << it.se << '\n';
    }

    return 0;
}

