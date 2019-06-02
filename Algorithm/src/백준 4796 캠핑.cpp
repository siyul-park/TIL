#include <iostream>
#include <algorithm>

int main() {
    int caseNum{0};

    while (true) {
        caseNum++;

        int L, P, V;
        std::cin >> L >> P >> V;

        if (L == 0 && P == 0 && V == 0)
            break;
        
        int d = V / P;
        int r = V % P;
        int maxDays = d * L + std::min(L, r);

        std::cout << "Case " << caseNum << ": " << maxDays << "\n";
    }
    
    return 0;
}