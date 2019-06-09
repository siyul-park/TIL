# Arithmetic Square

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 512 MB      | 14   | 7    | 4         | 40.000%   |

## 문제

You are given a 3×3 grid which contains integers.

Some of the 9 elements in the grid will have a value already, and the remaining elements will be unspecified.

Your task is to determine values for the unspecified elements such that each row, when read from left-to-right is an arithmetic sequence, and that each column, when read from the top-down, is an arithmetic sequence.

Recall that an arithmetic sequence of length three is a sequence of integers of the form

a, a+d, a+2d

for integer values of a and d. Note that d may be any integer, including zero or a negative integer.

## 입력

The input will be 3 lines long. Each line will have three space-separated values. Each value will either be an integer in the range from −1000000 to 1000000, inclusive, or the symbol X.

For 4 of the 15 marks available, there will be at most 3 X symbols in the input.

For an additional 3 of the 15 marks available, all integer values in the input will be between −10 and 10, inclusive.

For an additional 4 of the 15 marks available, there will be at least 7 X symbols in the input.

For an additional 2 of the 15 marks available, all integer values in the input will be even numbers.

## 출력

The output will be 3 lines long. Each line will have three space-separated integers. All integers that were given in the input must be in their same position (i.e., same row and same column as in the input). All rows and columns must form arithmetic sequences. All integers in the output must be between −1000000000 and 1000000000, inclusive.

If there is more than one solution, output any solution. There is guaranteed to be at least one solution.



## 예제 입력 1 복사

```
8 9 10
16 X 20
24 X 30
```

## 예제 출력 1 복사

```
8 9 10
16 18 20
24 27 30
```

Notice that the second element of the second row must be 16+t and since 20=16+2t, then t=2, and thus, this unspecified element must be 18. A similar argument applies to the second element of the third row.

## 예제 입력 2 복사

```
14 X X
X X 18
X 16 X
```

## 예제 출력 2 복사

```
14 20 26
18 18 18
22 16 10
```

This is one of many possible solutions. For example, another solution is:

```
14 16 18
14 16 18
14 16 18
```



## 출처

<https://www.acmicpc.net/problem/17015>



## 풀이 1차 시도

우선 주어진 조건만으로 성립하는 해를 찾을수 있는지 확인하자. 각 행 또는 열의 요소가 2개이면 나머지 한 요소는 결정이 된다. 그리고 각 행들을 독립되어 있고 각 열들 또한 동일하다. 모든 행과 모든 열을 확인한후 구해진 새로운 결과가 계산전 결과와 동일하다면 더 이상 찾을 수 있는 것이 없다. 그리고 이 단계후 나오는 결과를 A라 하자.

A의 결과에 찾을 수 없었던 요소 x가 존재한다고 하자. 이때 x가 속한 행, 열은 원소수가 1개 또는 0개 이다. 

1) 원소수 1개

| x    |      | b    |
| ---- | ---- | ---- |
|      |      |      |
| a    |      |      |

x가 결정되면 x가 속한 행과 열의 모든 요소 또한 결정이 된다

| x         | (x + b)/2 | b    |
| --------- | --------- | ---- |
| (x + a)/2 |           |      |
| a         |           |      |

아직 정해지지 않은 곳의 원소중 하나 가 결정되면 모든 원소는 결정된다.



따라서 최소 4개의 원소가 각 행, 열에 최대 2개씩 존재한다면 그 해는 1개로 결정이 된다. 



| x1 x2 x3 | | 1  |    | 0 |

| y1 y2 y3 | | -2 | = | 0 |

| z1 z2 z3 | | 1  |     | 0 |



| x1 y1 z1 | | 1  |    | 0 |

| x2 y2 z2 | | -2 | = | 0 |

| x3 y3 z3 | | 1  |     | 0 |



x2 = (x1 + x3) / 2

y1 = (x1 + z1) / 2

y2 = (x2 + z2) / 2

= ((x1 + x3) / 2 + (z1 + z3) / 2) / 2

y3 = (x3 + z3) / 2

z3 = (z1 + z3) / 2