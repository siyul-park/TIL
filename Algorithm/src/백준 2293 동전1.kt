import java.util.*

fun numberOfCase(values: List<Int>, total: Int): Long {
    var preWindow = Array(total + 1) { 0L }
    var currentWindow = Array(total + 1) { 0L }


    for (i in values.indices) {
        val current = values[i]

        for (subTotal in 0..total) {
            if (i == 0) {
                if ((subTotal % current) == 0) {
                    currentWindow[subTotal] = 1L
                } else {
                    currentWindow[subTotal] = 0L
                }
            } else {
                var preTotal = subTotal
                var sum = 0L
                while (preTotal >= 0) {
                    sum += preWindow[preTotal]
                    preTotal -= current
                }

                currentWindow[subTotal] = sum
            }
        }

        val tmp = preWindow
        preWindow = currentWindow
        currentWindow = tmp
    }

    return preWindow[total]
}

fun main() = with(Scanner(System.`in`)) {
    val n = nextInt()
    val k = nextInt()

    val values = mutableListOf<Int>()
    for (i in 0 until n) {
        values.add(nextInt())
    }

    println(numberOfCase(values, k))
}