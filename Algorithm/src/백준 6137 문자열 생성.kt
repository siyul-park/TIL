import java.util.*
import kotlin.collections.ArrayDeque
import kotlin.math.min

fun compare(a: List<String>, b: List<String>): Int {
    if (a === b) {
        return 0
    }

    val size = min(a.size, b.size)
    for (i in 0 until size) {
        if (a[i] != b[i]) {
            return a[i].compareTo(b[i])
        }
    }

    return 0
}

fun convert(source: ArrayDeque<String>): StringBuilder {
    if (source.isEmpty()) {
        return StringBuilder()
    }

    return if (compare(source, source.reversed()) < 0) {
        val first = source.removeFirst()
        val result = convert(source).append(first)
        source.addFirst(first)

        result
    } else {
        val last = source.removeLast()
        val result = convert(source).append(last)
        source.addLast(last)

        result
    }
}

fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val S = ArrayDeque<String>()
    for (i in 0 until N) {
        S.add(next())
    }

    val result = convert(S).reversed()
    for (i in result.indices) {
        print(result[i])
        if (((i + 1) % 80) == 0) {
            println()
        }
    }
    if (result.length % 80 != 0) {
        println()
    }
}