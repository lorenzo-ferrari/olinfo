#include <fstream>
#include <cmath>
using namespace std;

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");
   
    out.precision(6);
    out.setf(ios::fixed);
   
    int N;
    double xa, ya, xb, yb, xc, yc, r;
   
    in >> N;
   
    for(int i=0; i<N; i++){
        in >> xa >> ya >> xb >> yb >> xc >> yc >> r;
        double ab = sqrt(pow(xa-xb, 2) + pow(ya-yb, 2));  // distanza tra a e b
        double arbr = 0;  // distanza tra a e il cerchio + distanza tra b e il cerchio
        if (sqrt(pow(xa-xc, 2)+pow(ya-yc, 2)) > r) {
            arbr += sqrt(pow(xa-xc, 2) + pow(ya-yc, 2)) - r;
        }
        if (sqrt(pow(xb-xc, 2)+pow(yb-yc, 2)) > r) {
            arbr += sqrt(pow(xb-xc, 2) + pow(yb-yc, 2)) - r;
        }
        // out << fmin(ab, arbr) << endl;  // questo è sbagliato perché in alcuni casi approssima per eccesso il risultato invece il testo chiede l'output troncato (es: input: 0 0 3 3 2 2 0 -> 4,242640[6])
        out << floor(fmin(ab, arbr) * 1000000) / 1000000.0 << endl; // floor(double) ritorna la parte intera (come double) del numero senza la parte decimale
    }

    in.close();
    out.close();

    return 0;
}