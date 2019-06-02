#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int number;
    while (true) {
        std::cin >> number;
        if (number == 0)
            break;

        if (number % n == 0)
            std::cout << number << " is a multiple of " << n << ".\n";
        else
            std::cout << number << " is NOT a multiple of " << n << ".\n";
    }

    return 0;
}