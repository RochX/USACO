/*
 ID: 
 PROG: palsquare
 LANG: JAVA
 */
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   6 November 2018
//PROBLEM ID    :   USACO Palindromic Squares
//DESCRIPTION   :   Finds all base B numbers 1-300 base 10 that are palindromes.
//SOURCES/HELP  :   
import java.io.*;
import java.lang.*;
class palsquare
{
  //main function
  public static void main(String[] args) throws IOException
  {
    //file input
    BufferedReader in = new BufferedReader(new FileReader("palsquare.in"));

    //file output
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("palsquare.out")));

    //declare and read in variables
    int base = Integer.parseInt(in.readLine()), square;

    //loop for integers 1-300
    for (int num = 1; num <= 300; num++)
    {
      //generate the square of the integer
      square = num*num;

      //check if the square in the base is a palindrome
      if (palChecker(baseConvert(square,base)))
      {
        //output with letters being uppercase
        out.println(baseConvert(num,base) + " " + baseConvert(square,base));
      }
      
    }
    //exit program
    out.close();
    return;
  }
  
  //convert a base 10 number to any base 2-36
  public static String baseConvert(int dec, int base)
  {
    //declare string of values to use
    final String SYMBOLS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    String result = "";

    while (dec > 0)
    {
      //add the next digit
      result = SYMBOLS.charAt(dec%base) + result;

      //divide the base 10 number by the current base 
      dec /= base;
    }
    
    //return the converted number
    return result;
  }
  
  //function to check if a string is a palindrome
  public static boolean palChecker(String palindrome)
  {
    for (int i = 0; i < palindrome.length()/2; i++)
    {
      if (palindrome.charAt(i) != palindrome.charAt(palindrome.length()-i-1))
      {
        return false;
      }
    }
    return true;
  }
}