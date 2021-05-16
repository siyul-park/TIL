import java.util.*
import kotlin.math.max

fun getMaxFoodValue(foods: List<Int>): Int {
    val cache = MutableList(foods.size) { -1 }

    fun solve(index: Int): Int {
        if (index >= foods.size) {
            return 0
        }

        if (cache[index] != -1) {
            return cache[index]
        }

        return max(foods[index] + solve(index + 2), solve(index + 1))
            .also { cache[index] = it }
    }

    return solve(0)
}

fun main() = with(Scanner(System.`in`)) {
    val K = nextInt()
    for (i in 1 .. K) {
        val n = nextInt()
        val foods = mutableListOf<Int>()
        for (j in 0 until n) {
            foods.add(nextInt())
        }

        println("Data Set ${i}:\n${getMaxFoodValue(foods)}\n")
    }
}