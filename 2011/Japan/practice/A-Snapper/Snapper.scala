object Snapper {
  def main (args: Array[String]) {
    scala.io.Source.fromInputStream(System.in).getLines.zipWithIndex.foreach {
      case (line: String, count: Int) => line.split(' ') match {
        case Array(n, k) =>
          execute(count, n.toInt, k.toInt)

        case _ =>
      }
    }
  }

  def execute(count: Int, n: Int, k: Int) {
    val state = Integer.toBinaryString(k)
    if (state.length >= n && state.takeRight(n).forall(!_.equals('0')))
      println("Case #" + count + ": ON")
    else
      println("Case #" + count + ": OFF")
  }
}
