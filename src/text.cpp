#include <bits/stdc++.h>

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

long long N, K, spaceLeft;
string temp;

int main()
{
    in >> N >> K;
    
    spaceLeft = K;
    
    for(int i = 0; i < N; i++) {
        
        in >> temp;
        
        if(temp.size() <= spaceLeft) {
            out << temp << " ";
            spaceLeft = spaceLeft-1-temp.size();
        }
        else{
            out << "\n" << temp << " ";
            spaceLeft = K-1-temp.size();
        }
        
        if(spaceLeft == -1)
                spaceLeft = 0;
    }
}
