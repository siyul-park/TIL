#include <iostream>

int howManyNumberInDecimalNumber(long number, int findNumber) {
    int numberCount = 0;

    while (number) {
        if ((number % 10) == findNumber)
            numberCount++;
        number /= 10;
    }
    
    return numberCount;
}

int main() {
    int A, B, C;
    std::cin >> A >> B >> C;

    long sum = static_cast<long>(A) * B * C;

    for (int i = 0; i < 10; ++i) 
        std::cout << howManyNumberInDecimalNumber(sum, i) << "\n";

    return 0;
}