import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val M = nextInt()
    val numbers = Array(N) { 0 }
    for (i in 0 until N) {
        numbers[i] = nextInt()
    }

    var result = 0
    var sum = numbers[0]

    var low = 0
    var hight = 0
    while (hight in low until numbers.size) {
        when {
            sum < M -> {
                hight++
                sum += if (hight < numbers.size) numbers[hight] else 0
            }
            sum >= M -> {
                if (sum == M) {
                    result++
                }

                if (low == hight) {
                    hight++
                    sum += if (hight < numbers.size) numbers[hight] else 0
                }
                sum -= numbers[low++]
            }
        }
    }

    println(result)
}