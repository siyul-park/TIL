# Strongly Connected Component

| 시간 제한 | 메모리 제한 | 제출 | 정답 | 맞은 사람 | 정답 비율 |
| :-------- | :---------- | :--- | :--- | :-------- | :-------- |
| 2 초      | 128 MB      | 7121 | 3667 | 1992      | 47.827%   |

## 문제

방향 그래프가 주어졌을 때, 그 그래프를 SCC들로 나누는 프로그램을 작성하시오.

방향 그래프의 SCC는 우선 정점의 최대 부분집합이며, 그 부분집합에 들어있는 서로 다른 임의의 두 정점 u, v에 대해서 u에서 v로 가는 경로와 v에서 u로 가는 경로가 모두 존재하는 경우를 말한다.

![img](https://www.acmicpc.net/JudgeOnline/upload/201008/scco.PNG)

예를 들어 위와 같은 그림을 보자. 이 그래프에서 SCC들은 {a, b, e}, {c, d}, {f, g}, {h} 가 있다. 물론 h에서 h로 가는 간선이 없는 경우에도 {h}는 SCC를 이룬다.

## 입력

첫째 줄에 두 정수 V(1 ≤ V ≤ 10,000), E(1 ≤ E ≤ 100,000)가 주어진다. 이는 그래프가 V개의 정점과 E개의 간선으로 이루어져 있다는 의미이다. 다음 E개의 줄에는 간선에 대한 정보를 나타내는 두 정수 A, B가 주어진다. 이는 A번 정점과 B번 정점이 연결되어 있다는 의미이다. 이때 방향은 A → B가 된다.

정점은 1부터 V까지 번호가 매겨져 있다.

## 출력

첫째 줄에 SCC의 개수 K를 출력한다. 다음 K개의 줄에는 각 줄에 하나의 SCC에 속한 정점의 번호를 출력한다. 각 줄의 끝에는 -1을 출력하여 그 줄의 끝을 나타낸다. 각각의 SCC를 출력할 때 그 안에 속한 정점들은 오름차순으로 출력한다. 또한 여러 개의 SCC에 대해서는 그 안에 속해있는 가장 작은 정점의 정점 번호 순으로 출력한다.

## 예제 입력 1

```
7 9
1 4
4 5
5 1
1 6
6 7
2 7
7 3
3 7
7 2
```

## 예제 출력 1

```
3
1 4 5 -1
2 3 7 -1
6 -1
```

## 출처

https://www.acmicpc.net/problem/2150



# 풀이

**코사라주 알고리즘** 를 이용해서 푼다. https://jason9319.tistory.com/98
처음 접근 방식은 Union Find 와 DFS 를 사용해서 A 와 B 가 연결이 되어 있는지 전부 확인 한다음에 Union Find 로 상호 연결이 되어 있다면 그 집합을 합치는 방식으로 생각을 했다. 다만 이 경우 연결이 되어 있는지 전부 확인 하기 위해서 DFS 가 종료 되면 하위 그래프가 방문한 노드를 리스트로 주고 자신은 그 리스트를 전부 방문 할수 있다고 체크해야 한다. 이때 O((V+E)*V) 시간이 걸린다. 그리고 Union Find 하는 과정에서 O(V^2) 가 걸린다.



## 코드

```kotlin
import java.util.*

fun reverseEdges(edges: List<List<Int>>): List<List<Int>> {
    val reveredEdges = mutableListOf<MutableList<Int>>()
    for (i in edges.indices) {
        reveredEdges.add(mutableListOf())
    }

    for (i in edges.indices) {
        edges[i].forEach {
            reveredEdges[it].add(i)
        }
    }

    return reveredEdges
}

fun findAllSCC(edges: List<List<Int>>): List<List<Int>> {
    val visited = MutableList(edges.size) { false }
    val stack = Stack<Int>()

    fun dfs(current: Int) {
        if (visited[current]) {
            return
        }
        visited[current] = true

        edges[current].forEach { next ->
            dfs(next)
        }

        stack.add(current)
    }

    for (i in edges.indices) {
        dfs(i)
    }

    visited.replaceAll { false }

    val reveredEdges = reverseEdges(edges)
    fun reverseDfs(current: Int, route: MutableList<Int>) {
        if (visited[current]) {
            return
        }
        visited[current] = true

        reveredEdges[current].forEach { next ->
            reverseDfs(next, route)
        }

        route.add(current)
    }

    val sccs = mutableListOf<List<Int>>()
    while (stack.isNotEmpty()) {
        val value = stack.pop()
        val scc = mutableListOf<Int>()
        reverseDfs(value, scc)
        if (scc.isNotEmpty()) {
            sccs.add(scc)
        }
    }

    return sccs
}

fun printSCC(scc: List<List<Int>>) {
    val sorted = mutableListOf<List<Int>>()
    val order = TreeMap<Int, Int>()
    scc.forEachIndexed { i, it ->
        val list = it.sorted()
        sorted.add(list)
        order[list[0]] = i
    }

    println(scc.size)
    order.values.forEach {
        println("${sorted[it].map { it + 1 }.joinToString(" ")} -1")
    }
}

fun main() = with(Scanner(System.`in`)) {
    val V = nextInt()
    val E = nextInt()

    val edges = mutableListOf<MutableList<Int>>()
    for (i in 0 until V) {
        edges.add(mutableListOf())
    }

    for (i in 0 until E) {
        val A = nextInt()
        val B = nextInt()

        edges[A - 1].add(B - 1)
    }

    val scc = findAllSCC(edges)
    printSCC(scc)
}
```



## 시간 복잡도

O(V + E)



## 공간 복잡도

O(V + E) 