#include <iostream>
#include <algorithm>
#include <string>
#include <array>

bool isGroupWord(const std::string& word);

int main() {
    int n;
    std::cin >> n;

    int num_of_group_word {0};
    for (int i = 0; i < n; ++i) {
        std::string word {};
        std::cin >> word;

        if (isGroupWord(word))
            num_of_group_word++;
    }

    std::cout << num_of_group_word << std::endl;

    return 0;
}

bool isGroupWord(const std::string& word) {
    std::array<bool, 'z' - 'a' + 1> is_before {};

    signed char before_ch = -1;
    int j;
    for (j = 0; j < word.length(); ++j) {
        if (word[j] != before_ch)
            if (is_before[word[j] - 'a'])
                break;
            else
                is_before[word[j] - 'a'] = true;
        before_ch = word[j];
    }

    if (j == word.length())
        return true;
    return false;
}