# Triangle: The Data Structure

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 4 초      | 512 MB      | 19   | 6    | 4         | 23.529%   |

## 문제

In a parallel universe, the most important data structure in computer science is the triangle. A triangle of size M consists of M rows, with the ith row containing i elements. Furthermore, these rows must be arranged to form the shape of an equilateral triangule. That is, each row is centred around a vertical line of symmetry through the middle of the triangle. For example, the diagram below shows a triangle of size 4:

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/17017/1.svg)

A triangle contains sub-triangles. For example, the triangle above contains ten sub-triangles of size 1, six sub-triangles of size 2 (two of which are the triangle containing (3,1,2) and the triangle containing (4,6,1)), three sub-triangles of size 3 (one of which contains (2,2,1,1,4,2)). Note that every triangle is a sub-triangle of itself.

You are given a triangle of size N and must find the sum of the maximum elements of every sub-triangle of size K.

## 입력

The first line contains two space-separated integers N and K (1 ≤ K ≤ N ≤ 3000).

Following this are N lines describing the triangle. The ith of these lines contains 𝑖 space-separated integers ai,j (0 ≤ ai,j ≤ 109), representing the ith row of the triangle.

For 4 of the 15 available marks, N ≤ 1000.

## 출력

Output the integer sum of the maximum elements of every sub-triangle of size K.



## 예제 입력 1 복사

```
4 2
3
1 2
4 2 1
6 1 4 2
```

## 예제 출력 1 복사

```
23
```



## 출처

<https://www.acmicpc.net/problem/17017>



# 풀이

### 입력 코드

```c++
int N, K;
cin >> N >> K;

vector<vector<int>> triangle{};

for (int i = 0; i < N; ++i) {
    triangle.push_back(vector<int>(i + 1, 0));

    for (int j = 0; j < i + 1; ++j)
        cin >> triangle[i][j];
}
```

### 출력 코드

```c++
long long sum{0};
for (int i = 0; i < N - K + 1; ++i)
    for (int j = 0; j < i + 1; ++j)
        sum += triangle[i][j];

cout << sum;
```



### 부분 삼각형의 최대 요소 구하기

```c++
int getMaxElementInSubTriangle(const vector<vector<int>> &maxElementSubTriangle, int indexRow, int indexCol, int sizeOfCalculatedSub, int sizeOfNewSub) {
    int added = sizeOfNewSub - sizeOfCalculatedSub;

    return max(maxElementSubTriangle[indexRow][indexCol], maxElementSubTriangle[indexRow + added][indexCol], maxElementSubTriangle[indexRow + added][indexCol + added],
        maxElementSubTriangle[indexRow + added / 2][indexCol], maxElementSubTriangle[indexRow + added / 2][indexCol + added / 2], maxElementSubTriangle[indexRow + added][indexCol + added / 2]);
}

void calSubTriangle(const vector<vector<int>> &maxElementSubTriangle, vector<vector<int>> &newMaxElementSubTriangle, int sizeOfTriangle, int sizeOfCalculatedSub, int sizeOfNewSub) {
    for (int i = 0; i < sizeOfTriangle - sizeOfNewSub + 1; ++i)
        for (int j = 0; j < i + 1; ++j)
            newMaxElementSubTriangle[i][j] = getMaxElementInSubTriangle(maxElementSubTriangle, i, j, sizeOfCalculatedSub, sizeOfNewSub);
}
```



### 전체 코드

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b, int c, int d, int e, int f) {
    return max(a, max(b, max(c, max(d, max(e, f)))));
}

int getMaxElementInSubTriangle(const vector<vector<int>> &maxElementSubTriangle, int indexRow, int indexCol, int sizeOfCalculatedSub, int sizeOfNewSub) {
    int added = sizeOfNewSub - sizeOfCalculatedSub;

    return max(maxElementSubTriangle[indexRow][indexCol], maxElementSubTriangle[indexRow + added][indexCol], maxElementSubTriangle[indexRow + added][indexCol + added],
        maxElementSubTriangle[indexRow + added / 2][indexCol], maxElementSubTriangle[indexRow + added / 2][indexCol + added / 2], maxElementSubTriangle[indexRow + added][indexCol + added / 2]);
}

void calSubTriangle(const vector<vector<int>> &maxElementSubTriangle, vector<vector<int>> &newMaxElementSubTriangle, int sizeOfTriangle, int sizeOfCalculatedSub, int sizeOfNewSub) {
    for (int i = 0; i < sizeOfTriangle - sizeOfNewSub + 1; ++i)
        for (int j = 0; j < i + 1; ++j)
            newMaxElementSubTriangle[i][j] = getMaxElementInSubTriangle(maxElementSubTriangle, i, j, sizeOfCalculatedSub, sizeOfNewSub);
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<vector<int>> triangle{};
    for (int i = 0; i < N; ++i) {
        triangle.push_back(vector<int>(i + 1, 0));

        for (int j = 0; j < i + 1; ++j)
            cin >> triangle[i][j];
    }

    vector<vector<int>> tmpTriangle{triangle};
    for (int i = 1; i < K; i *= 2) {
        int newSize{min(i * 2, K)};

        calSubTriangle(triangle, tmpTriangle, N, i, newSize);
        swap(triangle, tmpTriangle);
    }

    long long sum{0};
    for (int i = 0; i < N - K + 1; ++i)
        for (int j = 0; j < i + 1; ++j)
            sum += triangle[i][j];

    cout << sum;

    return 0;
}
```



### 시간 복잡도

- O(N^2 * log(K))



### 공간 복잡도

- O(N^2)