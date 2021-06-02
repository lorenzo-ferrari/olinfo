#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

pii vals[10101]; //first il valore, second la posizione
int ans[10101];

int main(){
	int n; cin >> n;
	int idx=0;
	for(int i=0; i<n; ++i){
		int val; cin >> val;
		vals[i] = {val, i};
	}
	sort(vals, vals+n);
	int sum2=0, sum3=0, res=0;
	for(int i=1; i<=vals[n-1].first; ++i){
		++sum2, ++sum3;
		int dummy2=i, dummy3=i;
		while(dummy2 % 2 == 0 && dummy2){
			sum2 -= 1;
			dummy2 /= 2;
		}
		while(dummy3 % 3 == 0 && dummy3){
			sum3 -= 2;
			dummy3 /= 3;
		}
		if(sum2 == sum3) ++res;
		while(i == vals[idx].first && idx<n){
			ans[vals[idx].second] = res;
			++idx;
		}
	}
	for(int i=0; i<n; ++i){
		cout << ans[i] << " ";
	}
	cout << endl;
}
