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

    cout << sol.size() << endl;
    for (auto x : sol) cout << x << " ";
    return 0;
}
