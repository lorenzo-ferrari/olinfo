#include <stdio.h>
#include <assert.h>
#include <cmath>

int A[4], B[4];
long long result;

int main() {

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

    assert(4 == scanf("%d.%d.%d.%d", &A[0], &A[1], &A[2], &A[3]));
    assert(4 == scanf("%d.%d.%d.%d", &B[0], &B[1], &B[2], &B[3]));

    result = 1 + (B[3]-A[3]) + (B[2]-A[2])*256 + (B[1]-A[1])*pow(256, 2) + (B[0]-A[0])*pow(256, 3);



    printf("%lld\n", result);
}