#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        string n;
        cin >> n;
        vector<int> answers;
        
        int len = n.size();
        long long sum_digits = 0;
        for (char c : n) sum_digits += (c - '0');
        
        int last_digit = n.back() - '0';
        int last_two = (len >= 2) ? stoi(n.substr(len - 2)) : stoi(n);

        bool div2 = (last_digit % 2 == 0);
        if (div2) answers.push_back(2);

        bool div3 = (sum_digits % 3 == 0);
        if (div3) answers.push_back(3);

        if (last_two % 4 == 0) answers.push_back(4);

        if (last_digit == 0 || last_digit == 5) answers.push_back(5);

        if (div2 && div3) answers.push_back(6);

        if (answers.empty()) {
            cout << "-1" << endl;
        } else {
            for (int i = 0; i < answers.size(); i++) {
                cout << answers[i] << (i == answers.size() - 1 ? "" : " ");
            }
            cout << endl;
        }
    }
    return 0;
}