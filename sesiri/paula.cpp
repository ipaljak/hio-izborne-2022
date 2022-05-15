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

const char CHAR_0 = 'A', CHAR_1 = 'B';

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;


    auto color = [&](int x, int y) {
        if (max(x, y) == 1 << n) return 2;
        else return __builtin_popcount(min(x, y)) & 1;
    };


    int k = (1 << n) + (n & 1);
    vector<vector<unordered_set<int>>> edg(k);
    vector<int> deg(k);
    for (int i = 0; i < k; i++) {
        edg[i].resize(2 + (n & 1));
        if (i == (1 << n)) {
            for (int j = 0; j < (1 << n); j++)
                edg[i][2].insert(j);
            deg[i] = 1 << n;
        } else {
            for (int j = 0; j < n; j++)
                edg[i][color(i, i ^ (1 << j))].insert(i ^ (1 << j));
            if (n & 1) edg[i][2].insert(1 << n);
            deg[i] = n + (n & 1);
        }
    }


    vector<pair<pair<int, int>, int>> sol;

    for (int i = 0; i < (1 << n); i++)
        while (deg[i]) {
            int x = i, col = 0;
            while (deg[x]) {
                if (edg[x][col].empty()) {
                    if (!edg[x][0].empty()) col = 0;
                    else if (!edg[x][1].empty()) col = 1;
                    else col = 2;
                }
                int y = *edg[x][col].begin();

                deg[x]--;
                deg[y]--;
                edg[x][col].erase(y);
                edg[y][col].erase(x);
                
                if (max(x, y) != 1 << n)
                    sol.push_back({{-(x ^ y), min(x, y)}, x < y});

                x = y;
            }
        }


    sort(sol.begin(), sol.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n - 1); j++)
            if (sol[i * (1 << n - 1) + j].se) cout << CHAR_1; else cout << CHAR_0;
        cout << '\n';
    }
    
    return 0;
}

