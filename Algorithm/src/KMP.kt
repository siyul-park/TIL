fun getPartialMatch(source: String): List<Int> {
    val partialMatch: MutableList<Int> = MutableList(source.length) { 0 }

    var begin = 1
    var matched = 0
    while (begin + matched < source.length) {
        if (source[begin + matched] == source[matched]) {
            matched++
            partialMatch[begin + matched - 1] = matched
        } else {
            if (matched == 0) {
                begin++
            } else {
                begin += matched - partialMatch[matched - 1]
                matched = partialMatch[matched - 1]
            }
        }
    }

    return partialMatch
}

fun kmp(source: String, target: String): List<Int> {
    val result = mutableListOf<Int>()
    val partialMatch = getPartialMatch(target)

    var matched = 0
    for (i in source.indices) {
        while (matched > 0 && target[i] != source[matched]) {
            matched = partialMatch[matched - 1]
        }

        if (source[i] == target[matched]) {
            matched++
            if (matched == target.length) {
                result.add(i - target.length + 1)
                matched = partialMatch[matched - 1]
            }
        }
    }

    return result
}

fun gcd(m: Long, n: Long): Long {
    if (n == 0L) {
        return m
    }

    return gcd(n, m % n)
}

fun lcm(m: Long, n: Long): Long {
    return m * n / gcd(m, n)
}