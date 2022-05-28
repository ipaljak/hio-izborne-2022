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

bool query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    bool ans;
    cin >> ans;
    return ans;
}

int main() {
    int n;
    cin >> n;

    int sol = 1;
    for (int i = 0; i < n * 2 - 1; i++) {
        int lo = 0, hi = n / 2 + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            int l = (i + 1) / 2 - mid, r = i / 2 + mid;
            if (l < 0 || r >= n || l > r || !query(l + 1, r + 1)) hi = mid;
            else lo = mid;
        }
        sol = max(sol, lo * 2 + 1 - (i & 1));
    }

    cout << "! " << sol << endl;

    return 0;
}

