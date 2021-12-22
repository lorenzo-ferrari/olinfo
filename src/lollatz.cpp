#include <stdio.h>
#include <assert.h>
#define MAX 10000000

bool control[MAX] { };

int afaikdiyrotfl(int N)
{
    if(N % 10 == 0)
        return N;
    if(control[N] == 0)
    {
        control[N] == 1;
        return afaikdiyrotfl(N*(N%10 - 1) / 2);
    }

    return -1;
}

int main() {
    FILE *fr, *fw;
    int N, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));

    fprintf(fw, "%d\n", afaikdiyrotfl(N));
    fclose(fr);
    fclose(fw);
    return 0;
}