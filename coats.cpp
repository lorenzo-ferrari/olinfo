#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    int n, one = 0, two = 0;
    cin >> n;
    while (n--) {
        int a;
        cin >> a;
        if (a == 1) one++;
        if (a == 2) two++;
    }

    cout << fixed << setprecision(8) << (double)two*(two + 1)/(2.0*(one + 2*two)) << "\n";
}