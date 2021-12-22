#include <bits/stdc++.h>
//#include <unistd.h> //sleep(unsinged int seconds);
using namespace std;

int main(){
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int b, g, t, n;
    string word;
    set <string> bad, good;
    cin >> b;
    for(int i = 0; i < b; i++){
        cin >> word;
        bad.insert(word);
    }
    cin >> g;
    for(int i = 0; i < g; i++){
        cin >> word;
        good.insert(word);
    }
    cin >> t;
    int ansGood = 0, ansBad = 0;
    while(t--){
        cin >> n;
        bool isGood = 0, isBad = 0;
        for(int i = 0; i < n; i++){
            cin >> word;
            if(bad.find(word) != bad.end()) isBad = 1;
            if(good.find(word) != good.end()) isGood = 1;
        }
        ansBad += (isBad && !isGood);
        ansGood += (isGood && !isBad);
    }
    cout << ansBad << " " << ansGood << "\n";
} 