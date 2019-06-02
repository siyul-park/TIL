# Flipper

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 512 MB      | 112  | 65   | 33        | 58.929%   |

## 문제

You are trying to pass the time while at the optometrist. You notice there is a grid of four numbers:

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/17013/1.svg)

You see lots of mirrors and lenses at the optometrist, and wonder how flipping the grid horizontally or vertically would change the grid.

Specifically, a "horizontal" flip (across the horizontal centre line) would take the original grid of four numbers and result in:

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/17013/2.svg)

A "vertical" flip (across the vertical centre line) would take the original grid of four numbers and result in:

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/17013/3.svg)

Your task is to determine the final orientation of the numbers in the grid after a sequence of horizontal and vertical flips.

## 입력

The input consists of one line, composed of a sequence of at least one and at most 1000000 characters. Each character is either H, representing a horizontal flip, or V, representing a vertical flip.

For 8 of the 15 available marks, there will be at most 1000 characters in the input.

## 출력

Output the final orientation of the four numbers. Specifically, each of the two lines of output will contain two integers, separated by one space.



## 예제 입력 1 복사

```
HV
```

## 예제 출력 1 복사

```
4 3
2 1
```

## 예제 입력 2 복사

```
VVHH
```

## 예제 출력 2 복사

```
1 2
3 4
```



## 출처

<https://www.acmicpc.net/problem/17013>



## 풀이

V와 H의 계산 순서가 바뀌어도 결과는 동일하다. VV나, HH의 결과는 원래 결과와 동일하다.

따라서 V와 H의 개수를 세고 묘듈러 2 연산을 한후 계산을 해주면 된다.



### 입력 코드

```c++
int numOfV{0}, numOfH{0};

while (true) {
    char ch = std::cin.get();

    if (ch == 'V')
        numOfV++;
    else if (ch == 'H')
        numOfH++;
    else
        break;
}
```

### 출력 코드

```c++
for (int i = 0; i < 2; ++i)
    std::cout << output[i * 2] << " " << output[i * 2 + 1] << "\n";
```



### 결과 구하기

```c++
std::array<int, 4> getOutput(int numOfV, int numOfH) {
    numOfV %= 2;
    numOfH %= 2;

    std::array<int, 4> output = {
        1, 2,
        3, 4
    };

    if (numOfV == 1) {
        for (int i = 0; i < 2; ++i) {
            int tmp = output[i * 2];
            output[i * 2] = output[i * 2 + 1];
            output[i * 2 + 1] = tmp;
        }
    }
    if (numOfH == 1) {
        for (int i = 0; i < 2; ++i) {
            int tmp = output[i];
            output[i] = output[i + 2];
            output[i + 2] = tmp;
        }
    }

    return output;
}
```



### 전체 코드

```c++
#include <iostream>
#include <array>

std::array<int, 4> getOutput(int numOfV, int numOfH) {
    numOfV %= 2;
    numOfH %= 2;

    std::array<int, 4> output = {
        1, 2,
        3, 4
    };

    if (numOfV == 1) {
        for (int i = 0; i < 2; ++i) {
            int tmp = output[i * 2];
            output[i * 2] = output[i * 2 + 1];
            output[i * 2 + 1] = tmp;
        }
    }
    if (numOfH == 1) {
        for (int i = 0; i < 2; ++i) {
            int tmp = output[i];
            output[i] = output[i + 2];
            output[i + 2] = tmp;
        }
    }

    return output;
}

int main() {
    int numOfV{0}, numOfH{0};

    while (true) {
        char ch = std::cin.get();

        if (ch == 'V')
            numOfV++;
        else if (ch == 'H')
            numOfH++;
        else
            break;
    }

    auto output{getOutput(numOfV, numOfH)};

    for (int i = 0; i < 2; ++i)
        std::cout << output[i * 2] << " " << output[i * 2 + 1] << "\n";

    return 0;
}
```



### 공간 복잡도

- O(1)

### 시간 복잡도

- O(length(input))