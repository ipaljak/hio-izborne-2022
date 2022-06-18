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
typedef vector<int> vi;

typedef pair<ll, ll> pll;

void no() {
    cout << "WRONG!\n";
    exit(0);
}

pll reduce(ll a, ll b) {
    assert(b != 0);
    ll g = gcd(a, b);
    a /= g; b /= g;
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return {a, b};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    auto ppll_hash = [](pair<pll, pll> const& x) {
        return x.fi.fi ^ x.fi.se ^ x.se.fi ^ x.se.se;
    };

    unordered_set<pair<pll, pll>, decltype(ppll_hash)> lines(0, ppll_hash);
    unordered_set<ll> verticals;

    int n;
    cin >> n;
    vector<pll> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].fi >> pts[i].se;

        for (int j = 0; j < i; j++) {
            ll dx = pts[i].fi - pts[j].fi;
            ll dy = pts[i].se - pts[j].se;
            ll x = pts[i].fi, y = pts[i].se;

            if (dx == 0) {
                if (verticals.count(x)) no();
                verticals.insert(x);
            } else {
                pair<pll, pll> l = {reduce(dy, dx), reduce(dy * x - dx * y, dx)};
                if (lines.count(l)) no();
                lines.insert(l);
            }
        }
    }

    return 0;
}

