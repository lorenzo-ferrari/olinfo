#include <bits/stdc++.h>
#define MAX 30
using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

vector <int> graph[MAX];
int tramite[MAX];
int stato[MAX];
queue <int> Q;

int main()
{
    int n, m; in >> n >> m;
    int v1, v2;
    for(int i = 0; i < m; i++) {
        in >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    stato[0] = 1;
    Q.push(0);
    while(!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for(int i = 0; i < graph[cur].size(); i++) {
                int temp = graph[cur][i];
            if(stato[temp] == 0) {
                Q.push(temp);
                tramite[temp] = cur;
                stato[temp] = (stato[cur] % 2) + 1;
            }
            else if(stato[temp] == stato[cur]) {
                vector <int> v;
                int pos = temp;
                while(pos != 0) {
                    v.push_back(pos);
                    pos = tramite[pos];
                }
                v.push_back(0);
                reverse(v.begin(), v.end());
                pos = cur;
                while(pos != 0) {
                    v.push_back(pos);
                    pos = tramite[pos];
                }
                v.push_back(0);
                out << v.size() - 1 << endl;
                for(int i = 0; i < v.size(); i++)
                    out << v[i] << " ";

                return 0;
            }
        }
    }

    in.close();
    out.close();
}
