# Pretty Average Primes

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 512 MB      | 23   | 8    | 8         | 72.727%   |

## 문제

For various given positive integers N > 3, find two primes, A and B such that N is the average (mean) of A and B. That is, N should be equal to (A+B)/2.

Recall that a prime number is an integer P > 1 which is only divisible by 1 and P. For example, 2, 3, 5, 7, 11 are the first few primes, and 4, 6, 8, 9 are not prime numbers.

## 입력

The first line of input is the number T (1 ≤ T ≤ 1000), which is the number of test cases. Each of the next T lines contain one integer Ni (4 ≤ Ni ≤ 1000000, 1 ≤ i ≤ T).

For 6 of the available 15 marks, all Ni < 1000.

## 출력

The output will consist of T lines. The ith line of output will contain two integers, Ai and Bi, separated by one space. It should be the case that Ni = (Ai + Bi)/2 and that Ai and Bi are prime numbers.

If there are more than one possible Ai and bi for a particular Ni, output any such pair. The order of the pair Ai and Bi does not matter.

It will be the case that there will always be at least one set of values Ai and Bi for any given Ni.



## 예제 입력 1 복사

```
4
8
4
7
21
```

## 예제 출력 1 복사

```
3 13
5 3
7 7
13 29
```

Notice that:

- 8 = (3 + 13)/2,
- 4 = (5 + 3)/2,
- 7 = (7 + 7)/2,
- 21 = (13 + 29)/2,

It is interesting to note, that we can also write

- 8 = (5 + 11)/2
- 21 = (5 + 37)/2 = (11 + 31)/2 = (19 + 23)/2
- 7 = (3 + 11)/2

and so any of these pairs could have also been used in output. There is no pairs of primes other than 3 and 5 which average to the value of 4.

## 노트

You may have heard about Goldbach’s conjecture, which states that every even integer greater than 2 can be expressed as the sum of two prime numbers. There is no known proof, yet, so if you want to be famous, prove that conjecture (after you finish the CCC).

This problem can be used to help verify that conjecture, since every even integer can be written as 2N, and your task is to find two primes A and B such that 2N=A+B.

## 출처

<https://www.acmicpc.net/problem/17014>



## 풀이

에라토스테네스의 체를 사용하여 N이하의 소수들을 모두 구하고 소수들을 더해보며 확인한다.



### 입력 코드

```c++
int T;
std::cin >> T;

for (int i = 0; i < T; ++i) {
    int N;
    std::cin >> N;
}
```

### 출력 코드

```c++

for (int i = 0; i < T; ++i) {
    for (int j = N; j > 2; --j) {
        if (isPrime[j] && isPrime[N * 2 - j]) {
            std::cout << j << " " << N * 2 - j << "\n";
            break;
        }
    }
}
```



### 소수 구하기

```c++
std::vector<bool> getPrimes(int N) {
    int size = N * 2 + 1;
    std::vector<bool> isPrime(size, true);

    for (int i = 2; i < size; ++i)
        if (isPrime[i])
            for (int j = i * 2; j < size; j += i)
                isPrime[j] = false;

    return isPrime;
}
```



### 전체 코드

```c++
#include <iostream>
#include <vector>

std::vector<bool> getPrimes(int N) {
    int size = N * 2 + 1;
    std::vector<bool> isPrime(size, true);

    for (int i = 2; i < size; ++i)
        if (isPrime[i])
            for (int j = i * 2; j < size; j += i)
                isPrime[j] = false;

    return isPrime;
}

int main() {
    int T;
    std::cin >> T;

    std::vector<bool> isPrime{getPrimes(1000000)};

    for (int i = 0; i < T; ++i) {
        int N;
        std::cin >> N;

        for (int j = N; j > 2; --j) {
            if (isPrime[j] && isPrime[N * 2 - j]) {
                std::cout << j << " " << N * 2 - j << "\n";
                break;
            }
        }
    }

    return 0;
}
```



## 오답 노트

