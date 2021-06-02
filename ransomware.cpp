#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;

int N;
string contacts[MAXN];
string codes[10];

bool compara(string s1, string s2) {
    if(s1.size() != s2.size())
        return 0;
    for(int i = 0; i < s1.size(); i++)
        if(s1[i] != s2[i])
            return 0;
    return 1;
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> contacts[i];
    for (int i = 0; i < 10; i++)
        cin >> codes[i];

    for(int i = 0; i < N; i++) {
        string temp;
        for(int j = 0; j < contacts[i].size(); j++) {
            temp.push_back(contacts[i][j]);
            for(int k = 0; k < 10; k++) {
                if(compara(temp, codes[k])) {
                    temp.clear();
                    cout << k;
                }
            }
        }
        cout << "\n";
    }

    return 0;
}
