#include <iostream>
#include <array>

std::array<int, 4> getOutput(int numOfV, int numOfH) {
    numOfV %= 2;
    numOfH %= 2;

    std::array<int, 4> output = {
        1, 2,
        3, 4
    };

    if (numOfV == 1) {
        for (int i = 0; i < 2; ++i) {
            int tmp = output[i * 2];
            output[i * 2] = output[i * 2 + 1];
            output[i * 2 + 1] = tmp;
        }
    }
    if (numOfH == 1) {
        for (int i = 0; i < 2; ++i) {
            int tmp = output[i];
            output[i] = output[i + 2];
            output[i + 2] = tmp;
        }
    }

    return output;
}

int main() {
    int numOfV{0}, numOfH{0};

    while (true) {
        char ch = std::cin.get();

        if (ch == 'V')
            numOfV++;
        else if (ch == 'H')
            numOfH++;
        else
            break;
    }

    auto output{getOutput(numOfV, numOfH)};

    for (int i = 0; i < 2; ++i)
        std::cout << output[i * 2] << " " << output[i * 2 + 1] << "\n";

    return 0;
}