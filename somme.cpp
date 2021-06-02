#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
#define MAXN 100000
//da fare con priority_queue, sommare sempre i minori
using namespace std;

priority_queue<long long, vector<long long>, greater<long long> > pq;
int n;
long long costo = 0;

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> n;
    for(int i=0; i<n; i++) {
        int temp;
        in >> temp;
        pq.push(temp);
    }

    while(pq.size() >= 2) {
        int v1 = pq.top();
        pq.pop();
        int v2 = pq.top();
        pq.pop();
        costo += v1 + v2;
        pq.push(v1+v2);
    }

    out << costo;

    in.close();
    out.close();
}
