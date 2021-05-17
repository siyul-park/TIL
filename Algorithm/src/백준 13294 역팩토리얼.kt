import java.math.BigInteger
import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val nFactorial = nextBigInteger()

    var currnet = BigInteger.ZERO
    var i = BigInteger.ZERO
    while (currnet < nFactorial) {
        i = i.add(BigInteger.ONE)
        if (currnet == BigInteger.ZERO) {
            currnet = BigInteger.ONE
        }
        currnet = currnet.multiply(i)
    }

    println(i)
}