#include <bits/stdc++.h>

#define MAXN 100000

using namespace std;

int n;
int prefix[MAXN];
int monete[MAXN];
int maxGuadagno[MAXN];

int main() {

    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> n;

    for(int i = 0; i < n; i++) {
        int temp;
        in >> temp;
        switch(temp)
        {
            case 0:
                monete[i] = 1;
                break;
            case 1:
                monete[i] = 3;
                break;
            case 2:
                monete[i] = 5;
                break;
        }
    }

    prefix[0] = monete[0];

    for(int i = 1; i < n; i++) prefix[i] = prefix[i-1] + monete[i];

    maxGuadagno[0] = prefix[0];
    maxGuadagno[1] = prefix[1];
    maxGuadagno[2] = prefix[2];

    for(int i = 3; i < n; i++)
        maxGuadagno[i] = prefix[i] - fmin(fmin(maxGuadagno[i-1], maxGuadagno[i-2]), maxGuadagno[i-3]);

    out << maxGuadagno[n-1] << "00";

    in.close();
    out.close();
}
