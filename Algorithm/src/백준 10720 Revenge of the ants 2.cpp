#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

std::vector<long long> inputData(int size, long long length) {
    std::vector<long long> posSorted(size);

    long long pos;
    for (int i = 0; i < size; ++i) {
        std::cin >> pos;
        posSorted[i] = pos;
    }

    std::sort(posSorted.begin(), posSorted.end()); 

    std::vector<long long> ants(size);

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

long long getAntsPatternCorrectTime(const std::vector<long long> &ants) {
    long long time{0ll};
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

long long gcd(long long m, long long n) {
    if (m < n)
        std::swap(m, n);
    if (n == 0ll)
        return 0ll;

    long long r;
    while (true) {
        r = m % n;

        if (r == 0ll)
            return n;

        m = n;
        n = r;
    }

    return n;
}

int main() {
    long long L;
    int M, N;
    std::cin >> L >> N >> M;

    std::vector<long long> cwAnts{inputData(N, L)};
    std::vector<long long> ccwAnts{inputData(M, L)};
    std::reverse(ccwAnts.begin(), ccwAnts.end());

    long long timeCW = getAntsPatternCorrectTime(cwAnts);
    long long timeCCW = getAntsPatternCorrectTime(ccwAnts);

    long long minTime = timeCW / gcd(timeCW, timeCCW) * timeCCW;

    long long resultTime =  (N + M) * minTime / gcd(N + M, N + M + (N - M) * minTime / L);

    std::cout << resultTime;

    return 0;
}