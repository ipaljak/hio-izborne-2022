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

const int MAXN = 500005;

int n_limit = 300000, q_limit = 300000, seed = 42069, subtask = 4;
int n, m, q;
int ea[MAXN], eb[MAXN], qa[MAXN], qb[MAXN];

bool validate () {
    if (!(2 <= n && n <= n_limit)) return 0;
    if (!(0 <= m && m <= n_limit)) return 0;
    if (!(1 <= q && q <= q_limit)) return 0;

    for (int i = 0; i < m; i++) {
        if (!(1 <= ea[i] && ea[i] <= n)) return 0;
        if (!(1 <= eb[i] && eb[i] <= n)) return 0;
        if (ea[i] == eb[i]) return 0;
    }

    for (int i = 0; i < q; i++) {
        if (!(1 <= qa[i] && qa[i] <= n)) return 0;
        if (!(1 <= qb[i] && qb[i] <= n)) return 0;
        if (qa[i] == qb[i]) return 0;
    }

    if (subtask == 2) {
        if (m % 2 == 1) return 0;
        for (int i = 1; i < m; i += 2) {
            if (ea[i - 1] != ea[i] || eb[i - 1] != eb[i]) return 0;
        }
    }

    return 1;
}

void ispis () {
    cout << n << " " << m << '\n';
    for (int i = 0; i < m; i++) {
        cout << ea[i] << " " << eb[i] << '\n';
    }
    cout << q << '\n';
    for (int i = 0; i < q; i++) {
        cout << qa[i] << " " << qb[i] << '\n';
    }
}

void gen_random_queries () {
    for (int i = 0; i < q; i++) {
        int a, b;
        while (1) {
            a = rnd(1, n);
            b = rnd(1, n);
            if (a == b) continue;
            qa[i] = a; qb[i] = b;
            break;
        }
    }
}

vector <pi> e;

void gen_edges (int lo, int hi, int br) {
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    gen_edges(lo, mid, br);
    gen_edges(mid + 1, hi, br);
    for (int i = 0; i < br; i++) {
        e.push_back({mid, mid + 1});
    }
}

