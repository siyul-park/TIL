import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val size = 3

    val p = mutableListOf<Long>()
    for (i in 0 until size) {
        p.add(nextLong())
    }
    val x = mutableListOf<Long>()
    for (i in 0 until size) {
        x.add(nextLong())
    }

    val params = p.mapIndexed { i, value -> value to x[i] }

    val mul = p.reduce { acc, l -> acc * l }
    for (n in 1 .. mul) {
        if (params.all { (p, x) -> n % p == x }) {
            println(n)
            return@with
        }
    }

    println(-1)
}