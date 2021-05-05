import java.util.*

fun solve(array: String, edge: Map<Int, List<Int>>): Int {
    var count = 0

    edge.filterKeys { array[it] == '1' }
        .forEach { (_, link) -> link.forEach { end ->
            if (array[end] == '1') {
                count++
            }
        } }

    val visited = MutableList(array.length) { false }
    fun search(current: Int): Int {
        if (array[current] == '1') {
            return 1
        }

        if (visited[current]) {
            return 0
        }
        visited[current] = true

        return edge[current]
            ?.map { search(it) }
            ?.sum()
            ?: 0
    }

    for (i in array.indices) {
        if (array[i] == '0') {
            val linked = search(i)
            count += linked * (linked - 1)
        }
    }

    return count
}

fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val A = next()

    val edge = mutableMapOf<Int, MutableList<Int>>()
    for (i in 0 until N - 1) {
        val u = nextInt() - 1
        val v = nextInt() - 1

        var list = edge[u] ?: mutableListOf()
        list.add(v)
        edge[u] = list

        list = edge[v] ?: mutableListOf()
        list.add(u)
        edge[v] = list
    }

    println(solve(A, edge))
}