#include <iostream>

long long getMinNumOfOperations(long long dist);

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        long long x, y;
        std::cin >> x >> y;

        std::cout << getMinNumOfOperations(y - x) << std::endl;
    }

    return 0;
}

long long getMinNumOfOperations(long long dist) {
    long long warp_count = 0;
    for (long long i = 1; i <= dist; ++i) {
        if (dist <= i*i) {
            if ((i*i - dist) < i)
                warp_count = 2*i - 1;
            else if ((i*i - dist) >= i)
                warp_count = 2*i - 2;
            break;
        }   
    }

    return warp_count;
}
