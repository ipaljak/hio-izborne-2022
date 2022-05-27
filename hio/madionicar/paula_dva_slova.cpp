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

const int MOD = 1e9 + 7, MAXN = 1e5 + 10;
int pow2[MAXN];
struct Hash {
    vi pref;
    Hash(string s) {
        pref.resize(s.size());
        for (int i = 0; i < (int)s.size(); i++) {
            if (i > 0) pref[i] = pref[i - 1] * 2;
            pref[i] += s[i] - 'a';
            if (pref[i] >= MOD) pref[i] -= MOD;
        }
    }
    int h(int l, int r) {
        int ret = pref[r];
        if (l > 0) ret -= (ll)pref[l - 1] * pow2[r - l + 1] % MOD;
        if (ret < 0) ret += MOD;
        return ret;
    }
};

int main() {
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = pow2[i - 1] * 2;
        if (pow2[i] >= MOD) pow2[i] -= MOD;
    }

    int n;
    cin >> n;

    string s = "a";
    for (int i = 0; i + 1 < n; i++)
        if (query(i + 1, i + 2)) s += s.back();
        else s += s.back() ^ 'a' ^ 'b';

    auto hashA = Hash(s);
    reverse(s.begin(), s.end());
    auto hashB = Hash(s);

    int sol = 1;
    for (int m : {0, 1}) {
        int lo = 0, hi = n / 2 + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2, len = mid * 2 + m;
            bool found;
            if (len == 0) {
                found = true;
            } else {
                found = false;
                for (int i = 0; i + len <= n && !found; i++)
                    found |= hashA.h(i, i + len - 1) == hashB.h(n - 1 - (i + len - 1), n - 1 - i);
            }
            if (found) lo = mid;
            else hi = mid;
        }
        sol = max(sol, lo * 2 + m);
    }

    cout << "! " << sol << endl;

    return 0;
}

