#include <iostream>

long getN(int p, int a, int m) {
    for (long n = 1; n < 101000l; ++n) {
        if ((((n % p) * (n % p)) % p + (n % p) * (m % p) % p) % p == a)
            return n;
    }

    return 0;
}

int main() {
    int d;
    std::cin >> d;

    for (int i = 0; i < d; ++i) {
        int p, a, m;
        std::cin >> p >> a >> m;

        long n{getN(p, a, m)};

        if (n)
            std::cout << "TAK " << n << "\n";
        else
            std::cout << "NIE\n";
    }
}