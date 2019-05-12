#include <iostream>
#include <vector>
#include <algorithm>


std::vector<int> inputData(int size, int length) {
    std::vector<int> posSorted(size);

    int pos;
    for (int i = 0; i < size; ++i) {
        std::cin >> pos;
        posSorted[i] = pos;
    }

    std::sort(posSorted.begin(), posSorted.end()); 

    std::vector<int> ants(size);

    int i;
    for (i = 0; i < size - 1; ++i)
        ants[i] = posSorted[i + 1] - posSorted[i];
    ants[i] = posSorted[0] + length - posSorted[i];

    
    return ants;
}

int getFixedIndex(int index, int size) {
    int fixedIndex = index;
    fixedIndex %= size;

    return fixedIndex;
}

int getAntsPatternCorrectTime(const std::vector<int> &ants) {
    int time{0};
    int size = ants.size();

    std::vector<int> fail(size, 0);

    int firstCorrect{size};
    int j = fail[0];
    for (int i = 1; i < size * 2; ++i) {
        while (j > 0 && ants[getFixedIndex(i, size)] != ants[j])
            j = fail[j - 1];
        if (ants[getFixedIndex(i, size)] == ants[j]) {
            if (j == size - 1) {
                firstCorrect = i - size + 1;
                break;
            }
            fail[getFixedIndex(i, size)] = ++j;
        }
    }

    for (int i = 0; i < firstCorrect; ++i)
        time += ants[i];
    return time;
}

int gcd(int m, int n) {
    if (m < n)
        std::swap(m, n);
    if (n == 0)
        return 0;

    int r;
    while (true) {
        r = m % n;

        if (r == 0)
            return n;

        m = n;
        n = r;
    }

    return n;
}

int main() {
    int L, M, N;
    std::cin >> L >> N >> M;

    std::vector<int> cwAnts{inputData(N, L)};
    std::vector<int> ccwAnts{inputData(M, L)};
    std::reverse(ccwAnts.begin(), ccwAnts.end());

    int timeCW = getAntsPatternCorrectTime(cwAnts);
    int timeCCW = getAntsPatternCorrectTime(ccwAnts);

    int minTime = timeCW * timeCCW / gcd(timeCW, timeCCW);

    int resultTime = (N + M) * minTime / gcd(N + M, N + M + (N - M) * minTime / L);

    std::cout << resultTime;

    return 0;
}