#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

//////////////////////////////////////////////////////////////////////////
mt19937 rng;

int rnd (int lo, int hi) {
    return uniform_int_distribution<int>(lo, hi)(rng);
}

void good_shuffle (vector <int> &v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        swap(v[i], v[rnd(0, i)]);
    }
}

void good_shuffle (vector <pi> &v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        swap(v[i], v[rnd(0, i)]);
    }
}
//////////////////////////////////////////////////////////////////////////


//helper functions


//////////////////////////////////////////////////////////////////////////

const int MAXN = 500005;

int n_limit = 500000, seed = 42069, subtask = 4;
int n, m;
vector <int> v[MAXN], r[MAXN], g[MAXN], all_nodes;
vector <pi> edges;

/////////////////////////////////////////////////////////////

void build_adjacency_list () {
    for (int i = 1; i <= n; i++) {
        all_nodes.push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        v[a].push_back(b);
        r[b].push_back(a);
        g[a].push_back(b);
        g[b].push_back(a);
    }
}

int bio[MAXN];
vector < vector <int> > comp;
vector <int> curr_comp, st;

void dfs (int node) {
    if (bio[node]) return;
    bio[node] = 1;
    for (auto sus : r[node]) {
        if (!bio[sus]) dfs(sus);
    }
    st.push_back(node);
}

void dfs2 (int node) {
    if (bio[node] == 2) return;
    bio[node] = 2;
    curr_comp.push_back(node);
    for (auto sus : v[node]) {
        if (bio[sus] == 1) dfs2(sus);
    }
}

void kosaraju () {
    for (int i = 1; i <= n; i++) {
        if (!bio[i]) dfs(i);
    }
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        if (bio[x] == 2) continue;
        curr_comp.clear();
        dfs2(x);
        comp.push_back(curr_comp);
    }
}

//////////////////////////////////////////////////////////////////////////

int active[MAXN], col[MAXN], can_color;

void oboji (int node, int boja) {
    col[node] = boja;
    for (auto sus : g[node]) {
        if (!active[sus]) continue;
        if (col[sus] == 0) {
            oboji(sus, 3 - boja);
        } else {
            if (col[sus] != 3 - boja) can_color = 0;
        }
    }
}

bool is_bipartite (vector <int> nodes) {
    for (auto node : nodes) active[node] = 1;
    can_color = 1;
    for (auto node : nodes) {
        if (col[node] == 0) oboji(node, 1);
    }
    for (auto node : nodes) active[node] = 0;
    return can_color;
}

bool has_no_odd_cycle () {
    for (int i = 0; i < comp.size(); i++) {
        if (!is_bipartite(comp[i])) return 0;
    }
    return 1;
}

bool is_dag () {
    return (comp.size() == n);
}

bool validate () {
    if (!(1 <= n && n <= n_limit)) return 0;
    if (!(0 <= m && m <= n_limit)) return 0;
    if (!(m == edges.size())) return 0;

    set <pi> edge_set;
    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        if (!(1 <= a && a <= n)) return 0;
        if (!(1 <= b && b <= n)) return 0;
        if (a == b) return 0;
        edge_set.insert(edges[i]);
    }
    if (edge_set.size() != m) return 0;

    build_adjacency_list();
    kosaraju();

    if (!has_no_odd_cycle()) return 0;
    if (subtask == 1 && !is_dag()) return 0;
    if (subtask == 2 && !is_bipartite(all_nodes)) return 0;

    return 1;
}

//////////////////////////////////////////////////////////////////////////

int total_n, total_m;
vector <pi> total_edges;

void add_test_case () {
    for (auto pp : edges) {
        int a = pp.first, b = pp.second;
        total_edges.push_back({total_n + a, total_n + b});
    }
    total_n += n;
    total_m += m;

    n = m = 0;
    edges.clear();
}

void create_single_test_case () {
    n = total_n; m = total_m;
    edges = total_edges;
}

//////////////////////////////////////////////////////////////////////////

void ispis () {
    cout << n << " " << m << '\n';
    for (int i = 0; i < m; i++) {
        cout << edges[i].first << " " << edges[i].second << '\n';
    }
}

