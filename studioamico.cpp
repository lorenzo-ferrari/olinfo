bool associabili(int N, int voti2[], int voti5[]){
    int delta[12]{};
    for(int i = 0; i < N; ++i) delta[voti2[i]+1]--;
    for(int i = 0; i < N; ++i) delta[voti5[i]]++;

    for(int i = 11, suf = 0; i >= 1; --i)
        if((suf+=delta[i]) < 0) return false;

    return true;
}