void napravi_primjer (string tip) {
    if (subtask == 1) q_limit = 1;
    if (subtask == 3) n_limit = 5000;

    if (tip == "DUMMY_1") {
        n = 3; m = 3;
        ea[0] = 1; eb[0] = 2;
        ea[1] = 2; eb[1] = 3;
        ea[2] = 3; eb[2] = 1;
        q = 1;
        qa[0] = 1; qb[0] = 2;
    } else if (tip == "DUMMY_2") {
        n = 3; m = 4;
        ea[0] = 1; eb[0] = 2;
        ea[1] = 1; eb[1] = 2;
        ea[2] = 2; eb[2] = 3;
        ea[3] = 2; eb[3] = 3;
        q = 3;
        qa[0] = 1; qb[0] = 2;
        qa[1] = 2; qb[1] = 3;
        qa[2] = 3; qb[2] = 1;
    } else if (tip == "DUMMY_3") {
        n = 6; m = 7;
        ea[0] = 1; eb[0] = 2;
        ea[1] = 2; eb[1] = 3;
        ea[2] = 3; eb[2] = 4;
        ea[3] = 2; eb[3] = 5;
        ea[4] = 3; eb[4] = 5;
        ea[5] = 4; eb[5] = 5;
        ea[6] = 1; eb[6] = 3;
        q = 5;
        qa[0] = 1; qb[0] = 3;
        qa[1] = 2; qb[1] = 3;
        qa[2] = 4; qb[2] = 5;
        qa[3] = 1; qb[3] = 4;
        qa[4] = 2; qb[4] = 6;
    } else if (tip == "MALI") {
        n = 2; m = 0;
        q = 1;
        qa[0] = 1; qb[0] = 2;
    } else if (tip == "EDGE") {
        n = 2; m = 1;
        ea[0] = 1; eb[0] = 2;
        q = 1;
        qa[0] = 1; qb[0] = 2;
    } else if (tip == "DUPLI") {
        n = 2; m = 2;
        ea[0] = 1; eb[0] = 2;
        ea[1] = 1; eb[1] = 2;
        q = 1;
        qa[0] = 1; qb[0] = 2;
    } else if (tip == "PRAZAN") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = 0;
        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
    } else if (tip == "POTPUN") {
        n = 700;
        if (subtask == 3) n = 100;
        vector <pi> edges;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                edges.push_back({i, j});
            }
        }
        m = q = edges.size();
        for (int i = 0; i < m; i++) {
            ea[i] = qa[i] = edges[i].first;
            eb[i] = qb[i] = edges[i].second;
        }
        if (subtask == 1) {
            q = 1;
            gen_random_queries();
        }
    } else if (tip == "STABLO") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            ea[i - 2] = i;
            eb[i - 2] = rnd(1, i - 1);
        }
        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
    } else if (tip == "CIKLUS") {
        n = rnd(n_limit * 9 / 10, n_limit);
        m = n;
        for (int i = 2; i <= n; i++) {
            ea[i - 2] = i;
            eb[i - 2] = i - 1;
        }
        ea[n - 1] = 1;
        eb[n - 1] = n;
        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
    } else if (tip.substr(0, 6) == "RANDOM") {
        if (tip == "RANDOM_100") n = 100;
        if (tip == "RANDOM_1000") n = 1000;
        if (tip == "RANDOM_10000") n = 10000;
        if (tip == "RANDOM_100000") n = 100000;
        if (tip == "RANDOM_MAX") n = 300000;
        m = rnd(n_limit * 9 / 10, n_limit);
        for (int i = 0; i < m; i++) {
            int a, b;
            while (1) {
                a = rnd(1, n);
                b = rnd(1, n);
                if (a == b) continue;
                break;
            }
            ea[i] = a;
            eb[i] = b;
        }
        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
    } else if (tip.substr(0, 3) == "TLE") {
        int ofs = 1;
        while (ofs < n_limit) ofs *= 2; ofs /= 4;
        n = ofs;

        if (tip == "TLE_1") {
            gen_edges(1, ofs, 2);
        } else {
            for (int i = 2; i <= n; i++) {
                e.push_back({i - 1, i});
            }
        }

        m = e.size();
        for (int i = 0; i < m; i++) {
            ea[i] = e[i].first;
            eb[i] = e[i].second;
        }

        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
    } else if (tip == "PUNO") {
        n = n_limit / 10;
        int siz = 50;
        for (int i = 2; i <= n / siz; i++) {
            int a = (i - 1) * siz + 1;
            int b = rnd(0, i - 2) * siz + 1;
            e.push_back({a, b});
        }
        for (int i = 1; i <= n / siz; i++) {
            int ofs = (i - 1) * siz;
            for (int j = 0; j < siz * 9; j++) {
                int a, b;
                while (1) {
                    a = rnd(1, siz);
                    b = rnd(1, siz);
                    if (a == b) continue;
                    break;
                }
                e.push_back({ofs + a, ofs + b});
            }
        }

        m = e.size();
        for (int i = 0; i < m; i++) {
            ea[i] = e[i].first;
            eb[i] = e[i].second;
        }

        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        for (int i = 0; i < q; i++) {
            if (rnd(0, 1)) {
                int a, b;
                while (1) {
                    a = rnd(1, n);
                    b = rnd(1, n);
                    if (a == b) continue;
                    break;
                }
                qa[i] = a; qb[i] = b;
            } else {
                int a, b;
                while (1) {
                    a = rnd(1, siz);
                    b = rnd(1, siz);
                    if (a == b) continue;
                    break;
                }
                int ofs = rnd(0, n / siz - 1) * siz;
                qa[i] = ofs + a; qb[i] = ofs + b;
            }
        }
    } else if (tip == "STABLO2") {
        n = rnd(n_limit * 9 / 20, n_limit / 2);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            int a = i, b = rnd(1, i - 1);
            e.push_back({a, b});
            e.push_back({a, b});
        }
        m = e.size();
        for (int i = 0; i < m; i++) {
            ea[i] = e[i].first;
            eb[i] = e[i].second;
        }
        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
    } else if (tip == "LANAC2") {
        n = rnd(n_limit * 9 / 20, n_limit / 2);
        m = n - 1;
        for (int i = 2; i <= n; i++) {
            int a = i, b = i - 1;
            e.push_back({a, b});
            e.push_back({a, b});
        }
        m = e.size();
        for (int i = 0; i < m; i++) {
            ea[i] = e[i].first;
            eb[i] = e[i].second;
        }
        q = max(1, rnd(q_limit * 9 / 10, q_limit));
        gen_random_queries();
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
