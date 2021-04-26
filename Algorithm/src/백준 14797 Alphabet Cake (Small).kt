import java.lang.StringBuilder
import java.util.*

typealias Grid = MutableList<MutableList<Char?>>

fun createGrid(row: Int, col: Int): Grid {
    return MutableList(row) { MutableList(col) { null } }
}

fun solve(grid: Grid) {
    val row = grid.size
    val col = grid[0].size

    for (i in 0 until row) {
        var pre: Char? = null
        for (j in 0 until col) {
            if (grid[i][j] != null) {
                pre = grid[i][j]
                continue
            }

            if (grid[i][j] == null) {
                grid[i][j] = pre
            }
        }
    }

    for (i in 0 until row) {
        var pre: Char? = null
        for (j in 0 until col) {
            if (grid[i][col - j -1] != null) {
                pre = grid[i][col - j -1]
                continue
            }

            if (grid[i][col - j -1] == null) {
                grid[i][col - j -1] = pre
            }
        }
    }

    for (i in 0 until col) {
        var pre: Char? = null
        for (j in 0 until row) {
            if (grid[j][i] != null) {
                pre = grid[j][i]
                continue
            }

            if (grid[j][i] == null) {
                grid[j][i] = pre
            }
        }
    }

    for (i in 0 until col) {
        var pre: Char? = null
        for (j in 0 until row) {
            if (grid[row - j - 1][i] != null) {
                pre = grid[row - j - 1][i]
                continue
            }

            if (grid[row - j - 1][i] == null) {
                grid[row - j - 1][i] = pre
            }
        }
    }
}

fun main() = with(Scanner(System.`in`)) {
    val T = nextInt()
    for (i in 0 until T) {
        val R = nextInt()
        val C = nextInt()

        val grid = createGrid(R, C)
        for (r in 0 until R) {
            val row = next()
            for (c in 0 until C) {
                if (row[c] != '?') {
                    grid[r][c] = row[c]
                }
            }
        }

        solve(grid)

        println("Case #${i + 1}:")
        grid.forEach { row ->
            println(row.fold(StringBuilder()) { acc, char -> acc.append(char) }.toString())
        }
    }
}