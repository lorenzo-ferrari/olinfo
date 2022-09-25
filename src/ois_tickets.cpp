#include <assert.h>
#include <stdio.h>
#include <math.h>

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    long long T;
    assert(1 == scanf("%lld", &T));

    long long N = floor((sqrt(1 + 8 * T) - 1) / 2);

    printf("%d\n", N);

    return 0;
}

