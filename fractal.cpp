#include <bits/stdc++.h>
#define MOD 32749
using namespace std;
typedef array<array<int, 2>, 2> matrice;

matrice base;

matrice prodotto(matrice a, matrice b)
{
    matrice res;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            res[i][j] = ((a[i][0]*b[0][j])%MOD + (a[i][1]*b[1][j])%MOD)%MOD;

    return res;
}

matrice fast_exp(matrice m, int exp)
{
    if(exp == 0) return base;

    matrice res = fast_exp(m, exp>>1);
    res = prodotto(res, res);

    if(exp&1) res = prodotto(res, m);

    return res;
}

int main()
{
    base[0][0] = 1; base[1][1] = 1;

    int n;
    scanf("%d", &n);

    matrice mat;
    mat[0][0] = 6;
    mat[0][1] = -3;
    mat[1][0] = 1;
    mat[1][1] = 0;

    mat = fast_exp(mat, n);

    //printf("%d %d\n%d %d\n", mat[0][0], mat[0][1], mat[1][0], mat[1][1]);

    printf("%d %d\n",(mat[0][0] + mat[0][1]+MOD)%MOD, (MOD-mat[0][1])%MOD);
}