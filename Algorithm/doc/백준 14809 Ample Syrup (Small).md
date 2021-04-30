# Ample Syrup (Large) 스페셜 저지출처다국어분류

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 5 초      | 512 MB      | 60   | 25   | 23        | 79.310%   |

## 문제

The kitchen at the Infinite House of Pancakes has just received an order for a stack of **K**pancakes! The chef currently has **N** pancakes available, where **N** ≥ **K**. Each pancake is a cylinder, and different pancakes may have different radii and heights.

As the sous-chef, you must choose **K** out of the **N** available pancakes, discard the others, and arrange those **K** pancakes in a stack on a plate as follows. First, take the pancake that has the largest radius, and lay it on the plate on one of its circular faces. (If multiple pancakes have the same radius, you can use any of them.) Then, take the remaining pancake with the next largest radius and lay it on top of that pancake, and so on, until all **K** pancakes are in the stack and the centers of the circular faces are aligned in a line perpendicular to the plate, as illustrated by this example:

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14809/1.png)

You know that there is only one thing your diners love as much as they love pancakes: syrup! It is best to maximize the total amount of exposed pancake surface area in the stack, since more exposed pancake surface area means more places to pour on delicious syrup. Any part of a pancake that is not touching part of another pancake or the plate is considered to be exposed.

If you choose the **K** pancakes optimally, what is the largest total exposed pancake surface area you can achieve?

## 입력

The first line of the input gives the number of test cases, **T**. **T** test cases follow. Each begins with one line with two integers **N** and **K**: the total number of available pancakes, and the size of the stack that the diner has ordered. Then, **N** more lines follow. Each contains two integers **Ri** and **Hi**: the radius and height of the i-th pancake, in millimeters.

Limits

- 1 ≤ **T** ≤ 100.
- 1 ≤ **K** ≤ **N**.
- 1 ≤ **Ri** ≤ 106, for all i.
- 1 ≤ **Hi** ≤ 106, for all i.
- 1 ≤ **N** ≤ 1000.

## 출력

For each test case, output one line containing `Case #x: y`, where `x` is the test case number (starting from 1) and `y` is the maximum possible total exposed pancake surface area, in millimeters squared. `y` will be considered correct if it is within an absolute or relative error of 10-6 of the correct answer.

## 예제 입력 1 복사

```
4
2 1
100 20
200 10
2 2
100 20
200 10
3 2
100 10
100 10
100 10
4 2
9 3
7 1
10 1
8 4
```

## 예제 출력 1 복사

```
Case #1: 138230.076757951
Case #2: 150796.447372310
Case #3: 43982.297150257
Case #4: 625.176938064
```

## 힌트

In Sample Case #1, the "stack" consists only of one pancake. A stack of just the first pancake would have an exposed area of π × **R0**2 + 2 × π * **R0** × **H0** = 14000π mm2. A stack of just the second pancake would have an exposed area of 44000π mm2. So it is better to use the second pancake.

In Sample Case #2, we can use both of the same pancakes from case #1. The first pancake contributes its top area and its side, for a total of 14000π mm2. The second pancake contributes some of its top area (the part not covered by the first pancake) and its side, for a total of 34000π mm2. The combined exposed surface area is 48000π mm2.

In Sample Case #3, all of the pancakes have radius 100 and height 10. If we stack two of these together, we effectively have a single new cylinder of radius 100 and height 20. The exposed surface area is 14000π mm2.

In Sample Case #4, the optimal stack uses the pancakes with radii of 8 and 9.

## 출처

https://acmicpc.net/problem/14810



## 풀이

가장 밑에 있는 케이크를 강제 하고 가장 밑에 있는 케이크 보다 반지름이 작은 것중 옆면의 표면적이 큰 순서대로 K 개를 뽑는다



### 전체 코드

```kotlin
import java.lang.Long.max
import java.util.*

data class Cake(
    val round: Long,
    val height: Long
) {
    val sideWidth = round * 2 * height

    val topWidth = round * round
}

fun getMaxSurfaceArea(cakes: List<Cake>, amount: Int): Double {
    val sorted = cakes.sortedBy { it.sideWidth }.reversed()

    var value = 0L
    cakes.forEach { cake ->
        val other = sorted.filter { it !== cake && it.round <= cake.round }
        if (other.size < amount - 1) {
            return@forEach
        }

        var currnet = cake.sideWidth + cake.topWidth
        for (i in 0 until (amount - 1)) {
            currnet += other[i].sideWidth
        }

        value = max(value, currnet)
    }

    return value * Math.PI
}

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (case in 1..T) {
        val N = nextInt()
        val K = nextInt()

        val cakes = mutableListOf<Cake>()
        for (i in 0 until N) {
            val R = nextLong()
            val H = nextLong()
            cakes.add(Cake(R, H))
        }

        println("Case #${case}: ${getMaxSurfaceArea(cakes, K)}")
    }
}
```



### 시간 복잡도

O(N*N)

### 공간복잡도

O(N)



## 오답 노트

| 제출 번호 | 아이디                                                | 문제                                           | 결과             | 메모리 | 시간 | 언어                                                         | 코드 길이 | 제출한 시간                   |
| :-------- | :---------------------------------------------------- | :--------------------------------------------- | :--------------- | :----- | :--- | :----------------------------------------------------------- | :-------- | :---------------------------- |
| 28855499  | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [14809](https://www.acmicpc.net/problem/14809) | **맞았습니다!!** | 21428  | 240  | [Kotlin (JVM)](https://www.acmicpc.net/source/28855499) / [수정](https://www.acmicpc.net/submit/14809/28855499) | 1125      | [2분 전](javascript:void(0);) |
| 28855336  | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [14809](https://www.acmicpc.net/problem/14809) | 틀렸습니다       |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/28855336) / [수정](https://www.acmicpc.net/submit/14809/28855336) | 1117      | [6분 전](javascript:void(0);) |
| 28855271  | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [14809](https://www.acmicpc.net/problem/14809) | 틀렸습니다       |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/28855271) / [수정](https://www.acmicpc.net/submit/14809/28855271) | 1129      | [8분 전](javascript:void(0);) |

인풋이 Int 형을 초과했다