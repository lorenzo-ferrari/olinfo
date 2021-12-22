#include <iostream>
int main() {
  int n, l, u;
  scanf("%d%d%d", &n, &l, &u);

  int ans = (n + u - 1) / u;
  printf("%d", n / ans >= l ? ans : -1);
}
