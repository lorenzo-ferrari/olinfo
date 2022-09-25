#include <iostream>
using namespace std;

const int mod = 1000000007;

int main() {
  string word; cin >> word;
  long long count=0;
  long long res=1;
  for(int i = word.size()-1; i >= 0; --i) {
    long long pos = word[i] - 'a' + 1;
    if (i != int(word.size() - 1)) {
      res = res * 26 % mod;
    }
    count = (count + pos * res) % mod;
  }
  cout << count - 1 << "\n";
}