void napravi_primjer (string tip) {
    if (subtask == 3) n_limit = 5000;

    if (tip == "DUMMY_1") {
        n = 4; m = 4;
        edges.push_back({1, 2});
        edges.push_back({1, 3});
        edges.push_back({2, 4});
        edges.push_back({3, 4});
    } else if (tip == "DUMMY_2") {
        n = 4; m = 4;
        edges.push_back({1, 2});
        edges.push_back({2, 3});
        edges.push_back({3, 4});
        edges.push_back({4, 1});
    } else if (tip == "DUMMY_3") {
        n = 8; m = 11;
        edges.push_back({1, 2});
        edges.push_back({2, 1});
        edges.push_back({3, 4});
        edges.push_back({4, 5});
        edges.push_back({5, 6});
        edges.push_back({6, 3});
        edges.push_back({7, 8});
        edges.push_back({8, 7});
        edges.push_back({3, 2});
        edges.push_back({7, 3});
        edges.push_back({8, 1});
    } else if (tip == "LANAC") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n - 1;
        for (int i = 1; i < n; i++) {
            edges.push_back({i, i + 1});
        }
    } else if (tip == "LANCI") {
        for (int j = 0; j < 10; j++) {
            n = rnd((n_limit / 10) * 9 / 10, (n_limit / 10));
            m = n - 1;
            for (int i = 1; i < n; i++) {
                edges.push_back({i, i + 1});
            }
            add_test_case();
        }
        create_single_test_case();
    } else if (tip == "CVOR") {
        n = 1; m = 0;
    } else if (tip == "IZOLIRANI") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = 0;
    } else if (tip == "EDGEVI") {
        n = rnd(n_limit * 9 / 10, n_limit) / 2 * 2;
        m = n / 2;
        for (int i = 1; i <= n; i += 2) {
            edges.push_back({i, i + 1});
        }
    } else if (tip == "ZVIJEZDA1") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            edges.push_back({1, i});
        }
    } else if (tip == "ZVIJEZDA2") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            edges.push_back({i, 1});
        }
    } else if (tip == "ZVIJEZDA3") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            if (rnd(0, 1)) edges.push_back({i, 1}); else edges.push_back({1, i});
        }
    } else if (tip.substr(0, 6) == "STABLO") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            int a = i, b = rnd(1, i - 1);
            if (tip == "STABLO2" || tip == "STABLO3" && rnd(0, 1)) swap(a, b);
            edges.push_back({a, b});
        }
    } else if (tip.substr(0, 10) == "RANDOM_DAG" || tip == "GUSTO_DAG") {
        int tc = 0;
        if (tip == "RANDOM_DAG1") tc = 1;
        if (tip == "RANDOM_DAG2") tc = 10;
        if (tip == "RANDOM_DAG3") tc = 100;
        if (tip == "RANDOM_DAG4") tc = 1000;
        if (tip == "RANDOM_DAG5") tc = 10000;
        if (tip == "GUSTO_DAG") tc = 100;

        for (int j = 0; j < tc; j++) {
            n = rnd((n_limit / tc) * 9 / 10, (n_limit / tc));
            m = n;

            if (tip == "GUSTO_DAG") {
                n = rnd(90, 100);
                if (subtask == 3) n = rnd(9, 10);
                m = rnd(0, n * (n - 1) / 2);
            }

            set <pi> bridovi;
            for (int i = 0; i < m; i++) {
                while (1) {
                    int a = rnd(1, n);
                    int b = rnd(1, n);
                    if (a == b) continue;
                    if (a > b) swap(a, b);
                    if (bridovi.find({a, b}) != bridovi.end()) continue;
                    bridovi.insert({a, b});
                    edges.push_back({a, b});
                    break;
                }
            }
            add_test_case();
        }

        create_single_test_case();
    } else if (tip == "POTPUN") {
        n = 1000;
        m = n * (n - 1) / 2;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                edges.push_back({i, j});
            }
        }
    } else if (tip.substr(0, 17) == "RANDOM_BIPARTITAN" || tip == "GUSTO_BIPARTITAN") {
        int tc = 0;
        if (tip == "RANDOM_BIPARTITAN1") tc = 1;
        if (tip == "RANDOM_BIPARTITAN2") tc = 10;
        if (tip == "RANDOM_BIPARTITAN3") tc = 100;
        if (tip == "RANDOM_BIPARTITAN4") tc = 1000;
        if (tip == "RANDOM_BIPARTITAN5") tc = 10000;
        if (tip == "GUSTO_BIPARTITAN") tc = 100;

        for (int j = 0; j < tc; j++) {
            n = rnd((n_limit / tc) * 9 / 10, (n_limit / tc)) / 2 * 2;
            m = n;

            if (tip == "GUSTO_BIPARTITAN") {
                n = rnd(90, 100);
                if (subtask == 3) n = rnd(9, 10);
                m = rnd(0, (n / 2) * ((n + 1) / 2) * 2);
            }

            set <pi> bridovi;
            for (int i = 0; i < m; i++) {
                while (1) {
                    int a = rnd(1, n / 2);
                    int b = rnd(1, (n + 1) / 2) + n / 2;
                    if (rnd(0, 1)) swap(a, b);
                    if (bridovi.find({a, b}) != bridovi.end()) continue;
                    bridovi.insert({a, b});
                    edges.push_back({a, b});
                    break;
                }
            }
            add_test_case();
        }

        create_single_test_case();
    } else if (tip.substr(0, 14) == "SCC_BIPARTITAN") {
        int tc_limit = 50;
        int dag_node = 100;
        int more_edges = 50;
        if (subtask == 3) {
            tc_limit /= 10;
            dag_node /= 10;
            more_edges /= 10;
        }

        for (int tc_num = 0; tc_num < tc_limit; tc_num++) {
            for (int i = 1; i <= dag_node; i++) {
                int node = (i - 1) * 10 + 1;

                set <pi> bridovi;
                for (int j = 0; j < 10; j++) {
                    int a = node + j;
                    int b = node + (j + 1) % 10;
                    bridovi.insert({a, b});
                    edges.push_back({a, b});
                }

                for (int j = 0; j < more_edges; j++) {
                    int a = node + rnd(0, 9);
                    int b = node + rnd(0, 9);
                    if (((int) abs(a - b)) % 2 == 0 || bridovi.find({a, b}) != bridovi.end()) continue;
                    bridovi.insert({a, b});
                    edges.push_back({a, b});
                }

                if (tip == "SCC_BIPARTITAN_STABLO") {
                    if (i > 1) {
                        int rod = (rnd(1, i - 1) - 1) * 10 + 1;
                        if (rnd(0, 1)) edges.push_back({rod, node}); else edges.push_back({node, rod});
                    }
                }
            }

            if (tip == "SCC_BIPARTITAN_DAG") {
                set <pi> bridovi;
                for (int i = 0; i < more_edges * 10; i++) {
                    int a = rnd(0, dag_node - 1) * 10 + 1;
                    int b = rnd(0, dag_node - 1) * 10 + 1;
                    if (a == b) continue;
                    if (a > b) swap(a, b);
                    if (bridovi.find({a, b}) != bridovi.end()) continue;
                    bridovi.insert({a, b});
                    edges.push_back({a, b});
                }
            }

            n = dag_node * 10;
            m = edges.size();
            add_test_case();
        }
        create_single_test_case();
    } else if (tip == "CIKLUS") {
        n = rnd(n_limit * 9 / 10, n_limit) / 2 * 2;
        m = n;
        for (int i = 1; i < n; i++) {
            edges.push_back({i, i + 1});
        }
        edges.push_back({n, 1});
    } else if (tip == "CIKLUSI") {
        for (int j = 0; j < 10; j++) {
            n = rnd((n_limit / 10) * 9 / 10, (n_limit / 10)) / 2 * 2;
            m = n;
            for (int i = 1; i < n; i++) {
                edges.push_back({i, i + 1});
            }
            edges.push_back({n, 1});
            add_test_case();
        }
        create_single_test_case();
    } else if (tip == "SPECIAL") {
        n = n_limit / 10 * 2;
        for (int i = 1; i <= n; i += 2) {
            edges.push_back({i, i + 1});
            edges.push_back({i + 1, i});
            if (i - 2 > 0) {
                edges.push_back({i - 2, i});
                edges.push_back({i - 2, i + 1});
                edges.push_back({i - 1, i});
                edges.push_back({i - 1, i + 1});
            }
            if (i - 4 > 0) {
                edges.push_back({i - 4, i});
                edges.push_back({i - 4, i + 1});
                edges.push_back({i - 3, i});
                edges.push_back({i - 3, i + 1});
            }
        }
        m = edges.size();
    }

    if (!validate()) {
        cerr << tip << " not valid!" << endl;
        exit(0);
    } else {
        cerr << tip << " is ok!" << endl;
    }
    ispis();
}

int main (int argc, char *argv[]) {
    assert(argc == 2 || argc == 3 || argc == 4);
    if (argc >= 3) subtask = atoi(argv[2]);
    if (argc >= 4) seed = atoi(argv[3]);
    rng.seed(seed);
    napravi_primjer(argv[1]);
    return 0;
}
