#include <bits/stdc++.h>

#define MAXN 3001
#define INF 1000000000

using namespace std;

int N, counter, mst;
int dist[MAXN], X[MAXN], Y[MAXN];
bool tree[MAXN+5];

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    
    in >> N;

    char c;

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            in >> c;
            if(c == 'T')
            {
                X[counter] = i;
                Y[counter] = j;
                counter++;
            }
        }
    }

    //cout << counter;

    int index = 0, choice = 0, w = INF;

    tree[0] = 1;     

    for(int i = 1; i < counter; i++)
    {
        dist[i] = (X[i]-X[0])*(X[i]-X[0]) + (Y[i]-Y[0])*(Y[i]-Y[0]);
        if(dist[i] < w)
        {
            w = dist[i];
            choice = i;
        }
    }

    index = choice;

    for(int nodi = 1; nodi < counter; nodi++)
    {
        tree[index] = 1;
        //cout << "x" << w << "x";
        mst += w;
        w = INF;

        for(int i = 0; i < counter; i++)
        {
            if(!tree[i])
            {
                dist[i] = min(dist[i], (X[i]-X[index])*(X[i]-X[index]) + (Y[i]-Y[index])*(Y[i]-Y[index]));
                if(dist[i] < w)
                {
                    w = dist[i];
                    choice = i;
                }
            }
        }
        
        index = choice;
    }

    out << mst;
}