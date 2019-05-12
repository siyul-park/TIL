#include <iostream>
#include <string>

int howManyCharInString(std::string &str, char ch) {
    int count{0};
    for (auto &i : str)
        if (ch == i)
            count++;

    return count;
}   

int main() {
    int K;
    std::cin >> K;

    for (int i = 0; i < K; ++i) {
        int h;
        std::cin >> h;
        
        std::string str;
        std::cin >> str;

        int cutHeadCount = howManyCharInString(str, 'c');
        int burnHeadCount = howManyCharInString(str, 'b');

        h = h + cutHeadCount - burnHeadCount;
        if (h < 0)
            h = 0;
        
        std::cout << "Data Set " << i + 1 << ":\n"
            << h << "\n";
        if (i != K - 1)
            std::cout << "\n";
    }

    return 0;
}