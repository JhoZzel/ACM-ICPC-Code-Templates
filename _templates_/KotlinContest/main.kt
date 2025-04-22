fun solve() {
    println("hola")
}

fun main() {
    var t = readInt()
    repeat(t) {
        solve()
    }
}

fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readLong() = readLn().toLong()
fun readDouble() = readLn().toDouble()
fun readStrings() = readLn().split(" ")
fun readInts() = readStrings().map { it.toInt() }
fun readLongs() = readStrings().map { it.toLong() }
fun readDoubles() = readStrings().map { it.toDouble() }
