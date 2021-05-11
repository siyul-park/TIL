# Balloons

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 1 초      | 128 MB      | 3    | 1    | 1         | 50.000%   |

## 문제

A group of children came to a toy store. Each of them would like to buy a number of balloons. The children like diversity - none of them wants to have two balloons of the same colour. Help the shop-assistant to check whether orders of all children can be completed within the current assortment of the store.

Write a program that:

- reads a description of the store's assortment and the orders made by children from the standard input,
- checks whether all children can be made happy,
- writes the result to the standard output.

## 입력

The first line of input contains two integers *n* and *m* (1 ≤ *n* ≤ 200 000, 2 ≤ *m* ≤ 200 000), separated by a single space and denoting the number of different colours of balloons that are present in the store and the number of children. The second line of input contains *n* integers *ai* (1 ≤ *ai* ≤ 1 000 000 for 1 ≤ *i* ≤ *n*), separated by single spaces and denoting the quantities of balloons of respective colours. The third line of input contains *m* integers *bi* (1 ≤ *bi* ≤ 1 000 000 for 1 ≤ *i* ≤ *m*), separated by single spaces and denoting the orders of respective children; *bi* = *k* means that the *i*-th child would like to buy *k* balloons, all having different colours.

## 출력

The first and only line of output should contain a single word `TAK` (i.e. *yes* in Polish), if orders of all children can be completed, and `NIE` (i.e. *no* in Polish) otherwise.

## 예제 입력 1

```
4 3
3 2 1 3
1 3 4
```

## 예제 출력 1

```
TAK
```

## 예제 입력 2 

```
4 3
3 2 1 3
1 4 4
```

## 예제 출력 2

```
NIE
```

## 출처

https://www.acmicpc.net/problem/8363



# 풀이

n과 m 의 범위가 상당이 커서 하나하나 빼는것으론 불가능하다. 그래서 a, b 를 정렬을 하고 a 중 작은 값을 먼저 b에 큰 값에 대입을 하는 방법으로 해결을 한다. 만약 남아 있는 풍선 수가 현재 받아야 하는 것 보다 작다면 할당 할수 없다. 남아 있는 풍선 수가 현재 받아야 하는것 보다 크다면 앞에서 부터 그 차만큼의 풍선은 할당이 되지 않는다. 그래서 그부분은 adjust 란 배열을 만들어서 풍선 수를 조정 한다. 그후 (a[current] + adjust[current] - i - 1) > 0 가 되도록 current(정렬된 사용 가능한 풍선중 풍선 개수가 가장 작은것)을 조정한다.



## 코드

```kotlin
import java.util.*
import kotlin.collections.ArrayList

fun main() = with(Scanner(System.`in`)) {
    val n = nextInt()
    val m = nextInt()

    val a = ArrayList<Int>(n)
    for (i in 0 until n) {
        a.add(nextInt())
    }

    val b = ArrayList<Int>(m)
    for (i in 0 until m) {
        b.add(nextInt())
    }

    a.sortDescending()
    b.sortDescending()

    val adjust = MutableList(a.size) { 0 }

    var current = a.size - 1
    b.forEachIndexed { i, numberOfBalloons ->
        if ((current + 1) < numberOfBalloons) {
            println("NIE")
            return@with
        }
        if ((current + 1) > numberOfBalloons) {
            val notAssignment = current - numberOfBalloons
            adjust[notAssignment]++
        }

        while (current > 0 && (a[current] + adjust[current] - i - 1) <= 0) {
            adjust[current - 1] += adjust[current]
            current--
        }
        if (current == 0 && i < b.size - 1) {
            println("NIE")
            return@with
        }
    }

    println("TAK")
}
```



## 시간 복잡도

O(N + M)



## 공간 복잡도

O(N + M)



## 오답노트

|           |                                                       |                                              |             |        |      |                                                              |           |             |
| :-------- | :---------------------------------------------------- | :------------------------------------------- | :---------- | :----- | :--- | :----------------------------------------------------------- | :-------- | :---------- |
| 제출 번호 | 아이디                                                | 문제                                         | 결과        | 메모리 | 시간 | 언어                                                         | 코드 길이 | 제출한 시간 |
| 29185450  | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [8363](https://www.acmicpc.net/problem/8363) | 메모리 초과 |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29185450) / [수정](https://www.acmicpc.net/submit/8363/29185450) | 1044      |             |

- input 저장만 했는데 터졌다.. 인풋 전체를 저장을 하지 않고 해결 할수 있는 방법이 있나..?