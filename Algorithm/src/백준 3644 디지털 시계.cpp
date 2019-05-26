#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct SevenSegments {
    bool operator==(const SevenSegments &rhs) {
        for (int i = 0; i < 7; ++i) {
            if (this->segements[i] != rhs.segements[i])
                return false;
        }
        return true;
    }

    void converFromOneDigit(int oneDigit) {
        switch (oneDigit) {
        case 0:
            segements[0] = true;
            segements[1] = true;
            segements[2] = true;
            segements[4] = true;
            segements[5] = true;
            segements[6] = true;
            break;
        case 1:
            segements[2] = true;
            segements[5] = true;
            break;
        case 2:
            segements[0] = true;
            segements[2] = true;
            segements[3] = true;
            segements[4] = true;
            segements[6] = true;
            break;
        case 3:
            segements[0] = true;
            segements[2] = true;
            segements[3] = true;
            segements[5] = true;
            segements[6] = true;
            break;
        case 4:
            segements[1] = true;
            segements[3] = true;
            segements[2] = true;
            segements[5] = true;
            break;
        case 5:
            segements[0] = true;
            segements[1] = true;
            segements[3] = true;
            segements[5] = true;
            segements[6] = true;
            break;  
        case 6:
            segements[0] = true;
            segements[1] = true;
            segements[3] = true;
            segements[4] = true;
            segements[5] = true;
            segements[6] = true;
            break;
        case 7:
            segements[0] = true;
            segements[2] = true;
            segements[5] = true;
            segements[6] = true;
            break;
        case 8:
            segements[0] = true;
            segements[1] = true;
            segements[2] = true;
            segements[3] = true;
            segements[4] = true;
            segements[5] = true;
            segements[6] = true;
            break;
        case 9:
            segements[0] = true;
            segements[1] = true;
            segements[2] = true;
            segements[3] = true;
            segements[5] = true;
            segements[6] = true;
            break;  
        default:
            break;
        }
    }

    int converToOneDigit() {
        static SevenSegments num[10]{};
        for (int i = 0; i < 10; ++i)
            num[i].converFromOneDigit(i);

        for (int i = 0; i < 10; ++i)
            if (num[i] == *this)
                return i;
        
        return -1;
    }

    void calMayBeBroken(const SevenSegments &segments) {
        for (int i = 0; i < 7; ++i)
            if (segments.segements[i])
                this->segements[i] = true;
    }

    vector<int> getAllCombination(const SevenSegments &first) {
        static SevenSegments num[10]{};
        for (int i = 0; i < 10; ++i)
            num[i].converFromOneDigit(i);

        vector<int> combination{};
        for (int i = 0; i < 10; ++i) {
            int j;
            for (j = 0; j < 7; ++j) {
                if ((num[i].segements[j] && first.segements[j] | !this->segements[j]) || (!num[i].segements[j] && !first.segements[j]))
                    continue;
                else
                    break;
            }
            if (j == 7)
                combination.push_back(i);
        }

        return combination;
    }


    bool segements[7]{};
};

struct Time {
    SevenSegments hour[2], minute[2];
};

vector<int> getCombination(const vector<int> &ten, const vector<int> &one, int max, int min) {
    int tenSize = ten.size();
    int oneSize = one.size();

    vector<int> combination{};

    for (int i = 0; i < tenSize; i++)
        if (ten[i] <= max / 10 && ten[i] >= min / 10)
            for (int j = 0; j < oneSize; j++)
                if (!(ten[i] == max / 10 && one[j] > max % 10) && !(ten[i] == min / 10 && one[j] < min % 10))
                    combination.push_back(ten[i] * 10 + one[j]);

    return combination;
}

int main() {

    int N;
    while (scanf("%d", &N) != EOF) {
        vector<Time> times{};
        Time broken{};
        for (int i = 0; i < N; ++i) {
            int hour, minute;
            scanf("%d:%d", &hour, &minute);

            Time tmp{};
            tmp.hour[0].converFromOneDigit(hour/10);
            tmp.hour[1].converFromOneDigit(hour%10);

            tmp.minute[0].converFromOneDigit(minute/10);
            tmp.minute[1].converFromOneDigit(minute%10);

            broken.hour[0].calMayBeBroken(tmp.hour[0]);
            broken.hour[1].calMayBeBroken(tmp.hour[1]);

            broken.minute[0].calMayBeBroken(tmp.minute[0]);
            broken.minute[1].calMayBeBroken(tmp.minute[1]);

            times.push_back(tmp);
        }
        auto hour0 = broken.hour[0].getAllCombination(times[0].hour[0]);
        auto hour1 = broken.hour[1].getAllCombination(times[0].hour[1]);

        auto hours = getCombination(hour0, hour1, 24, 0);
        sort(hours.begin(), hours.end());

        auto minute0 = broken.minute[0].getAllCombination(times[0].minute[0]);
        auto minute1 = broken.minute[1].getAllCombination(times[0].minute[1]);

        auto minuts = getCombination(minute0, minute1, 60, 0);
        sort(minuts.begin(), minuts.end());

        int hoursSize = hours.size();
        int minitsSize = minuts.size();

        if (hoursSize == 0 || minitsSize == 0) {
            printf("none\n");
            continue;
        }
        
        for (int i = 0; i < hoursSize; ++i) {
            for (int j = 0; j < minitsSize; ++j) {
                printf("%02d:%02d ", hours[i], minuts[j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}