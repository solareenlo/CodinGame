import math._
import scala.util._
import scala.io.StdIn._
import scala.collection.immutable.ListMap

/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/
object Player extends App {

  // game loop
  while(true) {
    var heightOfMountain: Map[Int, Int] = Map.empty
    for(i: Int <- 0 until 8) {
      val mountainH = readLine.toInt // represents the height of one mountain.
      heightOfMountain += (i -> mountainH)
    }

    // Write an action using println
    // To debug: Console.err.println("Debug messages...")
    val sortedMap = ListMap(heightOfMountain.toSeq.sortWith(_._2 > _._2):_*).keys
    println(sortedMap.head)
  }
}
