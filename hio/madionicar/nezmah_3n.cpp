#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

int n, sol;

bool pitaj (int lef, int rig) {
    if (lef == rig) return 1;
    cout << "? " << lef << " " << rig << endl;
    int res;
    cin >> res;
    return res;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int idx = 1;
    for (int i = 2; i <= n; i++) {
        if (idx - 1 >= 1 && pitaj(idx - 1, i)) {
            idx--;
        } else {
            while (!pitaj(idx, i)) idx++;
        }
        sol = max(sol, i - idx + 1);
    }
    cout << "! " << sol;
    return 0;
}
