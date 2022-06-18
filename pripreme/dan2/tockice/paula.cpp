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

ll ccw(const pii& a, const pii& b, const pii& c) {
    return (ll)a.fi * (b.se - c.se) +
           (ll)b.fi * (c.se - a.se) +
           (ll)c.fi * (a.se - b.se);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<pii> pts(n);
    for (auto& pt : pts) cin >> pt.fi >> pt.se;

    sort(pts.begin(), pts.end());
    vector<pii> upper_hull, lower_hull;
    for (auto& pt : pts) {
        while (upper_hull.size() >= 2 &&
                ccw(upper_hull.end()[-2], upper_hull.end()[-1], pt) > 0)
            upper_hull.pop_back();
        upper_hull.push_back(pt);

        while (lower_hull.size() >= 2 &&
                ccw(lower_hull.end()[-2], lower_hull.end()[-1], pt) < 0)
            lower_hull.pop_back();
        lower_hull.push_back(pt);
    }

    int inner = n - (int)lower_hull.size() - (int)upper_hull.size() + min(2, n);
    if (inner % 2 == 0 && n > 1) cout << "Alenka\n";
    else cout << "Bara\n";

    return 0;
}

