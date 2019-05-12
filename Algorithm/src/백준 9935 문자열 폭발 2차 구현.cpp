#include <iostream>
#include <string>
#include <stack>
#include <vector>

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
    std::stack<char> result{}, input, indexed;

    int lengthExplosion = explosion.length();
    int lengthString = str.length();

    for (int i = lengthString - 1; i >= 0; --i)
        input.push(str[i]);

    char currnet;
    int j = 0;
    while (!input.empty()) {
        currnet = input.top();
        input.pop();
        result.push(currnet);

        if (currnet == explosion[j]) {
            indexed.push(j++);
            if (j == lengthExplosion) {
                for (int j = 0; j < lengthExplosion; ++j) {
                    result.pop();
                    indexed.pop();
                }

                if (!indexed.empty())
                    j = indexed.top() + 1;
                else
                    j = 0;
            }
        } else {
            if (currnet == explosion[0])
                j = 0;
            else
                j = -1;
            indexed.push(j++);
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