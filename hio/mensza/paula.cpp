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

void A() {
    int a;
    cin >> a;

    vector<int> vec;
    for (int i = 0; i < 20; i++)
        if (a & (1 << i)) a ^= 1 << i;
        else vec.push_back(a ^ (1 << i));

    cout << vec.size() << ' ';
    for (int x : vec) cout << x << ' ';
}

void B() {
    int b;
    cin >> b;

    vector<int> vec;
    for (int i = 0; i < 20; i++)
        if (b & (1 << i)) {
            vec.push_back(b);
            b ^= 1 << i;
        }

    cout << vec.size() << ' ';
    for (int x : vec) cout << x << ' ';
}

void C() {
    int c;
    cin >> c;
    vector<int> vec(c);
    for (int& x : vec) cin >> x;
    if (vec.back() == 2) cout << "B\n";
    else cout << "A\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int l, q;
    cin >> l >> q;
    while (q--) {
        string name;
        cin >> name;
        if (name[0] == 'a') A();
        if (name[0] == 'b') B();
        if (name[0] == 'c') C();
    }

    return 0;
}

