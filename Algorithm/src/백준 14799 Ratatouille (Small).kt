import java.lang.Integer.max
import java.lang.Integer.min
import java.util.*
import kotlin.math.ceil
import kotlin.math.floor

fun isCanSolution(recipe: List<Int>, amount: List<List<Int>>, index: Queue<Int>): Boolean {
    val div = mutableListOf<Pair<Int, Int>>()
    index.forEachIndexed { i, j ->
        val require = recipe[i]
        val current = amount[i][j]

        div.add(current to require)
    }
    val min = max(
        div.map { (current, require) -> floor(current.toDouble() * 10 / 11 / require).toInt() }.minOrNull() as Int - 1,
        1
    )
    val max = div.map { (current, require) -> ceil(current.toDouble() * 10 / 9 / require).toInt() }.maxOrNull() as Int + 1
    for (i in min..max) {
        if (div.all { (current, require) -> i * require * 9 <= current * 10 && current * 10 <= i * require * 11}) {
            return true
        }
    }

    return false
}

fun solve(recipe: List<Int>, amount: List<List<Int>>, index: Queue<Int> = LinkedList()): Int {
    if (index.size == amount.size) {
        return 1
    }

    var count = 0
    val i = index.size
    amount[i].forEachIndexed { j, _ ->
        index.add(j)
        if (isCanSolution(recipe, amount, index)) {
            count += solve(recipe, amount, index)
        }
        index.poll()
    }

    return count
}

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (i in 0 until T) {
        val N = nextInt()
        val P = nextInt()

        val R = mutableListOf<Int>()
        for (n in 0 until N) {
            R.add(nextInt())
        }

        val Q = mutableListOf<MutableList<Int>>()
        for (n in 0 until N) {
            val current = mutableListOf<Int>()
            for (p in 0 until P) {
                current.add(nextInt())
            }
            Q.add(current)
        }

        println("Case #${i + 1}: ${solve(R, Q)}")
    }
}