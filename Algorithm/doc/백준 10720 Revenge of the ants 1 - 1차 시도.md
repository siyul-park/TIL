# Revenge of the ants 1

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 5 초      | 256 MB      | 153  | 20   | 15        | 24.590%   |

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

[2번 문제](https://www.acmicpc.net/problem/10721)의 입력은 1≤L≤10^12, 1≤N,M,N+M≤10^6을 만족하며 해결하면 80점을 얻을 수 있다.

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

<https://www.acmicpc.net/problem/10720>



## 풀이 

### 1차 시도

 원 형태의 길이가 L인 두개의 배열을 만들고 cw로 도는 개미와 ccw로 도는 개미 각각을 다른 배열에 넣는다. 그리고 각각의 배열의 시작 인덱스 주소를 저장한다. cw가 한번 시계 방향으로 이동하기 위해서는 시작 인덱스 주소에 -1을 하면 되고 ccw가 반 시계  방향으로 이동 할려면 시작 인덱스 주소에 1을 더하면 된다. 이렇게 두 원반은 한번씩 회전 시킨 후 배열에  ... , cw 개미, ccw 개미, ... 이렇게 위치 하고 있다면 저 cw 개미와 ccw 개미는 1초 중 충돌 한거다. 따라서 저 cw 개미와 ccw 개미의 이름(구별이 가능한)을 바꿔주면 된다. 이렇게 하면 1초후에 개미들이 어떻게 변했는지를 알 수가 있다. 그후 새롬게 구해진 개미들의 위치와 원래의 개미의 위치를 비교하면 된다.

#### 입력코드

```c++
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
```

#### 출력 코드

```c++
std::cout << findTime(cwAnts, ccwAnts, origin);
```



#### 원래 위치로 가기까지 시간 구하기

```c++
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
```

#### 원래 위치인지 확인

```c++
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
```



#### 전체 코드

```c++
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
```



## 오답 노트

### 1차 시도

| 채점 번호 | 아이디                                                | 문제 번호                                      | 결과      | 메모리 | 시간 | 언어                                                         | 코드 길이 | 제출한 시간                                                  |
| :-------- | :---------------------------------------------------- | :--------------------------------------------- | :-------- | :----- | :--- | :----------------------------------------------------------- | :-------- | :----------------------------------------------------------- |
| 13084414  | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [10720](https://www.acmicpc.net/problem/10720) | 시간 초과 |        |      | [C++11](https://www.acmicpc.net/source/13084414) / [수정](https://www.acmicpc.net/submit/10720/13084414) | 2132      | [11시간 전](https://www.acmicpc.net/status?from_mine=1&problem_id=10720&user_id=kdpark0723#) |

- 시간 초과이다. 단순 시뮬레이션으로 구현 하는 것이 아닌것 같다.