#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, m, somma = 0;
vector <pair<int, int>> potenza;
int prese[3] { };

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> n >> m;
    for(int i = 0; i < n; i++)
    {
        int temp;
        in >> temp;
        potenza.push_back(make_pair(temp, 0));
    }
    for(int i = 0; i < n; i++)
    {
        char temp[10];
        in >> temp;
        if(temp[2] == '0')
            potenza[i].second = 0;
        else if(temp[2] == '6')
            potenza[i].second = 1;
    }
    for(int i = 0; i  < m; i++)
    {
        char temp[10];
        in >> temp;
        if(temp[2] == '0')
            prese[0]++;
        else if(temp[2] == '6')
            prese[1]++;
        else if(temp[2] == 'p')
            prese[2]++;
    }


    sort(potenza.begin(), potenza.end());
    reverse(potenza.begin(), potenza.end());

    for(int i = 0; i < n; i++)
    {
        if(potenza[i].second == 0 && prese[0] > 0)
        {
            somma += potenza[i].first;
            prese[0]--;
        }
        else if(potenza[i].second == 1 && prese[1] > 0)
        {
            somma += potenza[i].first;
            prese[1]--;
        }
        else if(prese[2] > 0)
        {
            somma += potenza[i].first;
            prese[2]--;
        }
    }

    out << somma;

    in.close();
    out.close();
}
