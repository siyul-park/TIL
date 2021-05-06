import java.util.*

val dx = listOf(-1, 1, 0, 0)
val dy = listOf(0, 0, -1, 1)

fun calculateMinTime(points: List<Pair<Int, Int>>, size: Int): Int {
    var numberOfCivilization = points.size
    var count = 0

    val map = mutableMapOf<Pair<Int, Int>, Int>()
    val parent = mutableMapOf<Int, Int>()

    points.forEachIndexed { i, it -> map[it] = i }
    points.forEachIndexed { i, _ -> parent[i] = i }

    fun findParent(idx: Int): Int {
        return if (idx == parent[idx]) {
            idx
        } else {
            val next = findParent(parent[idx] ?: throw Exception())
            parent[idx] = next
            next
        }
    }

    fun merge(a: Int, b: Int) {
        val parentA = findParent(a)
        val parentB = findParent(b)

        if (parentA != parentB) {
            parent[parentA] = parentB
        }
    }

    fun isSameParent(a: Int, b: Int): Boolean {
        return findParent(a) == findParent(b)
    }

    val unionQueue = LinkedList<Pair<Int, Int>>()
    val queue = LinkedList<Pair<Int, Int>>()

    points.forEach { unionQueue.add(it) }

    while (numberOfCivilization > 1) {
        while (unionQueue.isNotEmpty()) {
            val current = unionQueue.poll()
            queue.add(current)

            val currentCivil = map[current] ?: throw Exception()
            for (i in 0 until 4) {
                val next = (current.first + dx[i]) to (current.second + dy[i])

                if (next.first < 0 || next.first >= size || next.second < 0 || next.second >= size) {
                    continue
                }

                val existed = map[next] ?: continue
                if (currentCivil != existed && !isSameParent(currentCivil, existed)) {
                    merge(currentCivil, existed)
                    numberOfCivilization--
                }
            }
        }

        if (numberOfCivilization == 1) {
            break
        }

        while (queue.isNotEmpty()) {
            val current = queue.poll()

            for (i in 0 until 4) {
                val next = (current.first + dx[i]) to (current.second + dy[i])

                if (next.first < 0 || next.first >= size || next.second < 0 || next.second >= size) {
                    continue
                }

                val existed = map[next]
                if (existed == null) {
                    map[next] = map[current] ?: throw Exception()
                    unionQueue.add(next)
                }
            }
        }

        count++
    }

    return count
}



fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val K = nextInt()

    val points = mutableListOf<Pair<Int, Int>>()
    for (i in 0 until K) {
        points.add((nextInt() - 1) to (nextInt() - 1))
    }

    println(calculateMinTime(points, N))
}