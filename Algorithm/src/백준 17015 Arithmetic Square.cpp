#include <iostream>
#include <string>
#include <cstdlib>

void findRow(int (&square)[3][3], bool (&isFind)[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (!isFind[i][0] && isFind[i][1] && isFind[i][2]) {
            isFind[i][0] = true;
            square[i][0] = square[i][1] - (square[i][2] - square[i][1]);
        } else if (isFind[i][0] && !isFind[i][1] && isFind[i][2]) {
            isFind[i][1] = true;
            square[i][1] = (square[i][0] + square[i][2]) / 2;
        } else if (isFind[i][0] && isFind[i][1] && !isFind[i][2]) {
            isFind[i][2] = true;
            square[i][2] = square[i][1] + (square[i][1] - square[i][0]);
        } 
    }
}

void findCol(int (&square)[3][3], bool (&isFind)[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (!isFind[0][i] && isFind[1][i] && isFind[2][i]) {
            isFind[0][i] = true;
            square[0][i] = square[1][i] - (square[2][i] - square[1][i]);
        } else if (isFind[0][i] && !isFind[1][i] && isFind[2][i]) {
            isFind[1][i] = true;
            square[1][i] = (square[0][i] + square[2][i]) / 2;
        } else if (isFind[0][i] && isFind[1][i] && !isFind[2][i]) {
            isFind[2][i] = true;
            square[2][i] = square[1][i] + (square[1][i] - square[0][i]);
        } 
    }
}

bool findAll(bool (&isFind)[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (!isFind[i][j])
                return false;
    return true;
}

void find(int (&square)[3][3], bool (&isFind)[3][3]) {
    do {
        for (int i = 0; i < 9; ++ i) {
            findRow(square, isFind);
            findCol(square, isFind);
        }

        if (!isFind[1][1]) {
            if (isFind[0][1])
                square[1][1] = square[0][1];
            else if (isFind[1][0])
                square[1][1] = square[1][0];
            else if (isFind[1][2])
                square[1][1] = square[1][2];
            else if (isFind[2][1])
                square[1][1] = square[2][1];
            isFind[1][1] = true;
        } else if (!isFind[0][1]) {
            square[0][1] = square[1][1];
            isFind[0][1] = true;
        } else if (!isFind[1][0]) {
            square[1][0] = square[1][1];
            isFind[1][0] = true;
        } else if (!isFind[1][2]) {
            square[1][2] = square[1][1];
            isFind[1][2] = true;
        } else if (!isFind[2][1]) {
            square[2][1] = square[1][1];
            isFind[2][1] = true;
        }
    } while (!findAll(isFind));
}

int main() {
    int square[3][3] = {0};
    bool isFind[3][3] = {false};

    std::string num{};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> num;

            if (num[0] != 'X') {
                isFind[i][j] = true;

                square[i][j] = std::atoi(num.c_str());
            }
        }
    }
    
    find(square, isFind);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isFind[i][j]) {
                std::cout << square[i][j] << " ";
            } else {
                std::cout << "X ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}