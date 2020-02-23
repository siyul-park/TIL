#include <iostream>

constexpr int INPUT_MAX = 40;

struct Cache
{
    unsigned int zero;
    unsigned int one;

    Cache& operator+=(const Cache& lef) noexcept {
        zero += lef.zero;
        one += lef.one;

        return *this;
    }
    inline bool isEmpty() noexcept {
        return zero == 0 && one == 0;
    }
    
    inline void print() {
        std::cout << this->zero << " " << this->one << std::endl;
    }
};

class Fibonacci {
public:
    Fibonacci() : caches { 0 } {}

    Cache& operator()(int n) {
        if (!caches[n].isEmpty())
            return caches[n];

        if (n == 0)
            caches[n].zero = 1LL;
        else if (n == 1)
            caches[n].one = 1LL;
        else {
            caches[n] = this->operator()(n-1);
            caches[n] += this->operator()(n-2);
        }

        return caches[n];
    }
private:
    Cache caches[INPUT_MAX+1];
};

int main() {
    int T;
    std::cin >> T;

    Fibonacci fibonacci {};

    int tmp_input;
    for (std::size_t i = 0; i < T; i++) {
        std::cin >> tmp_input;
        fibonacci(tmp_input).print();
    }
    return 0;
}