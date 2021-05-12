# Growing Vegetables is Fun 4  

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 512 MB      | 42   | 30   | 25        | 71.429%   |

## 문제

Bitaro likes gardening. He is now growing plants called Biba-herbs in the garden. There are N Biba-herbs in the garden, planted in a line from the west to the east. The Biba-herbs are numbered from 1 to N from the west to the east. Now, the height of the Biba-herb i (1 ≤ i ≤ N) is Ai.

Due to the breed improvement, if Bitaro waters a Biba-herb once, then its height increases by 1. Since he wants to decorate the garden, he will water the Biba-herbs several times so that the following condition is satisfied.

- After Bitaro finishes watering, let Bi be the height of the Biba-herb i. Then, there exists an integer k (1 ≤ k ≤ N) such that Bj < Bj+1 holds for every 1 ≤ j ≤ k − 1, and Bj > Bj+1 holds for every k ≤ j ≤ N − 1.

However, Bitaro is not good at watering. When he waters Biba-herbs, he can only water consecutive Bibaherbs in an interval. In other words, he chooses integers L and R (1 ≤ L ≤ R ≤ N) and waters the Biba-herbs L, L + 1, . . . , R.

Bitaro wants to minimize the number of times of watering.

Write a program which, given the number of Biba-herbs and their current heights, calculates the minimum number of times of watering so that the above condition is satisfied.

## 입력

Read the following data from the standard input. Given values are all integers.

N
A1 · · · AN

## 출력

Write one line to the standard output. The output should contain the minimum number of times of watering.

## 제한

- 2 ≤ N ≤ 200 000.
- 1 ≤ Ai ≤ 1 000 000 000 (1 ≤ i ≤ N).

## 예제 입력 1

```
5
3 2 2 3 1
```

## 예제 출력 1 

```
3
```

The condition is satisfied if Bitaro waters the Biba-herbs three times as follows.

- Let L = 2 and R = 5. Then Bitaro waters the Biba-herbs 2, 3, 4, 5. The heights of the Biba-herbs become 3, 3, 3, 4, 2 from the west.
- Let L = 2 and R = 3. Then Bitaro waters the Biba-herbs 2, 3. The heights of the Biba-herbs become 3, 4, 4, 4, 2 from the west.
- Let L = 3 and R = 3. Then Bitaro waters the Biba-herb 3. The heights of the Biba-herbs become 3, 4, 5, 4, 2 from the west.

It is impossible to satisfy the condition if Bitaro waters the Biba-herbs less than three times. Hence the minimum number of times of watering is 3.

## 예제 입력 2 

```
5
9 7 5 3 1
```

## 예제 출력 2

```
0
```

Since the condition is already satisfied, the minimum number of times of watering is 0.

## 예제 입력 3 

```
2
2021 2021
```

## 예제 출력 3 

```
1
```

The condition is satisfied if Bitaro waters the Biba-herb 1 by choosing L = 1 and R = 1, or he waters the Biba-herb 2 by choosing L = 2 and R = 2.

## 예제 입력 4

```
8
12 2 34 85 4 91 29 85
```

## 예제 출력 4

```
93
```

## 출처

https://www.acmicpc.net/problem/20984



# 풀이

투 포인터 알고리즘을 사용해서 구한다



```kotlin
import java.util.*
import kotlin.collections.ArrayList

fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val A = ArrayList<Long>(N)

    for (i in 0 until N) {
        A.add(nextLong())
    }

    var startIndex = 0
    var endIndex = A.size - 1
    var count = 0L
    while (startIndex < endIndex) {
        if (A[startIndex] < A[startIndex + 1]) {
            startIndex++
        } else if (A[endIndex] < A[endIndex - 1]) {
            endIndex--
        } else {
            val diffOfStart = A[startIndex] - A[startIndex + 1] + 1
            val diffOfEnd = A[endIndex] - A[endIndex - 1] + 1

            if (diffOfStart <= diffOfEnd) {
                count += diffOfStart
                A[endIndex] -= diffOfStart

                startIndex++
            } else {
                count += diffOfEnd
                A[startIndex] -= diffOfEnd

                endIndex--
            }
        }
    }

    println(count)
}
```



## 시간 복잡도

O(N)



## 공간 복잡도

O(N)



## 오답노트

| 29212259 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [20984](https://www.acmicpc.net/problem/20984) | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29212259) / [수정](https://www.acmicpc.net/submit/20984/29212259) | 1088 | [9분 전](javascript:void(0);)  |
| -------- | ----------------------------------------------------- | ---------------------------------------------- | ---------- | ---- | ---- | ------------------------------------------------------------ | ---- | ------------------------------ |
| 29212118 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [20984](https://www.acmicpc.net/problem/20984) | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29212118) / [수정](https://www.acmicpc.net/submit/20984/29212118) | 1213 | [13분 전](javascript:void(0);) |

- input 값을 int 로 쓰고 있어서 틀렸다 long 으로 바꾸니 해결됨