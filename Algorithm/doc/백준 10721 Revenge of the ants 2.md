# Revenge of the ants 2 성공

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 5 초      | 256 MB      | 109  | 17   | 13        | 25.490%   |

## 문제

둘레의 길이가 L인 원형 레일이 있다. 경근이는 레일을 L등분하여 각 지점에 시계방향으로 0에서 L−1까지의 번호를 붙였다. 그리고 번호를 붙인 지점 중 몇 개를 선택하여 시계방향으로 레일 위를 움직이는 개미 N마리와 반시계방향으로 레일 위를 움직이는 개미 M마리를 놓았다. 이때 같은 지점에 두 마리 이상의 개미가 있는 경우는 없다.

레일 위에 올라온 모든 개미는 1초에 1의 거리를 움직인다. 레일의 폭은 최대 한 마리의 개미만이 움직일 수 있을 정도로 매우 좁아서, 서로 반대방향으로 움직이는 개미들이 어느 한 위치에서 부딪치고 난 다음에는 그 즉시 서로 방향을 반대로 바꾸어 움직인다. 개미의 크기는 매우 작아서 점으로 취급하여, 정확히 같은 위치에 존재하게 되어야 부딪친다고 하자.

경근이는 모든 개미를 구별할 수 있어서, 모든 개미가 처음과 같은 위치에서 같은 속도를 가지게 되려면 최소한 몇 초가 필요한지 궁금해졌다. 경근이를 도와 이 시간이 몇 초인지 알려주는 프로그램을 작성하라.

## 입력

첫 번째 줄에 원형 레일의 둘레를 의미하는 L, 시계방향으로 레일 위를 움직이는 개미의 수를 의미하는 N, 반 시계방향으로 레일 위를 움직이는 개미의 수를 의미하는 M이 공백으로 구분되어 주어진다.

두 번째 줄에는 시계방향으로 움직이는 개미들이 있는 지점을 의미하는 N개의 정수가 공백으로 구분되어 주어진다.

세 번째 줄에는 반시계방향으로 움직이는 개미들이 있는 지점을 의미하는 M개의 정수가 공백으로 구분되어 주어진다.

이 문제는 두 개의 부분 문제로 이루어져 있다.

[1번 문제](https://www.acmicpc.net/problem/10720)의 입력은 1≤L≤600, 1≤N,M,N+M≤600을 만족하며 해결하면 20점을 얻을 수 있다.

[2번 문제](https://www.acmicpc.net/problem/10721)의 입력은 1≤L≤1012, 1≤N,M,N+M≤106을 만족하며 해결하면 80점을 얻을 수 있다.

## 출력

첫 번째 줄에 모든 개미들이 처음과 같은 위치, 같은 속도를 가지게 되려면 최소한 몇 초가 필요한지 출력하라.



## 예제 입력 1 복사

```
2 1 1
0
1
```

## 예제 출력 1 복사

```
2
```

## 힌트

0.5초와 1.5초에 부딪친 후 2초가 되면 처음과 같은 상태가 된다.

## 출처

<https://www.acmicpc.net/problem/10721>



## 풀이

1번이랑 동일하다. 하지만 입력 데이터의 크기가 변했으므로 오버플로가 나지 않게 데이터 형의 크기를 조절한다



####  코드

```c++
long long L;
int M, N;
std::cin >> L >> N >> M;

std::vector<long long> cwAnts{inputData(N, L)};
std::vector<long long> ccwAnts{inputData(M, L)};
```

#### 출력 코드

```c++
std::cout << resultTime;
```



#### 개미 패턴을 찾기 위해 개미 정보를 인코딩

```c++
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
```

#### 개미 패턴 찾기

```c++
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
```



#### 전체 코드

```c++
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
```

