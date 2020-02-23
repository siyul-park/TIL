import java.util.*

fun main(args: Array<String>) = with(Scanner(System.`in`)) {
    val A = nextInt();
    val B = nextInt();
    val V = nextInt();

    println(Math.ceil((V - B).toDouble()/(A - B).toDouble()).toInt())
}