#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

constexpr bool isNumber(char ch) {
    return ch >= '0' && ch <='9';
}
constexpr int toNumber(char ch) {
    return ch - '0';
}

bool compare(const string &serial1, const string &serial2) {
    size_t size_of_1{serial1.size()};
    size_t size_of_2{serial2.size()};

    if (size_of_1 != size_of_2)
        return size_of_1 < size_of_2;

    int sum_of_1{0};
    int sum_of_2{0};

    for (size_t i = 0; i < size_of_1; ++i) {
        if (isNumber(serial1[i]))
            sum_of_1 += toNumber(serial1[i]);
        if (isNumber(serial2[i]))
            sum_of_2 += toNumber(serial2[i]);
    }

    if (sum_of_1 != sum_of_2)
        return sum_of_1 < sum_of_2;
    
    for (size_t i = 0; i < size_of_1; ++i) {
        if (serial1[i] != serial2[i]) {
            if (isNumber(serial1[i]) && !isNumber(serial2[i])) 
                return true;
            else if (!isNumber(serial1[i]) && isNumber(serial2[i])) 
                return false;
            else if (isNumber(serial1[i]) && isNumber(serial2[i]))
                return serial1[i] < serial2[i];
            else if (!isNumber(serial1[i]) && !isNumber(serial2[i])) 
                return serial1[i] < serial2[i];
        }
    }

    return true;
}

int main() {
    int size;
    cin >> size;

    vector<string> serials(size);
    for (auto i = 0; i < size; ++i)
        cin >> serials[i];

    sort(serials.begin(), serials.end(), compare);

    for (auto i = 0; i < size; ++i) 
        cout << serials[i] << "\n";

    return 0;
}