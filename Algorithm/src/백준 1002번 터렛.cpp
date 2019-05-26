#include <iostream>

struct Circle {
    int x, y, r;

    int getDistance(const Circle& circle) {
        return (x - circle.x) * (x - circle.x)
            + (y - circle.y) * (y - circle.y);
    }

    bool operator==(const Circle& lef) noexcept {
        return (x == lef.x) && (y == lef.y) && (r == lef.r);
    }
};


int main() {
    int T;
    std::cin >> T;

    for (int i = 0 ; i < T; ++i) {
        Circle a, b;
        std::cin >> a.x >> a.y >> a.r
            >> b.x >> b.y >> b.r;

        int distance = a.getDistance(b);
        int sum_of_radius = (a.r + b.r) * (a.r + b.r);
        int diff_of_radius = (a.r - b.r) * (a.r - b.r);

        if (a == b)
            std::cout << -1 << std::endl;
        else if (distance > sum_of_radius|| distance < diff_of_radius || distance == 0)
            std::cout << 0 << std::endl;
        else if (distance == sum_of_radius || distance == diff_of_radius)
            std::cout << 1 << std::endl;
        else if (diff_of_radius < distance && distance < sum_of_radius)
            std::cout << 2 << std::endl;
    }

    return 0;
}