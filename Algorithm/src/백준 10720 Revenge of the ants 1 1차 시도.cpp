#include <iostream>
#include <vector>
#include <algorithm>

struct Ant {
    long name;
    bool isCw;
};

struct Ants {
    std::vector<Ant*> ants;
    long startPos;
    long size;

    Ant*& get(long index) {
        long realPos = index - startPos;

        if (realPos < 0)
            realPos = size - realPos;
        realPos %= size;

        return ants[realPos];
    }
};

bool isCorrect(Ants &cwAnts, Ants &ccwAnts, Ants &origin) {
    long size = origin.size;

    for (long i = 0; i < size; ++i) {
        if (origin.ants[i]) {
            if (cwAnts.get(i) && origin.ants[i]->isCw) {
                if (cwAnts.get(i)->name != origin.ants[i]->name)
                    return false;
            } else if (ccwAnts.get(i) && !origin.ants[i]->isCw) {
                if (ccwAnts.get(i)->name != origin.ants[i]->name)
                    return false;
            } else {
                return false;
            }
        }
    }

    return true;
}

int findTime(Ants &cwAnts, Ants &ccwAnts, Ants &origin) {
    long size = origin.size;

    int time = 0;
    do {
        time++;
        cwAnts.startPos--;
        ccwAnts.startPos++;

        for (long i = 0; i < size; ++i) {
            if (cwAnts.get(i) && ccwAnts.get(i - 1)) {
                long tmpName = cwAnts.get(i)->name;

                cwAnts.get(i)->name = ccwAnts.get(i - 1)->name;
                ccwAnts.get(i - 1)->name = tmpName;
            }
        }
    } while (!isCorrect(cwAnts, ccwAnts, origin));

    return time;
}

int main() {
    long L, M, N;
    std::cin >> L >> N >> M;

    long pos;
    Ants cwAnts{std::vector<Ant*>(L, nullptr), 0, L}, ccwAnts{std::vector<Ant*>(L, nullptr), 0, L}, origin{std::vector<Ant*>(L, nullptr), 0, L};
    for (int i = 0; i < N; ++i) {
        std::cin >> pos;
        cwAnts.ants[pos] = new Ant{i, true};
        origin.ants[pos] = new Ant{i, true};
    }
    for (int i = 0; i < M; ++i) {
        std::cin >> pos;
        ccwAnts.ants[pos] = new Ant{i + N, false};
        origin.ants[pos] = new Ant{i + N, false};
    }

    std::cout << findTime(cwAnts, ccwAnts, origin);
        
    return 0;
}