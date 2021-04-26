# Alphabet Cake (Small) 스페셜 저지출처다국어분류

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 5 초      | 512 MB      | 76   | 56   | 46        | 75.410%   |

## 문제

You are catering a party for some children, and you are serving them a cake in the shape of a grid with **R** rows and **C** columns. Your assistant has started to decorate the cake by writing every child's initial in icing on exactly one cell of the cake. Each cell contains at most one initial, and since no two children share the same initial, no initial appears more than once on the cake.

Each child wants a single rectangular (grid-aligned) piece of cake that has their initial and no other child's initial(s). Can you find a way to assign every blank cell of the cake to one child, such that this goal is accomplished? It is guaranteed that this is always possible. There is no need to split the cake evenly among the children, and one or more of them may even get a 1-by-1 piece; this will be a valuable life lesson about unfairness.

## 입력

The first line of the input gives the number of test cases, **T**. **T** test cases follow. Each begins with one line with two integers **R** and **C**. Then, there are **R** more lines of **C**characters each, representing the cake. Each character is either an uppercase English letter (which means that your assistant has already added that letter to that cell) or `?`(which means that that cell is blank).

Limits

- 1 ≤ **T** ≤ 100.
- There is at least one letter in the input grid.
- No letter appears in more than one cell in the input grid.
- It is guaranteed that at least one answer exists for each test case.
- 1 ≤ **R** ≤ 12.
- 1 ≤ **C** ≤ 12.
- **R** × **C** ≤ 12.

## 출력

For each test case, output one line containing `Case #x:` and nothing else. Then output **R**more lines of **C** characters each. Your output grid must be identical to the input grid, but with *every* `?` replaced with an uppercase English letter, representing that that cell appears in the slice for the child who has that initial. You may not add letters that did not originally appear in the input. In your grid, for each letter, the region formed by all the cells containing that letter must be a single grid-aligned rectangle.

If there are multiple possible answers, you may output any of them.

## 예제 입력 1 복사

```
3
3 3
G??
?C?
??J
3 4
CODE
????
?JAM
2 2
CA
KE
```

## 예제 출력 1 복사

```
Case #1:
GGJ
CCJ
CCJ
Case #2:
CODE
COAE
JJAM
Case #3:
CA
KE
```

## 힌트

The sample output displays one set of answers to the sample cases. Other answers may be possible.

## 출처

https://www.acmicpc.net/problem/14797



## 풀이

~~백트레킹을 이용해서 푼다~~

이미 그리드에 채워진 값을을 상하 좌우로 퍼트리면서 채운다



### 전체 코드

```kotlin
import java.lang.StringBuilder
import java.util.*

typealias Grid = MutableList<MutableList<Char?>>

fun createGrid(row: Int, col: Int): Grid {
    return MutableList(row) { MutableList(col) { null } }
}

fun solve(grid: Grid) {
    val row = grid.size
    val col = grid[0].size

    for (i in 0 until row) {
        var pre: Char? = null
        for (j in 0 until col) {
            if (grid[i][j] != null) {
                pre = grid[i][j]
                continue
            }

            if (grid[i][j] == null) {
                grid[i][j] = pre
            }
        }
    }

    for (i in 0 until row) {
        var pre: Char? = null
        for (j in 0 until col) {
            if (grid[i][col - j -1] != null) {
                pre = grid[i][col - j -1]
                continue
            }

            if (grid[i][col - j -1] == null) {
                grid[i][col - j -1] = pre
            }
        }
    }

    for (i in 0 until col) {
        var pre: Char? = null
        for (j in 0 until row) {
            if (grid[j][i] != null) {
                pre = grid[j][i]
                continue
            }

            if (grid[j][i] == null) {
                grid[j][i] = pre
            }
        }
    }

    for (i in 0 until col) {
        var pre: Char? = null
        for (j in 0 until row) {
            if (grid[row - j - 1][i] != null) {
                pre = grid[row - j - 1][i]
                continue
            }

            if (grid[row - j - 1][i] == null) {
                grid[row - j - 1][i] = pre
            }
        }
    }
}

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (i in 0 until T) {
        val R = nextInt()
        val C = nextInt()

        val grid = createGrid(R, C)
        for (r in 0 until R) {
            val row = next()
            for (c in 0 until C) {
                if (row[c] != '?') {
                    grid[r][c] = row[c]
                }
            }
        }

        solve(grid)

        println("Case #${i + 1}:")
        grid.forEach { row ->
            println(row.fold(StringBuilder()) { acc, char -> acc.append(char) }.toString())
        }
    }
}
```



### 시간 복잡도

O(N)

### 공간복잡도

O(N)



## 오답 노트

- | 제출 번호 | 아이디                                              | 문제                                           | 결과             | 메모리 | 시간 | 언어                                                         | 코드 길이 | 제출한 시간                    |
  | :-------- | :-------------------------------------------------- | :--------------------------------------------- | :--------------- | :----- | :--- | :----------------------------------------------------------- | :-------- | :----------------------------- |
  | 28731042  | [siyualbak](https://www.acmicpc.net/user/siyualbak) | [14797](https://www.acmicpc.net/problem/14797) | **맞았습니다!!** | 14908  | 180  | [Kotlin (JVM)](https://www.acmicpc.net/source/28731042) / [수정](https://www.acmicpc.net/submit/14797/28731042) | 2169      | [1분 전](javascript:void(0);)  |
  | 28731010  | [siyualbak](https://www.acmicpc.net/user/siyualbak) | [14797](https://www.acmicpc.net/problem/14797) | 틀렸습니다       |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/28731010) / [수정](https://www.acmicpc.net/submit/14797/28731010) | 2152      | [2분 전](javascript:void(0);)  |
  | 28730433  | [siyualbak](https://www.acmicpc.net/user/siyualbak) | [14797](https://www.acmicpc.net/problem/14797) | 틀렸습니다       |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/28730433) / [수정](https://www.acmicpc.net/submit/14797/28730433) | 2552      | [20분 전](javascript:void(0);) |
  | 28730206  | [siyualbak](https://www.acmicpc.net/user/siyualbak) | [14797](https://www.acmicpc.net/problem/14797) | 틀렸습니다       |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/28730206) / [수정](https://www.acmicpc.net/submit/14797/28730206) | 2376      | [26분 전](javascript:void(0);) |
  | 28730029  | [siyualbak](https://www.acmicpc.net/user/siyualbak) | [14797](https://www.acmicpc.net/problem/14797) | 틀렸습니다       |        |      | [Kotlin (JVM)](https://www.acmicpc.net/source/28730029) / [수정](https://www.acmicpc.net/submit/14797/28730029) | 2151      | [31분 전](javascript:void(0);) |

- 백트레킹으로 풀다가 현재 까지 상태가 값이 될수 있는지 확인하는 check 함수를 만들지 못했다.(만든다면 전체 순회를 돌며 BFS 로 재 검색을 돌려야 할듯)

- 그후 문자열을 계속 미는 방식으로 수정을 했다