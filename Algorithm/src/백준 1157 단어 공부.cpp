#include <iostream>
#include <string>
#include <array>
#include <algorithm>

int main() {
    constexpr int LENGTH = 'Z' - 'A' + 1;

    std::string str;
    std::cin >> str;
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);

    std::array<int, LENGTH> count {};
    for (auto& element : count)
        element = 0;
    
    for (auto&& ch : str)
        count[ch - 'A']++;

    int frequent_char {0};
    bool is_overlap = false;
    for (int i = 1; i < count.size(); ++i)
        if (count[frequent_char] < count[i]) {
            frequent_char = i;
            is_overlap = false;
        } else if (count[frequent_char] == count[i])
            is_overlap = true;

    if (!is_overlap)
        std::cout << static_cast<char>('A' + frequent_char) << std::endl;
    else
        std::cout << '?' << std::endl;

    return 0;
}