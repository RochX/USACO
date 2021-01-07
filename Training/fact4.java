/*
 ID: 
 PROG: fact4
 LANG: JAVA
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   23 October 2018
//PROBLEM ID    :   USACO Factorials
//DESCRIPTION   :   Given a number N, find the right most digit of N!.
//SOURCES/HELP  :   
import java.util.*;
import java.io.*;
class fact4 
{
  public static void main(String[] args) throws IOException
  {
    //file input
    BufferedReader in = new BufferedReader(new FileReader("fact4.in"));

    //file output
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fact4.out")));

    //declare and input variables
    int factorial = Integer.parseInt(in.readLine()), prod = 1;

    //loop through each natural number 1-N
    for (int i = 1; i <= factorial; i++)
    {
      //multiply the value by the current natural number (factorial)
      prod *= i;

      //make the ones place a non-zero digit
      while (prod % 10 == 0)
      {
        prod /= 10;
      }
	  
      //chop off unneeded values to the left
      prod %= 10000;
    }
    //output the first non-zero digit of the factorial
    out.println(prod % 10);

    //exit program
    in.close();
    out.close();
  }
}