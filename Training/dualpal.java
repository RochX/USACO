/*
 ID: 
 PROG: dualpal
 LANG: JAVA
 */
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   6 November 2018
//PROBLEM ID    :   USACO Dual Palindromes
//DESCRIPTION   :   Finds all numbers greater than a certain number S that are palindromes in 2 or more in the number bases 2-10
//SOURCES/HELP  :   
import java.io.*;
import java.lang.*;
import java.util.StringTokenizer;
class dualpal
{
  //main function
  public static void main(String[] args) throws IOException
  {
    //file input
    BufferedReader in = new BufferedReader(new FileReader("dualpal.in"));
    StringTokenizer tokenizer = new StringTokenizer(in.readLine());

    //file output
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("dualpal.out")));

    //declare variables
    int numsNeeded, startNum, currentNum, basesCorrect;

    //input and initialize variables
    numsNeeded = Integer.parseInt(tokenizer.nextToken());
    startNum = Integer.parseInt(tokenizer.nextToken());
    currentNum = startNum+1;

    //System.out.println(numsNeeded + " " + startNum);

    //loop until enough numbers are found
    while (numsNeeded > 0)
    {
      //initialize variable
      basesCorrect = 0;

      //loop through all bases 2-10
      for (int base = 2; base <= 10; base++)
      {
        //check if the number in the base is a palindrome
        if (palChecker(baseConvert(currentNum, base)))
        {
          basesCorrect++;
        }

        //case when the number is a palindrome in 2 or more bases
        if (basesCorrect == 2)
        {
          //decrement the amount of numbers needed and output
          numsNeeded--;
          out.println(currentNum);
          break;
        }
      }

      //move to next number
      currentNum++;
    }

    //exit program
    in.close();
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