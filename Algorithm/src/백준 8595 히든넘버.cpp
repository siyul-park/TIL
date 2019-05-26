#include <iostream>

int main() {
    int n;
    std::cin >> n;

    long long sum{0}, num{0};
    char numChar;
    for (int i = 0; i < n; ++i) {
        std::cin >> numChar;
        if (numChar >= '0' && numChar <= '9') {
            num *= 10;
            num += numChar - '0';
        } else {
            sum += num;
            num = 0;
        }
    }
    sum += num;
    num = 0;

    std::cout << sum;
    
    return 0;
}