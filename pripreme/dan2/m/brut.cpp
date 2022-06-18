#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 5005;

int n, m, q;
int ea[MAXN], eb[MAXN], qa[MAXN], qb[MAXN], sol[MAXN];
int bio[MAXN], dub[MAXN], link[MAXN], most[MAXN], comp[MAXN];
vector <pi> v[MAXN];
vector <int> nodes;

void dfs (int x, int rod) {
    bio[x] = 1;
    if (rod == 0) dub[x] = 0; else dub[x] = 1 + dub[rod];
    link[x] = dub[x];

    int pe = -1;
    for (auto pp : v[x]) {
        int sus = pp.first, idx = pp.second;
        if (sus == rod) {
            pe = idx;
            continue;
        }
        if (!bio[sus]) {
            dfs(sus, x);
            link[x] = min(link[x], link[sus]);
        } else {
            link[x] = min(link[x], dub[sus]);
        }
    }

    if (pe != -1 && link[x] == dub[x]) most[pe] = 1;
}

void oboji (int x, int col) {
    comp[x] = col;
    for (auto pp : v[x]) {
        int sus = pp.first, idx = pp.second;
        if (most[idx]) continue;
        if (comp[sus] == 0) oboji(sus, col);
    }
}

void find_components () {
    for (auto x : nodes) {
        if (!bio[x]) dfs(x, 0);
    }
    for (auto x : nodes) {
        if (comp[x] == 0) oboji(x, x);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ea[i] >> eb[i];
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qa[i] >> qb[i];
        sol[i] = m;
    }
    for (int i = 1; i <= n; i++) {
        nodes.push_back(i);
    }
    for (int i = 0; i < m; i++) {
        for (auto x : nodes) {
            bio[x] = 0;
            comp[x] = 0;
        }
        for (int j = 0; j <= i; j++) {
            most[j] = 0;
        }
        v[ea[i]].push_back({eb[i], i});
        v[eb[i]].push_back({ea[i], i});
        find_components();
        for (int j = 0; j < q; j++) {
            if (comp[qa[j]] == comp[qb[j]]) sol[j] = min(sol[j], i);
        }
    }
    for (int i = 0; i < q; i++) {
        if (sol[i] == m) cout << -1 << '\n'; else cout << sol[i] + 1 << '\n';
    }
    return 0;
}
