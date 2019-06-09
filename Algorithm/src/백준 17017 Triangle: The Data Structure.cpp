#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b, int c, int d, int e, int f) {
    return max(a, max(b, max(c, max(d, max(e, f)))));
}

int getMaxElementInSubTriangle(const vector<vector<int>> &maxElementSubTriangle, int indexRow, int indexCol, int sizeOfCalculatedSub, int sizeOfNewSub) {
    int added = sizeOfNewSub - sizeOfCalculatedSub;

    return max(maxElementSubTriangle[indexRow][indexCol], maxElementSubTriangle[indexRow + added][indexCol], maxElementSubTriangle[indexRow + added][indexCol + added],
        maxElementSubTriangle[indexRow + added / 2][indexCol], maxElementSubTriangle[indexRow + added / 2][indexCol + added / 2], maxElementSubTriangle[indexRow + added][indexCol + added / 2]);
}

void calSubTriangle(const vector<vector<int>> &maxElementSubTriangle, vector<vector<int>> &newMaxElementSubTriangle, int sizeOfTriangle, int sizeOfCalculatedSub, int sizeOfNewSub) {
    for (int i = 0; i < sizeOfTriangle - sizeOfNewSub + 1; ++i)
        for (int j = 0; j < i + 1; ++j)
            newMaxElementSubTriangle[i][j] = getMaxElementInSubTriangle(maxElementSubTriangle, i, j, sizeOfCalculatedSub, sizeOfNewSub);
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<vector<int>> triangle{};
    for (int i = 0; i < N; ++i) {
        triangle.push_back(vector<int>(i + 1, 0));

        for (int j = 0; j < i + 1; ++j)
            cin >> triangle[i][j];
    }

    vector<vector<int>> tmpTriangle{triangle};
    for (int i = 1; i < K; i *= 2) {
        int newSize{min(i * 2, K)};

        calSubTriangle(triangle, tmpTriangle, N, i, newSize);
        swap(triangle, tmpTriangle);
    }

    long long sum{0};
    for (int i = 0; i < N - K + 1; ++i)
        for (int j = 0; j < i + 1; ++j)
            sum += triangle[i][j];

    cout << sum;

    return 0;
}