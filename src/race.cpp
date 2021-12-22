#include <fstream>
#include <algorithm>
#define MAXN 1<<16
using namespace std;
pair<int, int> v[MAXN];
int incr[MAXN];
bool comp(pair<int, int> a, pair<int, int> b)
{
    return (a.first > b.first || (a.first == b.first && a.second > b.second));
}
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n; in >> n;
    for(int i = 0; i < n; i++) {
        in >> v[i].first >> incr[i];
        v[i].second = i;
    }
    int temp = n;
    while(temp != 1) {
        for(int i = 0; i < temp; i++) v[i].first += incr[v[i].second];
        sort(v, v + temp, comp);
        temp /= 2;
    }
    out << v[0].second;

    in.close();
    out.close();

}
