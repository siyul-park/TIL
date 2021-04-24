import java.lang.Integer.min
import java.util.Scanner

fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val S = nextInt()
    val numbers = Array(N) { 0 }
    for (i in 0 until N) {
        numbers[i] = nextInt()
    }

    var result = Int.MAX_VALUE
    var sum = numbers[0]

    var low = 0
    var hight = 0
    while (hight in low until numbers.size) {
        when {
            sum < S -> {
                ++hight
                sum += if (hight < numbers.size) numbers[hight] else 0
            }
            sum == S -> {
                result = min(result, hight - low + 1)
                ++hight
                sum += if (hight < numbers.size) numbers[hight] else 0
            }
            sum > S -> {
                result = min(result, hight - low + 1)
                sum -= numbers[low++]
            }
        }
    }

    println(if (result == Int.MAX_VALUE) {
        0
    } else {
        result
    })
}