import java.util.*
import kotlin.collections.ArrayList

fun main() = with(Scanner(System.`in`)) {
    val n = nextInt()
    val m = nextInt()

    val a = ArrayList<Int>(n)
    for (i in 0 until n) {
        a.add(nextInt())
    }

    val b = ArrayList<Int>(m)
    for (i in 0 until m) {
        b.add(nextInt())
    }

    a.sortDescending()
    b.sortDescending()

    val adjust = MutableList(a.size) { 0 }

    var current = a.size - 1
    b.forEachIndexed { i, numberOfBalloons ->
        if ((current + 1) < numberOfBalloons) {
            println("NIE")
            return@with
        }
        if ((current + 1) > numberOfBalloons) {
            val notAssignment = current - numberOfBalloons
            adjust[notAssignment]++
        }

        while (current > 0 && (a[current] + adjust[current] - i - 1) <= 0) {
            adjust[current - 1] += adjust[current]
            current--
        }
        if (current == 0 && i < b.size - 1) {
            println("NIE")
            return@with
        }
    }

    println("TAK")
}