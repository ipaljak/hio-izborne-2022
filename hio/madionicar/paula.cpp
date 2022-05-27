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
    int n;
    cin >> n;
    int sol = 1;
    for (int i = 0; i < n * 2 - 1; i++) {
        int len0 = sol + 1 + ((sol ^ i) & 1);
        for (int len = len0; ; len += 2) {
            int lo = (i + 1) / 2 - len / 2, hi = i / 2 + len / 2;
            if (lo < 0 || hi >= n) break;

            cout << "? " << lo + 1 << " " << hi + 1 << endl;
            bool ans;
            cin >> ans;

            if (!ans) break;
            else sol = len;
        }
    }
    cout << "! " << sol << endl;

    return 0;
}

