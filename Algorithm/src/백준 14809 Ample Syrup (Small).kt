import java.lang.Long.max
import java.util.*

data class Cake(
    val round: Long,
    val height: Long
) {
    val sideWidth = round * 2 * height

    val topWidth = round * round
}

fun getMaxSurfaceArea(cakes: List<Cake>, amount: Int): Double {
    val sorted = cakes.sortedBy { it.sideWidth }.reversed()

    var value = 0L
    cakes.forEach { cake ->
        val other = sorted.filter { it !== cake && it.round <= cake.round }
        if (other.size < amount - 1) {
            return@forEach
        }

        var currnet = cake.sideWidth + cake.topWidth
        for (i in 0 until (amount - 1)) {
            currnet += other[i].sideWidth
        }

        value = max(value, currnet)
    }

    return value * Math.PI
}

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (case in 1..T) {
        val N = nextInt()
        val K = nextInt()

        val cakes = mutableListOf<Cake>()
        for (i in 0 until N) {
            val R = nextLong()
            val H = nextLong()
            cakes.add(Cake(R, H))
        }

        println("Case #${case}: ${getMaxSurfaceArea(cakes, K)}")
    }
}