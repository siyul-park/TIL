import java.lang.Integer.min
import java.util.*

fun getMaxSameLength(s1: String, s2: String): Int {
    var current = 0
    val length = min(s1.length, s2.length)

    for (i in 0 until length) {
        if (s1[current] != s2[current]) {
            return current
        }
        current++
    }

    return current
}

fun canBeExistX(s: String, xSize: Int): Boolean {
    for (i in xSize until s.length) {
        if (s[i] != s[s.length + xSize - i - 1]) {
            return false
        }
    }

    return true
}

fun getMinPostfixOfPalindrome(a: String, b: String) {
    val maxSameLength = getMaxSameLength(a, b)

    for (i in 1 .. min(a.length, b.length)) {
        val xIsExistedInA = canBeExistX(a, i)
        val xIsExistedInB = canBeExistX(b, i)

        if (xIsExistedInA && xIsExistedInB) {
            if (i <= maxSameLength) {
                continue
            }

            val xForA = a.substring(0, i).reversed()
            val xForB = b.substring(0, i).reversed()

            println(if (xForA < xForB) xForA else xForB)
            return
        } else if (xIsExistedInA) {
            println(a.substring(0, i).reversed())
            return
        } else if (xIsExistedInB) {
            println(b.substring(0, i).reversed())
            return
        }
    }

    if (a.length < b.length) {
        var c = 'a'
        while (b[a.length] == c) {
            c++
        }

        println(c + a.reversed())
        return
    } else if (a.length > b.length) {
        var c = 'a'
        while (a[b.length] == c) {
            c++
        }

        println(c + b.reversed())
        return
    }

    println("No Solution.")
}

fun main() = with(Scanner(System.`in`)) {
    while (true) {
        try {
            val a = next()
            val b = next()

            getMinPostfixOfPalindrome(a, b)

            if (!hasNext()) {
                return@with
            }
        } catch (e: Exception) {
            return@with
        }
    }
}