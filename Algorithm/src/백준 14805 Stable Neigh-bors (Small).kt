import java.util.*
import kotlin.math.abs

fun getPrevIndex(size: Int, index: Int): Int {
    return if (index == 0) {
        size - 1
    } else {
        index - 1
    }
}

fun getNextIndex(size: Int, index: Int): Int {
    return if (index == size - 1) {
        0
    } else {
        index + 1
    }
}

fun getStable(size: Int, unicorns: List<Int>): List<Int>? {
    val current = unicorns.toMutableList()
    val solution = mutableListOf<Int?>()
    for (i in 0 until size) {
        solution.add(null)
    }

    fun canSolve(index: Int): Boolean {
        val prev = getPrevIndex(size, index)
        val next = getNextIndex(size, index)

        val prevUnicorn = solution[prev]
        val nextUnicorn = solution[next]
        val currentUnicorn = solution[index] ?: return false

        if (prevUnicorn != null && (abs(prevUnicorn - currentUnicorn) <= 1 || abs(prevUnicorn - currentUnicorn) == 5)) {
            return false
        }
        if (nextUnicorn != null && (abs(nextUnicorn - currentUnicorn) <= 1 || abs(nextUnicorn - currentUnicorn) == 5)) {
            return false
        }
        return true
    }

    fun solve(index: Int): Boolean {
        if (index == size) {
            return true
        }

        for (i in current.indices) {
            if (current[i] == 0) {
                continue
            }

            solution[index] = i
            current[i]--
            if (canSolve(index) && solve(index + 1)) {
                return true
            }
            current[i]++
            solution[index] = null
        }

        return false
    }

    return if (solve(0)) {
        solution.filterNotNull()
    } else {
        null
    }
}

val color = listOf("R", "O", "Y", "G", "B", "V")
fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (t in 1..T) {
        val N = nextInt()
        val unicorns = mutableListOf<Int>()

        for (i in 0 until 6) {
            unicorns.add(nextInt())
        }

        println("Case #${t}: ${getStable(N, unicorns)?.joinToString("") { color[it] } ?: "IMPOSSIBLE"}")
    }
}