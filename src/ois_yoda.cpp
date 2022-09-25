#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

vector <string> tokenizza(string line) {
    istringstream ss(line); //creo un input stream a partire da una stringa
    vector <string> t;
    string token;
    while (getline(ss,token,' ')) {
        t.push_back(token);
    }

    return t;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string s;
    getline(cin, s);
    auto x = tokenizza(s);

    for (int i = x.size() - 1; i >= 0; i--) {
        cout << x[i] << " ";
    }

    cout << "\n";
}
