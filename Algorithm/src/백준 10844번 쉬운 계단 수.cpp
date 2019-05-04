#include "iostream"

constexpr long max = 100;

long howManyNumberHaveCache[max][10] = {0};

long howManyNumberHave(long n, long number) {
    if (number < 0 || number > 9)
        return 0;

    if (howManyNumberHaveCache[n][number])
        return howManyNumberHaveCache[n][number];

    if (n == 0) {
        if (number == 0) {
            howManyNumberHaveCache[n][number] = 0L;
            return howManyNumberHaveCache[n][number];
        }

        howManyNumberHaveCache[n][number] = 1L;
        return howManyNumberHaveCache[n][number];
    }

    howManyNumberHaveCache[n][number] = (howManyNumberHave(n - 1, number - 1) + howManyNumberHave(n - 1, number + 1)) % 1000000000;
    return howManyNumberHaveCache[n][number];
}

long getNumberOfStairNumber(long n) {
    long sum = 0L;
    for (int i = 0; i < 10; ++i)
        sum += howManyNumberHave(n, i);

    return sum % 1000000000;
}


int main() {
    long N;
    std::cin >> N;

    std::cout << getNumberOfStairNumber(N - 1);
    return 0;
}