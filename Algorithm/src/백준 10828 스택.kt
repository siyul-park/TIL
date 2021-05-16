import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val stack = Stack<Int>()
    val output = StringBuilder()

    val N = nextInt()
    for (i in 0 until N) {
        val operator = next()
        when (operator) {
            "push" -> {
                val X = nextInt()
                stack.push(X)
            }
            "pop" -> {
                output.append("${if (stack.empty()) -1 else stack.pop()}\n")
            }
            "size" -> {
                output.append("${stack.size}\n")
            }
            "empty" -> {
                output.append("${if (stack.empty()) 1 else 0}\n")
            }
            "top" -> {
                output.append("${if (stack.empty()) -1 else stack.peek()}\n")
            }
        }
    }

    print(output)
}