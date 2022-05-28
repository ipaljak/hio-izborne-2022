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

string random(char** argv) {
    int n = atoi(argv[0]), k = atoi(argv[1]);
    string s(n, 0);
    for (int i = 0; i < n; i++) s[i] = 'a' + rand() % k;
    return s;
}


struct UnionFind {
    vi dad;
    UnionFind(int n) {
        dad.resize(n);
        iota(dad.begin(), dad.end(), 0);
    }
    int find(int x) {
        if (dad[x] == x) return x;
        return dad[x] = find(dad[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) dad[x] = y;
    }
};

string construct(vector<int> len, int k) {
    int n = (int)len.size() / 2 + 1;
    UnionFind UF(n);
    for (int i = 0; i < 2 * n - 1; i++) {
        int l = (i + 1) / 2 - len[i] / 2, r = i / 2 + len[i] / 2;
        while (l < r) {
            UF.unite(l, r);
            l++;
            r--;
        }
    }

    string comp_let(n, 0);
    for (int i = 0; i < n; i++) comp_let[i] = 'a' + rand() % k;

    string s(n, 0);
    for (int i = 0; i < n; i++) s[i] = comp_let[UF.find(i)];
    return s;
}


string normal(char** argv) {
    int n = atoi(argv[0]), k = atoi(argv[1]);
    int max_l = atoi(argv[2]), cnt_max_l = atoi(argv[3]);
    int nxt_l_odd = atoi(argv[4]), cnt_nxt_l_odd = atoi(argv[5]);
    int nxt_l_even = atoi(argv[6]), cnt_nxt_l_even = atoi(argv[7]);
    int front = atoi(argv[8]);

    vector<int> len(2 * n - 1);
    for (int iter = 0; iter < cnt_max_l; iter++) {
        int i = rand() % (n - max_l + 1);
        if (front) i %= 100;
        int center = i + (i + max_l - 1);
        len[center] = max_l;
    }

    for (int iter = 0; iter < cnt_nxt_l_odd; iter++) {
        int l = 0;
        while (!(l & 1)) l = rand() % (nxt_l_odd + 1);

        int i = rand() % (n - l + 1);
        int center = i + (i + l - 1);
        len[center] = max(len[center], l);
    }

    for (int iter = 0; iter < cnt_nxt_l_even; iter++) {
        int l = 1;
        while (l & 1) l = rand() % (nxt_l_even + 1);

        int i = rand() % (n - l + 1);
        int center = i + (i + l - 1);
        len[center] = max(len[center], l);
    }

    string s = construct(len, k);
    if (front == 2) reverse(s.begin(), s.end());
    return s;
}

string zero_p(char** argv) {
    int n = atoi(argv[0]), k = atoi(argv[1]);
    string s(n, 0);
    for (int i = 0; i < n; i++) s[i] = 'a' + (i % k);
    return s;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int seed = argv[1][0];
    srand(seed);

    string type = argv[2];
    if (type == "random") cout << random(argv + 3) << '\n';
    if (type == "normal") cout << normal(argv + 3) << '\n';
    if (type == "zero_p") cout << zero_p(argv + 3) << '\n';

    return 0;
}

