#include <fstream>

using namespace std;

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");
int n, voto, somma = 0, sommaTemp, ristoranteInTesta;
in >> n;
for(int ristorante = 0; ristorante < n; ristorante++){
    sommaTemp = 0;
    for(int i = 0; i < n + 1; i++){
        in >> voto;
 
    sommaTemp += voto;
    }
    if(sommaTemp > somma){
        somma = sommaTemp;
        ristoranteInTesta = ristorante + 1;
    }
    out << ristoranteInTesta << endl;
}

return 0;
}