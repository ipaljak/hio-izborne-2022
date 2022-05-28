#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 500005;

int n, m;
int deg[MAXN], removed[MAXN];
vector <int> v[MAXN], r[MAXN], sol;

queue <int> q;

void makni (int node) {
    removed[node] = 1;
    for (auto sus : r[node]) {
        deg[sus]--;
        if (deg[sus] == 0) q.push(sus);
    }
}

void dfs (int node, int boja) {
    if (removed[node]) return;
    removed[node] = 1;
    if (boja == 1) sol.push_back(node);
    for (auto sus : v[node]) dfs(sus, !boja);
    for (auto sus : r[node]) dfs(sus, !boja);
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

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (removed[x]) continue;
        removed[x] = 1;
        sol.push_back(x);
        for (auto sus : r[x]) {
            if (!removed[sus]) makni(sus);
        }
    }

    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
    }

    cout << sol.size() << endl;
    for (auto x : sol) cout << x << " ";
    return 0;
}
