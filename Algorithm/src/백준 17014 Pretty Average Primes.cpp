#include <iostream>
#include <vector>

std::vector<bool> getPrimes(int N) {
    int size = N * 2 + 1;
    std::vector<bool> isPrime(size, true);

    for (int i = 2; i < size; ++i)
        if (isPrime[i])
            for (int j = i * 2; j < size; j += i)
                isPrime[j] = false;

    return isPrime;
}

int main() {
    int T;
    std::cin >> T;

    std::vector<bool> isPrime{getPrimes(1000000)};

    for (int i = 0; i < T; ++i) {
        int N;
        std::cin >> N;

        for (int j = N; j > 2; --j) {
            if (isPrime[j] && isPrime[N * 2 - j]) {
                std::cout << j << " " << N * 2 - j << "\n";
                break;
            }
        }
    }

    return 0;
}