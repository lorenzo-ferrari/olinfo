#include <iostream>
using namespace std;

const int N = 100000;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin >> n;

  int v[N];
  for (int i = 0; i < n; ++i)
    cin >> v[i];

  int maxPari1 = -1;
  int maxPari2 = -1;
  int maxDispari1 = -1;
  int maxDispari2 = -1;

  for (int i = 0; i < n; ++i)
  {
    if (v[i] % 2 == 0) // pari
    {
      if (v[i] >= maxPari1)
      {
        maxPari2 = maxPari1;
        maxPari1 = v[i];
      }
      else if (v[i] > maxPari2)
      {
        maxPari2 = v[i];
      }
    }
    else // dispari
    {
      if (v[i] >= maxDispari1)
      {
        maxDispari2 = maxDispari1;
        maxDispari1 = v[i];
      }
      else if (v[i] > maxDispari2)
      {
        maxDispari2 = v[i];
      }
    }
  }

  if (maxPari2 != -1 || maxDispari2 != -1)
    cout << max(maxPari1 + maxPari2, maxDispari1 + maxDispari2) << endl;
  else
   cout << -1 << endl;
}