#include <iostream>

int getDistence(int n);

int main() {
    int n;
    std::cin >> n;

    int min_distence = getDistence(n);

    std::cout << min_distence;

    return 0;
}

int getDistence(int n) {
    int max_num_in_level {1};
    int level {1};

    while (true) {
        if (n <= max_num_in_level)
            return level;
        max_num_in_level += 6 * (level++);
    }
}
