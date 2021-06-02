 #include <fstream>
 #include <cmath>
 using namespace std;

 int n, maxx = 0;
 bool v[101] { };
 int w[21];

 int main()
 {
     ifstream in ("input.txt");
     ofstream out ("output.txt");
     in >> n;

     for(int i = 0; i < n; i++)
     {
         int temp;
         in >> temp;
         w[i] = temp;
         v[temp] = 1;
     }


     for(int i = 1; i <= 100; i++)
     {
         for(int j = 0; j < n; j++)
              if(i - w[j] >= 0)
                  if(v[i - w[j]] == 1)
                      v[i] = 1;
        if(v[i] == 0)
             maxx = i;
     }
    out << maxx;
    in.close();
    out.close();

    return 0;
}

