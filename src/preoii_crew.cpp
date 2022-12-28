#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    for (int i = 0; i <= n; ++i) {
        cout << "0 ";
        for (int j = 1; j <= n; ++j) {
            cout << i*n + j << " ";
        }
        cout << "\n";
    }

    for (int i = 1; i <= n; ++i) {
        int sh = i-1;
        for (int j = 0; j < n; ++j) {
            cout << i << " ";
            for (int k = 0; k < n; ++k) {
                cout << (n+1) + k*n + (j + k * sh) % n << " ";
            }
            cout << "\n";
        }
    }
}

/*

run.sh:

#!/bin/bash
for i in $(seq 0 9)
do
    echo "running on input_00$i"
    ./x < input/input_00$i.txt > output/output_00$i.txt
done

*/
