# Fly me to the Alpha Centauri

| 시간 제한 | 메모리 제한 | 제출  | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :---- | :--- | :-------- | :-------- |
| 2 초      | 512 MB      | 22766 | 5756 | 4493      | 27.214%   |

## 문제

우현이는 어린 시절, 지구 외의 다른 행성에서도 인류들이 살아갈 수 있는 미래가 오리라 믿었다. 그리고 그가 지구라는 세상에 발을 내려 놓은 지 23년이 지난 지금, 세계 최연소 ASNA 우주 비행사가 되어 새로운 세계에 발을 내려 놓는 영광의 순간을 기다리고 있다.

그가 탑승하게 될 우주선은 Alpha Centauri라는 새로운 인류의 보금자리를 개척하기 위한 대규모 생활 유지 시스템을 탑재하고 있기 때문에, 그 크기와 질량이 엄청난 이유로 최신기술력을 총 동원하여 개발한 공간이동 장치를 탑재하였다. 하지만 이 공간이동 장치는 이동 거리를 급격하게 늘릴 경우 기계에 심각한 결함이 발생하는 단점이 있어서, 이전 작동시기에 k광년을 이동하였을 때는 k-1 , k 혹은 k+1 광년만을 다시 이동할 수 있다. 예를 들어, 이 장치를 처음 작동시킬 경우 -1 , 0 , 1 광년을 이론상 이동할 수 있으나 사실상 음수 혹은 0 거리만큼의 이동은 의미가 없으므로 1 광년을 이동할 수 있으며, 그 다음에는 0 , 1 , 2 광년을 이동할 수 있는 것이다. ( 여기서 다시 2광년을 이동한다면 다음 시기엔 1, 2, 3 광년을 이동할 수 있다. )



김우현은 공간이동 장치 작동시의 에너지 소모가 크다는 점을 잘 알고 있기 때문에 x지점에서 y지점을 향해 최소한의 작동 횟수로 이동하려 한다. 하지만 y지점에 도착해서도 공간 이동장치의 안전성을 위하여 y지점에 도착하기 바로 직전의 이동거리는 반드시 1광년으로 하려 한다.

김우현을 위해 x지점부터 정확히 y지점으로 이동하는데 필요한 공간 이동 장치 작동 횟수의 최솟값을 구하는 프로그램을 작성하라.

## 입력

입력의 첫 줄에는 테스트케이스의 개수 T가 주어진다. 각각의 테스트 케이스에 대해 현재 위치 x 와 목표 위치 y 가 정수로 주어지며, x는 항상 y보다 작은 값을 갖는다. ( 0 ≤ x < y < 231)

## 출력

각 테스트 케이스에 대해 x지점으로부터 y지점까지 정확히 도달하는데 필요한 최소한의 공간이동 장치 작동 회수를 출력한다.



## 예제 입력 1 복사

```
3
0 3
1 5
45 50
```

## 예제 출력 1 복사

```
3
3
4
```



## 출처

<https://www.acmicpc.net/problem/1011>



## 풀이

최고속도 n까지 최대한 빠르게 가속한후 최대한 빠르게 감속할때 갈수 있는 길이는 n^2이고 이때 워프 횟수는 2*n - 1이다.
(n-1)^2 < dist <= n^2 일때 워프 횟수는 2*(n-1) - 1 보다 크고 2*n - 1 보다 작거나 같다.
이 때 경우의 수는 2가지가 나온다.
만약 n^2 - dist가 최고 속도 n보다 작다면 워프 횟수는 2*n - 1이고
그렇지 않다면 워프 횟수는 2*n - 2 <=> 2*(n-1) 가 나온다.

### 입력 코드

``` C++
int t;
std::cin >> t;

for (int i = 0; i < t; ++i) {
    long long x, y;
    std::cin >> x >> y;
}
```

### 출력 코드

``` C++
for (int i = 0; i < t; ++i) {
    std::cout << getMinNumOfOperations(y - x) << std::endl;
}
```

### 워프 횟수 찾기

``` C++
long long getMinNumOfOperations(long long dist) {
    long long warp_count = 0;
    for (long long i = 1; i <= dist; ++i) {
        if (dist <= i*i) {
            if ((i*i - dist) < i)
                warp_count = 2*i - 1;
            else if ((i*i - dist) >= i)
                warp_count = 2*i - 2;
            break;
        }
    }

    return warp_count;
}
```

### 코드

``` C++
#include <iostream>

long long getMinNumOfOperations(long long dist);

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        long long x, y;
        std::cin >> x >> y;

        std::cout << getMinNumOfOperations(y - x) << std::endl;
    }

    return 0;
}

long long getMinNumOfOperations(long long dist) {
    long long warp_count = 0;
    for (long long i = 1; i <= dist; ++i) {
        if (dist <= i*i) {
            if ((i*i - dist) < i)
                warp_count = 2*i - 1;
            else if ((i*i - dist) >= i)
                warp_count = 2*i - 2;
            break;
        }
    }

    return warp_count;
}

```

### 공간 복잡도

- O(1)

### 시간 복잡도

- O(n)
