void Vernicia(int indice, int colore);

void Diversifica(int N, int colore[])
{
    int counter = 0;
    int utilizzabili[100001] = {0};
    int test [100001] = {0};
    for(int i = 0; i < N; i++)
    {
        test[colore[i]] = 1;
    }
    for(int i = 1; i <= N; i++)
    {
        if(test[i] == 0)
        {
            utilizzabili[counter] = i;
            counter++;
        }
    }
    counter = 0;
    for(int i = 0; i < N; i++)
    {
        test[colore[i]]++;
        if(test[colore[i]] > 2)
        {
             Vernicia(i, utilizzabili[counter]);
             counter++;
        }
    }
}