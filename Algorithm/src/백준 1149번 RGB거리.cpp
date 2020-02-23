#include <iostream>
#include <array>

constexpr int INPUT_MAX = 1000;

struct Cost
{
    unsigned int r;
    unsigned int g;
    unsigned int b;

    Cost& operator+=(const Cost& lef) {
        r += lef.r;
        g += lef.g;
        b += lef.b;

        return *this;
    }
    inline bool isEmpty() {
        return r == 0 && g == 0 && b == 0;
    }
    
    inline void print() {
        auto min = std::min(r, std::min(g, b));
        std::cout << min << std::endl;
    }
};

class FillHouse {
public:
    FillHouse(const std::array<Cost, INPUT_MAX+1>& cost_data) : cost_data{ cost_data }, caches { 0 } {}

    Cost& operator()(int n) {
        if (!caches[n].isEmpty())
            return caches[n];
        if (n == 0)
            caches[n] = cost_data[n];
        else {
            Cost& pre_cost = this->operator()(n-1);

            caches[n].r = std::min(pre_cost.b, pre_cost.g) + cost_data[n].r;
            caches[n].g = std::min(pre_cost.b, pre_cost.r) + cost_data[n].g;
            caches[n].b = std::min(pre_cost.r, pre_cost.g) + cost_data[n].b;
        }
        return caches[n];
    }
private:
    std::array<Cost, INPUT_MAX+1> caches;
    const std::array<Cost, INPUT_MAX+1>& cost_data;
};

int main() {
    int T;
    std::cin >> T;

    std::array<Cost, INPUT_MAX+1> cost_data {};
    for (size_t i = 0; i < T; i++)
        std::cin >> cost_data[i].r >> cost_data[i].g >> cost_data[i].b;

    FillHouse fillHouse(cost_data);

    fillHouse(T).print();

    return 0;
}