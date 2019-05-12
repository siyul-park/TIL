#include <iostream>
#include <vector>
#include <algorithm>

struct Ant {
    int firstPos;
    bool isFisrtCW;
    bool isCW;
};

struct Ants {
    std::vector<Ant> ants;
    int travelDistance;
};

struct Distance {
    int distance;
    Ant *cw;
    Ant *ccw;
};

struct Distances {
    std::vector<Distance> distances;
    int index;
    int travelDistance;
};


int getRealPos(Ant &ant, int travelDistance, int size) {
    int realPos = ant.firstPos - travelDistance;

    if (realPos < 0)
        realPos = size - realPos;
    realPos %= size;

    return realPos;
}

Ants inputData(int length, bool isCW) {
    std::vector<int> posSorted(length);

    int pos;
    for (int i = 0; i < length; ++i) {
        std::cin >> pos;
        posSorted[i] = pos;
    }

    std::sort(posSorted.begin(), posSorted.end()); 

    Ants ants{std::vector<Ant>(length, Ant{0, isCW, isCW}), 0};
    for (int i = 0; i < length; ++i)
        ants.ants[i].firstPos = posSorted[i];
    
    return ants;
}

Distances getDistance(Ants &cw, Ants &ccw, int length) {
    int cwSize = cw.ants.size();
    int ccwSize = ccw.ants.size();

    Distances distances{std::vector<Distance>(cwSize * ccwSize), 0, 0};
    for (int cwIndex = 0; cwIndex < cwSize; ++cwIndex) {
        for (int ccwIndex = 0; ccwIndex < ccwSize; ++ccwIndex) {
            distances.distances[cwIndex * cwSize + ccwIndex].distance = (ccw.ants[ccwIndex].firstPos + length - cw.ants[cwIndex].firstPos) % length;
        }
    }
    
    
}


int main() {
    int L, M, N;
    std::cin >> L >> N >> M;

    Ants cw = inputData(N, true);
    Ants ccw = inputData(M, false);
        
    return 0;
}