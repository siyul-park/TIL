import java.util.*

fun getNumberOfIslands(sequence: List<Int>): Int {
    var pre = 0
    var count = 0

    sequence.forEach {
        if (it < pre) {
            count++
        }
        pre = it
    }

    return count
}

fun main() = with(Scanner(System.`in`)) {
    val P = nextInt()
    for (i in 1 .. P) {
        val K = nextInt()
        val sequence = mutableListOf<Int>()
        for (j in 0 until 15) {
            sequence.add(nextInt())
        }

        println("$K ${getNumberOfIslands(sequence)}")
    }
}