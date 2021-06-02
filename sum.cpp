#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> a, b, sum;
vector<int> ans(10, -1);
vector<int> used(10, 0);

void print(){
	for(int i = N-1; i >= 0; --i) cout << ans[a[i]];
	cout << "\n";
	for(int i = N-1; i >= 0; --i) cout << ans[b[i]];
	cout << "\n";
	exit(0);
}

void boh(int n, bool carry){
	if(N > 1 && (ans[a[N-1]] == 0 || ans[b[N-1]] == 0)) return;
	if(n == N){
		if(carry == sum[N]) print();
	}
	else if(ans[a[n]] != -1 && ans[b[n]] != -1 && (ans[a[n]] + ans[b[n]] + carry)%10 == sum[n]){
		boh(n+1, (ans[a[n]] + ans[b[n]] + carry)>=10);
	}
	else if(a[n] == b[n] && ans[a[n]] == -1){
		ans[a[n]] = (sum[n]-carry) >> 1;
		++used[ans[a[n]]];
		if(used[ans[a[n]]] < 2) boh(n+1, 0);
		--used[ans[a[n]]];
		ans[a[n]] += 5;
		++used[ans[a[n]]];
		if(used[ans[a[n]]] < 2) boh(n+1, 1);
		--used[ans[a[n]]];
		ans[a[n]] = -1;
	}
	else if(ans[a[n]] == -1 && ans[b[n]] == -1){
		for(int i = 0; i < 10; ++i){
			int j = sum[n]-i+10-carry;
			if(j >= 10) j -= 10;
			if(i == j) continue;
			if(used[i] || used[j]) continue;
			ans[a[n]] = i, ans[b[n]] = j;
			++used[i];
			++used[j];
			boh(n+1, (i+j+carry)>=10);
			--used[i];
			--used[j];
			ans[a[n]] = -1, ans[b[n]] = -1;
		}
	}
	else if(ans[a[n]] == -1){
		int j = (sum[n]-carry-ans[b[n]]+10);
		if(j >= 10) j -= 10;
		if(used[j]) return;
		ans[a[n]] = j;
		++used[j];
		boh(n+1, (j + ans[b[n]]+carry)>=10);
		--used[j];
		ans[a[n]] = -1;
	}
	else if(ans[b[n]] == -1){
		int j = (sum[n]-carry-ans[a[n]]+10);
		if(j >= 10) j -= 10;
		if(used[j]) return;
		ans[b[n]] = j;
		++used[j];
		boh(n+1, (j + ans[a[n]] + carry)>=10);
		--used[j];
		ans[b[n]] = -1;
	}
}

int main(){
	string s; cin >> s;
	N = s.size();
	for(int i = N-1; i >= 0; --i) a.push_back(s[i]-'A');
	cin >> s;
	for(int i = N-1; i >= 0; --i) b.push_back(s[i]-'A');
	cin >> s;
	for(int i = s.size()-1; i >= 0; --i) sum.push_back(s[i]-'0');
	sum.push_back(0);
	boh(0, 0);
}
