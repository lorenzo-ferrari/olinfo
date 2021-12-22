#include <bits/stdc++.h>
#define min(a, b) ((a < b) ? a : b)
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int a[200000];
    for(int i = 0, x; i < n; i++){
        scanf("%d", &x);
        a[i] = a[i + n] = x-10;
    }
    int m = 0, mh = 0, ans = 0;
    for(int i = 0; i < (n<<1); i++){
        mh = min(0, mh + a[i]);
        if(mh < m){
            m = mh;
            ans = i + 1;
        }
    }
    printf("%d\n", ans % n + 1);
}