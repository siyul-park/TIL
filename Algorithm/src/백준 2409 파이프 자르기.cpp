#include <iostream>
#include <vector>
#include <algorithm>

int findMaxPipe(const std::vector<int>& remainingPipe, const std::vector<int>& newPipe) {
    return 0;
}

int main() {
    int M;
    std::cin >> M;

    std::vector<int> remainingPipe(M, 0);
    for (int i = 0; i < M; ++i)
        std::cin >> remainingPipe[i];

    std::sort(remainingPipe.begin(), remainingPipe.end());

    auto sumOfRemain = std::accumulate(remainingPipe.begin(), remainingPipe.end(), 0);

    int N;
    std::cin >> N;
    std::vector<int> newPipe(N, 0);
    for (int i = 0; i < N; ++i)
        std::cin >> newPipe[i];
    std::sort(newPipe.begin(), newPipe.end());

    int i{0};
    for (int maxSum = 0; i < N && maxSum + newPipe[i] < sumOfRemain; ++i)
        maxSum += newPipe[i];
    newPipe.erase(i, newPipe.size());
}