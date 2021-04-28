import java.util.*

class HashCodeSet<T>(set: MutableSet<T>, private val code: Int): MutableSet<T> by set {
    override fun hashCode(): Int {
        return code
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as HashCodeSet<*>

        if (code != other.code) return false

        return true
    }
}

fun getMaxLength(dices: MutableSet<Set<Int>>): Int {
    fun getMaxLength(dices: MutableSet<Set<Int>>, current: Int): Int {
        if (dices.isEmpty()) {
            return 0
        }
        val existed = dices.filter { it.contains(current + 1) }

        return existed.map { dice ->
            dices.remove(dice)
            (getMaxLength(dices, current + 1) + 1)
                .also { dices.add(dice) }
        }.maxOrNull() ?: 0
    }

    val result = dices.map { dice ->
        val free = dices.filter { it !== dice }.toHashSet()
        dice.map { getMaxLength(free, it) + 1 }.maxOrNull()
    }

    return result
        .filterNotNull()
        .maxOrNull() ?: 1
}

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (t in 1..T) {
        val N = nextInt()

        val dices: MutableSet<Set<Int>> = HashSet<Set<Int>>()
        for (i in 0 until N) {
            val dice = HashCodeSet(HashSet<Int>(), i)
            for (j in 0 until 6) {
                dice.add(nextInt())
            }
            dices.add(dice)
        }

        println("Case #${t}: ${getMaxLength(dices)}")
    }
}