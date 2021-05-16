# Exotic Foods  

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 128 MB      | 28   | 12   | 11        | 64.706%   |

## 문제

Traveling through time is tiring and can really work up an appetite. Luckily, there is a huge variety of exotic foods to be found throughout time, such as dinosaur meat, dodo-bird eggs, mammoth milk, etc. Unfortunately, there is not enough space in the time machine to store a refrigerator, so if Tim wants to eat an exotic food, he must eat it right away. But, if he eats, he will become very full and will not be able to eat again while visiting the immediately following time period. Each food has a perceived value to Tim, and his goal is to maximize the total sum value for all the foods he actually eats. The order in which he visits the time periods has already been set and cannot be changed. By selectively choosing which foods he eats, what is the maximum total sum value he can achieve?

## 입력

The first line is the number K of input data sets, followed by the K data sets, each of the following form: The first line of each data set contains an integer n indicating the number of foods Tim will come across, where 1 ≤ n ≤ 50000. Next follows one line containing n integers vi, 1 ≤ vi ≤ 1000, indicating the values of the foods. The order of vi in the list is also the order in which Tim will encounter them.

## 출력

For each data set, output “Data Set x:” on a line by itself, where x is its number. On the next line, output the maximum sum of values Tim can achieve. Each data set should be followed by a blank line.

## 예제 입력 1 복사

```
2
3
3 8 4
4
12 8 9 10
```

## 예제 출력 1 복사

```
Data Set 1:
8

Data Set 2:
22
```

## 출처

https://www.acmicpc.net/problem/5132



 # 풀이

P(i) = max(V(i) + P(i + 2), P(i + 1))



```kotlin
import java.util.*
import kotlin.math.max

fun getMaxFoodValue(foods: List<Int>): Int {
    val cache = MutableList(foods.size) { -1 }

    fun solve(index: Int): Int {
        if (index >= foods.size) {
            return 0
        }

        if (cache[index] != -1) {
            return cache[index]
        }

        return max(foods[index] + solve(index + 2), solve(index + 1))
            .also { cache[index] = it }
    }

    return solve(0)
}

fun main() = with(Scanner(System.`in`)) {
    val K = nextInt()
    for (i in 1 .. K) {
        val n = nextInt()
        val foods = mutableListOf<Int>()
        for (j in 0 until n) {
            foods.add(nextInt())
        }

        println("Data Set ${i}:\n${getMaxFoodValue(foods)}\n")
    }
}
```



## 시간 복잡도

O(K*n)



## 공간 복잡도

O(n)



## 오답 노트

| 출 번호  | 아이디                                                | 문제                                         | 결과             | 메모리 | 시간 | 언어                                                         | 코드 길이 | 제출한 시간                   |
| :------- | :---------------------------------------------------- | :------------------------------------------- | :--------------- | :----- | :--- | :----------------------------------------------------------- | :-------- | :---------------------------- |
| 29322942 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [5132](https://www.acmicpc.net/problem/5132) | **맞았습니다!!** | 178304 | 984  | [Kotlin (JVM)](https://www.acmicpc.net/source/29322942) / [수정](https://www.acmicpc.net/submit/5132/29322942) | 753       | [1분 전](javascript:void(0);) |
| 29322929 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [5132](https://www.acmicpc.net/problem/5132) | 시간 초과        |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29322929) / [수정](https://www.acmicpc.net/submit/5132/29322929) | 713       | [1분 전](javascript:void(0);) |

- Cache 를 업데이트 안해줬다.