#include <iostream>
#include <string>
#include <vector>

std::vector<int> computeFail(std::string &pattern) {
    auto lengthPattern = pattern.length();
    std::vector<int> fail(lengthPattern, -1);

    auto j = fail[0];
    for (auto i = 1; i < lengthPattern; ++i) {
        while (j >= 0 && pattern[i] != pattern[j + 1])
            j = fail[j];
        if (pattern[i] == pattern[j + 1])
            fail[i] = ++j;
    }

    return fail;
}

std::vector<int> kmp(std::string &text, std::string &pattern) {
    std::vector<int> answer{};

    auto fail = computeFail(pattern);
    auto lengthText = text.length();
    auto lengthPattern = pattern.length();

    auto j = fail[0] + 1;
    for (auto i = 0; i < lengthText; ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = fail[j - 1] + 1;
        if (text[i] == pattern[j]) {
            if (j == lengthPattern - 1) {
                answer.push_back(i - lengthPattern + 1);
                j = fail[j] + 1;
            } else {
                ++j;
            }
        }
    }

    return answer;
}

int main() {
    std::string text{};
    std::string pattern{};

    std::getline(std::cin, text);
    std::getline(std::cin, pattern);

    auto answer = kmp(text, pattern);

    std::cout << answer.size() << '\n';
    for (auto pos : answer)
        std::cout << pos + 1 << ' ';

    return 0;
}