#include <iostream>

using namespace std;

int main() {
    int n, odgovor;
    cin >> n;

    cout << "? 1 1" << endl;
    cout.flush();
    cin >> odgovor;

    cout << "? 2 3" << endl;
    cout.flush();
    cin >> odgovor;

    cout << "? 2 4" << endl;
    cout.flush();
    cin >> odgovor;

    cout << "? 3 5" << endl;
    cout.flush();
    cin >> odgovor;

    cout << "? 1 5" << endl;
    cout.flush();
    cin >> odgovor;

    cout << "! 5" << endl;
    cout.flush();

    return 0;
}
