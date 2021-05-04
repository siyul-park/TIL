import java.lang.Integer.max
import java.lang.Integer.min
import java.util.*

data class Link(
    val min: Int,
    val max: Int
) {
    companion object {
        fun of(a: Int, b: Int): Link {
            val min = min(a, b)
            val max = max(a, b)

            return Link(min, max)
        }
    }
}

fun solve(array: String, edge: Map<Int, List<Int>>): Int {
    val inner = array
        .mapIndexed { i, char -> i to char }
        .filter { (_, char) -> char == '1' }
        .map { (i, _) -> i }

    val cache = mutableMapOf<Link, Boolean>()
    fun isCanLinked(link: Link): Boolean = cache[link] ?: run {
        val (start, end) = link
        if (start == end) {
            return@run true
        }

        edge[start]?.let { it.forEach { next ->
            if (array[next] == '1') {
                if (next == end) {
                    return@run true
                } else {
                    return@forEach
                }
            } else {
                if (isCanLinked(Link.of(next, end))) {
                    return@run true
                }
            }
        } }

        false
    }.apply { cache[link] = this }

    var count = 0
    for (i in inner.indices) {
        for (j in i + 1 until inner.size) {
            if (isCanLinked(Link.of(inner[i], inner[j]))) {
                count++
            }
        }
    }

    return count * 2
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