import java.util.*

fun divideWordAndSort(word: String, start: Int, size: Int): String {
    if (size == 1) {
        return word.subSequence(start, word.length).reversed().toString()
    }

    var small: String? = null
    for (i in start until (word.length - (size - 1))) {
        val pre = word.subSequence(start, i + 1).reversed().toString()
        val next = divideWordAndSort(word, i + 1, size - 1)
        val current = pre + next

        if (small == null) {
            small = current
        }
        if (current < small) {
            small = current
        }
    }

    return small!!
}

fun main() = with(Scanner(System.`in`)) {
    val word = next()
    println(divideWordAndSort(word, 0, 3))
}