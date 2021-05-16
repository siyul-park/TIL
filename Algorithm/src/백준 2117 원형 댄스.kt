import java.util.*
import kotlin.math.min

fun getSubSum(n: Int): Int {
    return n * (n - 1) / 2
}

fun getMinOfReverseCount(n: Int): Int {
    var current = Int.MAX_VALUE
    for (i in 0 .. n) {
        current = min(current, getSubSum(i) + getSubSum(n - i))
    }

    return current
}

fun main() = with(Scanner(System.`in`)) {
    val n = nextInt()
    println(getMinOfReverseCount(n))
}