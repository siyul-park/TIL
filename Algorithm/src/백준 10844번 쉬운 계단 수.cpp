#include "iostream"

constexpr int MAX = 100;

long howManyNumberHaveStepNumber(int length, int number) {
    static long cache[MAX][10] = {0};

    if (number < 0 || number > 9)
        return 0;

    int lengthIndex = length - 1;

    if (cache[lengthIndex][number])
        return cache[lengthIndex][number];

    if (lengthIndex == 0) {
        if (number == 0) {
            cache[lengthIndex][number] = 0L;
            return cache[lengthIndex][number];
        }

        cache[lengthIndex][number] = 1L;
        return cache[lengthIndex][number];
    }

    cache[lengthIndex][number] = (howManyNumberHaveStepNumber(length - 1, number - 1) + howManyNumberHaveStepNumber(length - 1, number + 1)) % 1000000000;
    return cache[lengthIndex][number];
}

long getNumberOfStepNumber(int length) {
    long sum = 0L;
    for (int i = 0; i < 10; ++i)
        sum += howManyNumberHaveStepNumber(length, i);

    return sum % 1000000000;
}

int main() {
    int N;
    std::cin >> N;

    std::cout << getNumberOfStepNumber(N);
    return 0;
}