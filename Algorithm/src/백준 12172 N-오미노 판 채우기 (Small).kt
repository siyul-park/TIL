import java.lang.Integer.max
import java.lang.Integer.min
import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (i in 1 .. T) {
        val X = nextInt()
        val R = nextInt()
        val C = nextInt()

        var result = true
        if ((R * C) % X != 0) {
            result = false
        } else if (X >= 7) {
            result = false
        } else if ((X + 1) / 2 > min(R, C)){
            result = false
        } else if (X == 4 && min(R, C) == 2) {
            result = false
        } else if (X == 5 && min(R, C) == 3 && max(R, C) <= 5) {
            result = false
        } else if (X == 6 && min(R, C) == 3) {
            result = false
        }

        if (result) {
            println("Case #${i}: GABRIEL")
        } else {
            println("Case #${i}: RICHARD")
        }
    }
}