#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 500005;

int n, m, last;
int bio[MAXN], removed[MAXN];
vector <int> v[MAXN], r[MAXN], sol, novi;

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
    oboji(last, 0);

    for (auto x : novi) {
        removed[x] = 1;
        sol.push_back(x);
        for (auto sus : r[x]) {
            removed[sus] = 1;
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        r[b].push_back(a);
    }
    while (!everyone_removed()) kosaraju();

    cout << sol.size() << endl;
    for (auto x : sol) cout << x << " ";
    return 0;
}
