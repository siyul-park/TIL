#include <iostream>
#include <utility>
#include <array>
#include <algorithm>

using StationData = std::pair<int, int>;
constexpr int DATA_SIZE = 4;
using StationDataArray = std::array<StationData, DATA_SIZE>;

int test();

StationDataArray inputDataFromConsole();
StationDataArray inputDataFromTestCase();

int outputDataFromTestCase();

int getMaxPeopleNum(StationDataArray& station_datas);

int main() {
    auto input_data = std::move(inputDataFromConsole());
    auto max_people_num = getMaxPeopleNum(input_data);

    std::cout << max_people_num;
    // test();
    
    return 0;
}

int test() {
    auto input_data = std::move(inputDataFromTestCase());
    auto max_people_num = getMaxPeopleNum(input_data);

    if (max_people_num == outputDataFromTestCase())
        std::cout << "Pass" << std::endl;
    else
        std::cout << "Fail" << std::endl;
    return 0;
}

StationDataArray inputDataFromConsole() {
    StationDataArray input;

    for (int i = 0; i < input.size(); ++i)
        std::cin >> input[i].first >> input[i].second;
    
    return input;
}

StationDataArray inputDataFromTestCase() {
    StationDataArray input = {
        StationData {0, 32},
        StationData {3, 13},
        StationData {28, 25},
        StationData {39, 0},
    };
    
    return input;
}

int outputDataFromTestCase() {
    return 42;
}

int getMaxPeopleNum(StationDataArray& station_datas) {
    int max_people_num = 0;
    int now_people_num = 0;

    for (int i = 0; i < station_datas.size(); ++i) {
        now_people_num -= station_datas[i].first;
        now_people_num += station_datas[i].second;

        max_people_num = std::max(max_people_num, now_people_num);
    }

    return max_people_num;
}