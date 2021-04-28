import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (t in 1 .. T) {
        val D = nextInt()
        val N = nextInt()

        val horses = mutableListOf<Pair<Int, Int>>()
        for (i in 0 until N) {
            val K = nextInt()
            val S = nextInt()
            horses.add(K to S)
        }

        println("Case #${t}: ${D / (horses.map { (K, S) -> (D - K).toDouble() / S }.maxOrNull() ?: 1.0)}")
    }
}