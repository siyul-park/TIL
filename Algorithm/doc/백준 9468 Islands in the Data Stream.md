# Islands in the Data Stream  

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 128 MB      | 129  | 117  | 111       | 90.244%   |

## 문제

Given a sequence of integers a1, a2, a3, …, an, an island in the sequence is a contiguous subsequence for which each element is greater than the elements immediately before and after the subsequence. In the examples below, each island in the sequence has a bracket below it. The bracket for an island contained within another island is below the bracket of the containing island.

![img](https://www.acmicpc.net/upload/images/ids.png)

Write a program that takes as input a sequence of 15 non-negative integers, in which each integer differs from the previous integer by at most 1, and outputs the number of islands in the sequence.

## 입력

The first line of input contains a single integer P, (1 ≤ P ≤ 1000), which is the number of data sets that follow. Each data set should be processed identically and independently.

Each data set consists of a single line of input. It contains the data set number, K, followed by 15 non-negative integers separated by a single space. The first and last integers in the sequence will be 0. Each integer will differ from the previous integer by at most 1.

## 출력

For each data set there is one line of output. The single output line consists of the data set number, K, followed by a single space followed by the number of islands in the sequence.

## 예제 입력 1

```
4
1 0 0 1 1 2 2 1 1 0 1 2 2 1 1 0
2 0 1 2 3 4 3 2 1 2 3 4 3 2 1 0
3 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
4 0 1 2 3 4 5 6 7 6 5 4 3 2 1 0
```

## 예제 출력 1 

```
1 4
2 7
3 7
4 7
```

## 출처



# 풀이

전에 값보다 현재 값이 더 작아지면 출력에 1 을 더한다



```kotlin
import java.util.*

fun getNumberOfIslands(sequence: List<Int>): Int {
    var pre = 0
    var count = 0

    sequence.forEach {
        if (it < pre) {
            count++
        }
        pre = it
    }

    return count
}

fun main() = with(Scanner(System.`in`)) {
    val P = nextInt()
    for (i in 1 .. P) {
        val K = nextInt()
        val sequence = mutableListOf<Int>()
        for (j in 0 until 15) {
            sequence.add(nextInt())
        }

        println("$K ${getNumberOfIslands(sequence)}")
    }
}
```



## 시간 복잡도

O(P)



## 공간 복잡도

O(P)