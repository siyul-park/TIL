#include <iostream>
#include <limits>
#include <vector>

constexpr int INPUT_MAX = 1000000;

struct Cost
{
    Cost() {
        count = max;
    }

    bool isEmpty() {
        return count == max;
    }
    void print() {
        std::cout << count << std::endl;
    }

    static const unsigned int max = std::numeric_limits<unsigned int>::max();

    unsigned int count;
};

class MakeOne {
public:
    MakeOne(std::size_t size) : caches (size) {}

    Cost& operator()(int n) {
        if (!caches[n].isEmpty())
            return caches[n];

        if (n == 1) {
            caches.at(n).count = 0;
        } else {
            this->operator()(n-1);
            if (n%2 == 0)
                this->operator()(n/2);
            if (n%3 == 0)
                this->operator()(n/3);

            caches.at(n).count = std::min(caches.at(n-1).count, std::min(caches.at(n/2).count, caches.at(n/3).count)) + 1;
        }
        return caches.at(n);
    }
private:
    std::vector<Cost> caches;
};

int main() {
    int X;
    std::cin >> X;

    try {
        MakeOne makeOne { INPUT_MAX+1 };

        makeOne(X).print();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}