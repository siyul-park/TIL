import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val n = nextInt()
    for (i in 0 until n) {
        val k = nextInt()
        for (j in 0 until k) {
            print("=")
        }
        println()
    }
}