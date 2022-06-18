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

vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
int bridges;
int lca_iteration;
vector<int> last_visit;

vector<pair<int, pii>> history;
int hist_t = 0;

void init(int n) {
    par.resize(n);
    dsu_2ecc.resize(n);
    dsu_cc.resize(n);
    dsu_cc_size.resize(n);
    lca_iteration = 0;
    last_visit.assign(n, 0);
    for (int i=0; i<n; ++i) {
        dsu_2ecc[i] = i;
        dsu_cc[i] = i;
        dsu_cc_size[i] = 1;
        par[i] = -1;
    }
    bridges = 0;
}

int find_2ecc(int v) {
    if (v == -1)
        return -1;
    return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}

int find_cc(int v) {
    v = find_2ecc(v);
    return dsu_cc[v] == v ? v : dsu_cc[v] = find_cc(dsu_cc[v]);
}

void make_root(int v) {
    v = find_2ecc(v);
    int root = v;
    int child = -1;
    while (v != -1) {
        int p = find_2ecc(par[v]);
        par[v] = child;
        dsu_cc[v] = root;
        child = v;
        v = p;
    }
    dsu_cc_size[root] = dsu_cc_size[child];
}

void merge_path (int a, int b) {
    ++lca_iteration;
    vector<int> path_a, path_b;
    int lca = -1;
    while (lca == -1) {
        if (a != -1) {
            a = find_2ecc(a);
            path_a.push_back(a);
            if (last_visit[a] == lca_iteration){
                lca = a;
                break;
                }
            last_visit[a] = lca_iteration;
            a = par[a];
        }
        if (b != -1) {
            b = find_2ecc(b);
            path_b.push_back(b);
            if (last_visit[b] == lca_iteration){
                lca = b;
                break;
                }
            last_visit[b] = lca_iteration;
            b = par[b];
        }
    }

    for (int v : path_a) {
        dsu_2ecc[v] = lca;
        history.push_back({hist_t, {v, lca}});
        if (v == lca)
            break;
        --bridges;
    }
    for (int v : path_b) {
        dsu_2ecc[v] = lca;
        history.push_back({hist_t, {v, lca}});
        if (v == lca)
            break;
        --bridges;
    }
}

void add_edge(int a, int b) {
    a = find_2ecc(a);
    b = find_2ecc(b);
    if (a == b)
        return;

    int ca = find_cc(a);
    int cb = find_cc(b);

    if (ca != cb) {
        ++bridges;
        if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
            swap(a, b);
            swap(ca, cb);
        }
        make_root(a);
        par[a] = dsu_cc[a] = b;
        dsu_cc_size[cb] += dsu_cc_size[a];
    } else {
        merge_path(a, b);
    }
}


const int MAXN = 1e6 + 10;
int dad[MAXN];
set<int> comp[MAXN];
set<pii> queries[MAXN];
int find_dad(int x) { if (x == dad[x]) return x; return dad[x] = find_dad(dad[x]); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    init(n);

    while (m--) {
        int x, y;
        cin >> x >> y;
        x--; y--;

        hist_t++;
        add_edge(x, y);
    }


    for (int i = 0; i < n; i++) {
        dad[i] = i;
        comp[i] = {i};
    }


    int q;
    cin >> q;

    vi sol(q, -1);

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (x == y) sol[i] = 0;
        else {
            queries[x].insert({y, i});
            queries[y].insert({x, i});
        }
    }

    for (auto& it : history) {
        int t = it.fi, x = it.se.fi, y = it.se.se;
        x = find_dad(x); y = find_dad(y);
        if (x == y) continue;
        if (comp[x].size() < comp[y].size()) swap(x, y);

        for (auto& [z, qid] : queries[y]) {
            if (comp[x].count(z)) sol[qid] = t;
            else queries[x].insert({z, qid});
        }
        for (int z : comp[y]) {
            dad[z] = x;
            comp[x].insert(z);
        }
    }

    for (int i = 0; i < q; i++)
        cout << sol[i] << '\n';

    return 0;
}

