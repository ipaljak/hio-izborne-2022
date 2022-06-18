#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 500005;

int n, m, q;
int ea[MAXN], eb[MAXN], qa[MAXN], qb[MAXN], sol[MAXN];
int bio[MAXN], dub[MAXN], link[MAXN], most[MAXN], comp[MAXN];
vector <pi> v[MAXN];
vector <int> nodes;

void dfs (int x, int pe) {
    bio[x] = 1;
    if (pe == -1) dub[x] = 0;
    link[x] = dub[x];

    for (auto pp : v[x]) {
        int sus = pp.first, idx = pp.second;
        if (idx == pe) continue;
        if (!bio[sus]) {
            dub[sus] = 1 + dub[x];
            dfs(sus, idx);
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
        if (!bio[x]) dfs(x, -1);
    }
    for (auto x : nodes) {
        if (comp[x] == 0) oboji(x, x);
    }
}

void solve (int lo, int hi, vector <int> edges, vector <int> queries) {
    if (queries.empty()) return;
    /*cout << "sad na " << lo << " " << hi << endl;
    cout << "edges: "; for (auto i : edges) cout << i << " "; cout << endl;
    cout << "quers: "; for (auto i : queries) cout << i << " "; cout << endl;*/

    int mid = (lo + hi) / 2;

    nodes.clear();
    for (auto i : edges) {
        nodes.push_back(ea[i]);
        nodes.push_back(eb[i]);
    }
    for (auto i : queries) {
        nodes.push_back(qa[i]);
        nodes.push_back(qb[i]);
    }

    for (auto x : nodes) {
        v[x].clear();
        bio[x] = 0;
        comp[x] = 0;
    }
    for (auto i : edges) {
        if (i <= mid) {
            v[ea[i]].push_back({eb[i], i});
            v[eb[i]].push_back({ea[i], i});
            most[i] = 0;
        }
    }

    find_components();

    vector <int> e_lef, e_rig, q_lef, q_rig;
    for (auto i : edges) {
        if (i <= mid && !most[i]) {
            e_lef.push_back(i);
        } else {
            ea[i] = comp[ea[i]];
            eb[i] = comp[eb[i]];
            e_rig.push_back(i);
        }
    }
    for (auto i : queries) {
        if (comp[qa[i]] == comp[qb[i]]) {
            q_lef.push_back(i);
        } else {
            qa[i] = comp[qa[i]];
            qb[i] = comp[qb[i]];
            q_rig.push_back(i);
        }
    }

    if (lo <= mid - 1) {
        solve(lo, mid - 1, e_lef, q_lef);
    } else {
        for (auto i : q_lef) sol[i] = mid;
    }

    if (mid + 1 <= hi) {
        solve(mid + 1, hi, e_rig, q_rig);
    } else {
        for (auto i : q_rig) sol[i] = mid + 1;
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector <int> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> ea[i] >> eb[i];
        edges[i] = i;
    }
    cin >> q;
    vector <int> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> qa[i] >> qb[i];
        if (m == 0) cout << -1 << '\n';
        queries[i] = i;
    }
    if (m == 0) return 0;
    solve(0, m - 1, edges, queries);
    for (int i = 0; i < q; i++) {
        if (sol[i] == m) cout << -1 << '\n'; else cout << sol[i] + 1 << '\n';
    }
    return 0;
}
