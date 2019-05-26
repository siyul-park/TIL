#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double getTruncatedMean(const vector<float> &nums, int k) {
    int size = nums.size();

    int sum{};
    for (int i = k; i < size - k; ++i)
        sum += nums[i] * 10;

    double mean = ((sum * 100) / (size - 2 * k)) / 1000.0 + 0.00000001;
    mean = round(mean * 100) / 100;

    return mean;
}

double getCalibrationAverage(const vector<float> &nums, int k) {
    int size = nums.size();

    int sum{};
    int i;
    for (i = 0; i < k; ++i)
        sum += nums[k] * 10;
    for (; i < size - k; ++i)
        sum += nums[i] * 10;
    for (; i < size; ++i)
        sum += nums[size - k - 1] * 10;

    double mean = ((sum * 100) / size) / 1000.0 + 0.00000001;
    mean = round(mean * 100) / 100;

    return mean;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<float> nums(N);
    for (int i = 0; i < N; ++i)
        cin >> nums[i];
    sort(nums.begin(), nums.end());

    printf("%0.2lf\n", getTruncatedMean(nums, K));
    printf("%0.2lf", getCalibrationAverage(nums, K));

    return 0;
}