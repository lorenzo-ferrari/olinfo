#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
#define in cin
#define out cout
#endif

int prefix[100100];

int latest[100100];

pii sorted[100100];

int a[100000];
int b[100000];

int main(){
	int n; in >> n;
	for(int i=0; i<n; ++i) in >> a[i];
	for(int i=0; i<n; ++i) in >> b[i];
	prefix[0]=b[0]-a[0];
	sorted[0]={0, 0};
	for(int i=1; i<n; ++i){
		prefix[i]=prefix[i-1]+b[i]-a[i];
		sorted[i]={prefix[i-1], i};
	}
	sort(sorted, sorted+n);
	int maxval=-2147483648;
	for(int i=n-1; i>=0; --i){
		if(prefix[i] > maxval){
			pii p = {prefix[i], 999999};
			int idx = upper_bound(sorted, sorted+n, p) - sorted - 1;
			while(idx >= 0 && sorted[idx].first > maxval) latest[sorted[idx].second] = i, --idx;
			maxval = prefix[i];
		}
	}
	int ans=1;
	for(int i=0; i<n; ++i) ans = max(ans, latest[i]-i+1);
	out << ans << endl;
}
