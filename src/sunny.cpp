#include <fstream>
#include <vector>
#define MAX 50000
using namespace std;
typedef pair<int, int> pii;

vector <pii> graph[MAX + 1];
bool vis[MAX + 1];
int n, m, h, s;
int v1, v2, luce;

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    in >> n >> m >> h >> s;
    for(int i = 0; i < m; i++) {
        in >> v1 >> v2 >> luce;
        graph[v1].push_back({v2, luce});
        graph[v2].push_back({v1, luce});
    }

    int pos = h, counter = 0;
    while(!vis[pos] && pos != s) {
        vis[pos] = 1;
        counter++;
        int nodo = graph[pos][0].first;
        int luce = graph[pos][0].second;
        for(int i = 1; i < graph[pos].size(); i++) {
            if(graph[pos][i].second < luce) {
                luce = graph[pos][i].second;
                nodo = graph[pos][i].first;
            }
        }
        pos = nodo;
    }

    if(pos == s)
        out << counter;
    else
        out << -1;

    in.close();
    out.close();
}
