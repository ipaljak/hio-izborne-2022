#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int N = 5000;

int n, m, q;
int bio[N + 5][N + 5];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(0) * getpid());
    n = rand() % N + 1;
    m = rand() % (min(n * (n - 1) / 2 + 1, 5000));
    q = rand() % N + 1;

    cout << n << " " << m << endl;
    for (int i = 0; i < m; i++) {
        int a, b;
        while (1) {
            a = rand() % n + 1;
            b = rand() % n + 1;
            if (a == b || bio[a][b]) continue;
            bio[a][b] = bio[b][a] = 1;
            cout << a << " " << b << endl;
            break;
        }
    }
    cout << q << endl;
    for (int i = 0; i < q; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        cout << a << " " << b << endl;
    }
    return 0;
}
