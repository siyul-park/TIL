import java.lang.Integer.max
import java.lang.Integer.min
import java.util.*

fun getMinAndMaxTime(ants: List<Int>, stickLength: Int): Pair<Int, Int> {
    val diff = ants.map { it to stickLength - it }

    val minOfDiff = diff.map { (a, b) -> min(a, b) }
    val maxOfDiff = diff.map { (a, b) -> max(a, b) }

    val minOfTime = minOfDiff.maxOrNull() ?: throw Exception()
    val maxOfTime = maxOfDiff.maxOrNull() ?: throw Exception()

    return minOfTime to maxOfTime
}

fun main() = with(Scanner(System.`in`)) {
    val numberOfCase = nextInt()
    for (i in 0 until numberOfCase) {
        val l = nextInt()
        val n = nextInt()

        val ants = mutableListOf<Int>()
        for (j in 0 until n) {
            ants.add(nextInt())
        }

        val (min, max) = getMinAndMaxTime(ants, l)
        println("$min $max")
    }
}