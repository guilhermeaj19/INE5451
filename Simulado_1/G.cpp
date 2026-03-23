#include <bits/stdc++.h>

using namespace std;



int main() {
    int N;

    cin >> N;

    for (int i = 0; i < N; i++) {
        cout << 1 << endl;
        cout.flush();

        int response;
        cin >> response;

        if (response == 2) {
            cout << 3 << endl;
            cout.flush();
        } else {
            cout << 2 << endl;
            cout.flush();
        }

        cin >> response;

    }

}