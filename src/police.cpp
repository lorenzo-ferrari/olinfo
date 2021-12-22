#include <assert.h>
#include <stdio.h>

#define MAXN 100000

int N, K, i;
int V[MAXN + 1];
bool control [MAXN + 1] { };

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

  assert(2 == scanf("%d %d", &N, &K));
  for (i = 1; i <= N; i++) assert(1 == scanf("%d", &V[i]));
  int pos = 1, counter = 0;

  while(!control[pos] && pos != K) {
    control[pos] = 1;
    pos = V[pos];
    counter++;
  }

  if(pos == K)
    printf("%d\n", counter);
  else
    printf("%d\n", -1);

  return 0;
}
