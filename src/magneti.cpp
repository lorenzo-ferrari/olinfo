#include <stdio.h>
#include <assert.h>
#include <math.h>

#define MAXN 100000

int gira(int N, char descrizione[]) {
    int piuMeno = 0, menoPiu = 0;
    for(int i = 1; i < N; i = i + 4)
        if(descrizione[i] == '+')
            piuMeno++;
        else
            menoPiu++;

    return fmin(piuMeno, menoPiu);
}


char descrizione[MAXN + 5]; // Maggiore di MAXN per contenere newline e null

int main() {
    FILE *fr, *fw;
    int N;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d\n", &N));
    assert(fgets(descrizione, MAXN + 5, fr) == descrizione);
    descrizione[N] = 0;

    fprintf(fw, "%d\n", gira(N, descrizione));
    fclose(fr);
    fclose(fw);
    return 0;
}
