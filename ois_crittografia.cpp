#include <stdio.h>
#include <assert.h>

int codifica(int N) {
    int base = N, rev = 0;
    while(base>0)
    {
        rev = 10*rev + base%10;
        base /= 10;
    }

    return N+rev;
}


int main() {
    FILE *fr, *fw;
    int N;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));

    fprintf(fw, "%d\n", codifica(N));
    fclose(fr);
    fclose(fw);
    return 0;
}

