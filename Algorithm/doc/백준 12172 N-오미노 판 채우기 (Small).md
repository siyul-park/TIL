# N-오미노 판 채우기 (Small)  

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 5 초      | 512 MB      | 24   | 19   | 19        | 82.609%   |

## 문제

N-오미노는 이차원 평면 위에 N개의 정사각형이 연결된 도형이다. 1-오미노는 1*1 크기의 정사각형이다. 그래서 n-노미노는 n - 1오미노에 1-오미노, 즉 1*1짜리 정사각형을 추가 한 것과 같다. 단, 두 N-오미노가 합동이면 같다고 가정한다.

아래에는 가능한 5가지 4-오미노가 있다.

![images-73.png](https://upload.acmicpc.net/e9ed4bdd-14d6-477c-85f1-4b487f2c094f/-/preview/)

아래에는 전체 108가지의 7-오미노 중 일부가 있다.

![images-74.png](https://upload.acmicpc.net/002f9f2d-5cde-4031-9b74-950f14df52b4/-/preview/)

철수와 동수는 변수 X, R, C가 정해진 상태에서 아래의 절차대로 게임을 진행하려고 한다.

1.철수는 가능한 X-오미노 중에서 하나를 고른다.                  

2.동수는 여러 가지 X-오미노를 이용해서 넘치지도 부족하지도 않게 R*C 판을 채운다. 단, 철수가 고른 X-오미노를 적어도 한개를 이용해야 하며 X-오미노를 뒤집거나 회전하여 이용해도 된다. 동수가 위의 조건을 만족하면서 판을 채우면 동수는 승리하고 판을 채우지 못하면 패배한다.

X, R, C가 주어질때 철수가 무조건 이길지 동수가 무조건 이길지 판별하라.

## 입력

입력의 첫째 줄에는 테스트케이스의 수 T가 주어진다

다음 T개의 줄에서는 각각 X, R, C가 차례대로 주어진다.

**T** = 64., 1 ≤ **X, R, C** ≤ 4

## 출력

각각의 테스트케이스에 대하여 "Case #x:y"를 출력한다. 이때 x는 테스트케이스 번호(1부터 시작한다). 철수가 선택했을때 무조건 이기는 X-오미노가 하나라도 있으면 y는 RICHARD이고 하나도 없으면 y는 GABRIEL이다.

## 예제 입력 1 

```
4
2 2 2
2 1 3
4 4 1
3 2 3
```

## 예제 출력 1

```
Case #1: GABRIEL
Case #2: RICHARD
Case #3: RICHARD
Case #4: GABRIEL
```

## 힌트

Case #1에서는 철수는 선택할 수 있는 2-오미노가 하나 밖에 없다--1*2짜리 직사각형. 2*2판은 1*2 직사각형 두개로 무조건 채울수 있으므로 동수 승!

Case #2에서도 철수는 선택할 수 있는 2-오미노가 하나 밖에 없다--1*2짜리 직사각형. 하지만 동수가 그 2-오미노를 어느것에 놓더라도 1*1이 하나 남으므로 철수 승!

Case #3에서 철수가 이길수 있는 방법은 2*2짜리 4-오미노를 선택하는 것이다. 1*4판에다가 2*2정사각형은 절대 넣을 수 없으므로 철수 승!

Case #4에서는 1*3짜리 3-오미노 또는 L모양으로 생긴 3-오미노를 선택해야 한다. 두 경우 모두 동수가 2*3판에 하나를 놓고 똑같은 모양 하나를 더 넣으면 되므로 동수 승!

## 출처

https://www.acmicpc.net/problem/12172



# 풀이

C * R 이 X 로 나누어 지는지 확인한다. 만약 나눌수 없다면 답이 될수 없다. 
X + 1 / 2 가 min(R, C) 라면 답이 될수 없다. 
X >= 7이면 답이 될수 없다. 
그후 X 가 7보다 작을때 안되는 경우를 전부 찾는다



```kotlin
import java.lang.Integer.max
import java.lang.Integer.min
import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (i in 1 .. T) {
        val X = nextInt()
        val R = nextInt()
        val C = nextInt()

        var result = true
        if ((R * C) % X != 0) {
            result = false
        } else if (X >= 7) {
            result = false
        } else if ((X + 1) / 2 > min(R, C)){
            result = false
        } else if (X == 4 && min(R, C) == 2) {
            result = false
        } else if (X == 5 && min(R, C) == 3 && max(R, C) <= 5) {
            result = false
        } else if (X == 6 && min(R, C) == 3) {
            result = false
        }

        if (result) {
            println("Case #${i}: GABRIEL")
        } else {
            println("Case #${i}: RICHARD")
        }
    }
}
```



## 시간 복잡도

O(1)



## 공간 복잡도

O(1)



## 오답노트

| 29342823 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [12172](https://www.acmicpc.net/problem/12172)               | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29342823) / [수정](https://www.acmicpc.net/submit/12172/29342823) | 1015 | [16분 전](javascript:void(0);) |
| -------- | ----------------------------------------------------- | ------------------------------------------------------------ | ---------- | ---- | ---- | ------------------------------------------------------------ | ---- | ------------------------------ |
| 29342813 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [12172](https://www.acmicpc.net/problem/12172) | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29342813) / [수정](https://www.acmicpc.net/submit/12172/29342813) | 1015 | [17분 전](javascript:void(0);) |
| 29342670 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [12172](https://www.acmicpc.net/problem/12172) | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29342670) / [수정](https://www.acmicpc.net/submit/12172/29342670) | 970  | [21분 전](javascript:void(0);) |
| 29342445 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [12172](https://www.acmicpc.net/problem/12172) | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29342445) / [수정](https://www.acmicpc.net/submit/12172/29342445) | 967  | [28분 전](javascript:void(0);) |
| 29342403 | [kdpark0723](https://www.acmicpc.net/user/kdpark0723) | [12172](https://www.acmicpc.net/problem/12172) | 틀렸습니다 |      |      | [Kotlin (JVM)](https://www.acmicpc.net/source/29342403) / [수정](https://www.acmicpc.net/submit/12172/29342403) | 935  | [29분 전](javascript:void(0);) |

- 생각 못한 경우의 수가 있었다