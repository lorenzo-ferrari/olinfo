#include <iostream>

int main() {
	int a, b, c, d;
	std::cin >> a >> b >> c >> d;

	if (a < b) std::swap(a, b);
	if (c < d) std::swap(c, d);

	int ans = 1e9;
	if (a >= c && b >= d) ans = 0;
	else if (a >= c) ans = ((d - b + 1) / 2) * c;
	else if (b >= d) ans = ((c - a + 1) / 2) * d;
	else ans = c * d - a * b;

	std::cout << ans << "\n";
}
