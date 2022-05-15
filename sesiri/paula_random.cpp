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

bool checker(int n, vector<string> sol) {
  vector<vector<int>> cnt(1 << n, vector<int>(2));
  for (int i = 0; i < n; i++) {
      string s = sol[i];
      int mask_A = (1 << n - 1 - i) - 1, mask_B = ((1 << i) - 1) << n - 1 - i;
      for (int j = 0; j < (1 << n - 1); j++) {
          int hat = s[j] == CHAR_1;
          int scene = (j & mask_A) ^ (hat << n - 1 - i) ^ ((j & mask_B) << 1);
          cnt[scene][hat]++;
      }
  }

  for (int i = 0; i < (1 << n); i++) {
      int total_1 = __builtin_popcount(i), total_0 = n - total_1;
      if (cnt[i][0] < total_0 / 2) return false;
      if (cnt[i][1] < total_1 / 2) return false;
  }
  return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));

    int n;
    cin >> n;

    while (true) {
        vector<string> sol(n, string(1 << n - 1, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (1 << n - 1); j++) {
                if (rand() & 1) sol[i][j] = CHAR_0;
                else sol[i][j] = CHAR_1;
            }
        }
        if (checker(n, sol)) {
            for (auto& s : sol) cout << s << '\n';
            break;
        }
        cerr << '.';
    }

    return 0;
}

