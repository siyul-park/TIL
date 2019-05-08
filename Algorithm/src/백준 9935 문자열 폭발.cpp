#include <iostream>
#include <string>
#include <stack>
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

std::string convertString(std::stack<char> stack) {
    auto size = stack.size();

    std::string resultString(size, '\0');
    for (int i = size - 1; i >= 0; --i) {
        resultString[i] = stack.top();
        stack.pop();
    }

    return resultString;
}

std::string exploseString(std::string &str, std::string &explosion) {
    std::stack<char> result{}, input{};

    auto fail = computeFail(explosion);
    auto lengthExplosion = explosion.length();

    auto lengthString = str.length();
    for (int i = lengthString - 1; i >= 0; --i)
        input.push(str[i]);

    auto j = fail[0] + 1;
    char currnet;
    while (!input.empty()) {
        currnet = input.top();
        input.pop();
        result.push(currnet);

        while (j > 0 && currnet != explosion[j])
            j = fail[j - 1] + 1;

        if (currnet == explosion[j]) {
            if (j == lengthExplosion - 1) {
                for (int k = 0; k < lengthExplosion; ++k)
                    result.pop();
                for (int k = 0; !result.empty() &&k < lengthExplosion - 1; ++k) {
                    currnet = result.top();
                    result.pop();
                    input.push(currnet);
                }
                j = fail[j] + 1;
            } else {
                ++j;
            }
        }
        
    }
        
    return convertString(result);
}

int main() {
    std::string str{};
    std::cin >> str;

    std::string explosion{};
    std::cin >> explosion;

    std::string result{exploseString(str, explosion)};
    if (result.empty())
        std::cout << "FRULA";
    else
        std::cout << result;

    return 0;
}