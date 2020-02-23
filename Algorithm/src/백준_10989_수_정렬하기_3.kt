import java.util.*
import java.io.*

fun BufferedReader.nextInt() = Integer.parseInt(this.readLine())

fun main(args: Array<String>) {
    val inputBuffer = BufferedReader(InputStreamReader(System.`in`))

    val N = inputBuffer.nextInt()
    val counter = MutableList(10_000 + 1) { 0 }

    (0 until N).forEach { counter[inputBuffer.nextInt()] += 1 }

    inputBuffer.close()

    val outputBuffer = BufferedWriter(OutputStreamWriter(System.out))
    counter.forEachIndexed { i, count -> (0 until count).forEach { outputBuffer.write("$i\n") } }

    outputBuffer.flush();
    outputBuffer.close();
}