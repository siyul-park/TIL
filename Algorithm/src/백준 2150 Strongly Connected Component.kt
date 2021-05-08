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