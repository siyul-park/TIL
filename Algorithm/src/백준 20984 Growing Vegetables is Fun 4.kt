import java.util.*
import kotlin.collections.ArrayList

fun main() = with(Scanner(System.`in`)) {
    val N = nextInt()
    val A = ArrayList<Long>(N)

    for (i in 0 until N) {
        A.add(nextLong())
    }

    var startIndex = 0
    var endIndex = A.size - 1
    var count = 0L
    while (startIndex < endIndex) {
        if (A[startIndex] < A[startIndex + 1]) {
            startIndex++
        } else if (A[endIndex] < A[endIndex - 1]) {
            endIndex--
        } else {
            val diffOfStart = A[startIndex] - A[startIndex + 1] + 1
            val diffOfEnd = A[endIndex] - A[endIndex - 1] + 1

            if (diffOfStart <= diffOfEnd) {
                count += diffOfStart
                A[endIndex] -= diffOfStart

                startIndex++
            } else {
                count += diffOfEnd
                A[startIndex] -= diffOfEnd

                endIndex--
            }
        }
    }

    println(count)
}