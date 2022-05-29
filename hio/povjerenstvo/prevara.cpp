#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 500005;

int n, m, last;
int deg[MAXN], bio[MAXN], removed[MAXN];
vector <int> v[MAXN], r[MAXN], sol, novi;

queue <int> q;

bool everyone_removed () {
    for (int i = 1; i <= n; i++) {
        if (!removed[i]) return 0;
    }
    return 1;
}

void dfs (int node) {
    if (bio[node]) return;
    bio[node] = 1;
    for (auto sus : r[node]) {
        if (!removed[sus] && !bio[sus]) dfs(sus);
    }
    last = node;
}

void oboji (int node, int boja) {
    bio[node] = 2;
    if (boja == 0) novi.push_back(node);
    for (auto sus : v[node]) {
        if (!removed[sus] && bio[sus] == 1) oboji(sus, !boja);
    }
}

void makni (int node, int flg) {
    removed[node] = 1;
    for (auto sus : r[node]) {
        deg[sus]--;
        if (deg[sus] == 0 && flg) q.push(sus);
    }
}

void izaberi (int node, int flg) {
    removed[node] = 1;
    sol.push_back(node);
    for (auto sus : r[node]) {
        if (!removed[sus]) makni(sus, flg);
    }
}

void remove_terminal_nodes (vector <int> nodes) {
    for (auto node : nodes) {
        if (removed[node]) continue;
        if (deg[node] == 0) q.push(node);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (removed[node]) continue;
        izaberi(node, 1);
    }
}

void kosaraju () {
    last = 0;
    novi.clear();
    for (int i = 1; i <= n; i++) {
        bio[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (removed[i]) continue;
        dfs(i);
    }
    if (last == 0) return;
    oboji(last, 0);

    for (auto x : novi) {
        izaberi(x, 0);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        deg[a]++;
        v[a].push_back(b);
        r[b].push_back(a);
    }
    vector <int> all_nodes;
    for (int i = 1; i <= n; i++) all_nodes.push_back(i);
    while (!everyone_removed()) {
        remove_terminal_nodes(all_nodes);
        kosaraju();
    }

    cout << sol.size() << endl;
    for (auto x : sol) cout << x << " ";
    return 0;
}
