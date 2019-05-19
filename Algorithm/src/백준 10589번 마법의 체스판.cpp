#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    int minFuncUseNum = n / 2 + m / 2;
    std::cout << minFuncUseNum << "\n";

    for (int i = n % 2; i < n; i += 2)
        std::cout << i + 1 << " 1 " << i + 1 << " " << m << "\n";
    for (int i = m % 2; i < m; i += 2)
        std::cout << "1 " << i + 1 << " " << n << " " << i + 1 << "\n";

    return 0;
}