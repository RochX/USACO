/*
 ID: 
 PROG: namenum
 LANG: JAVA
 */
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   12 November 2018
//PROBLEM ID    :   USACO Name That Number
//DESCRIPTION   :   Finds suitable names for cows with serial numbers.
//SOURCES/HELP  : 
import java.io.*;
import java.util.*;  
class namenum
{
  public static void main(String[] args) throws IOException
  {
    //file IO
    Scanner in = new Scanner(new File("namenum.in"));
    Scanner dictIn = new Scanner(new File("dict.txt"));
    PrintWriter out = new PrintWriter(new File("namenum.out"));

    //declare and initialize variables
    String code = in.next();
    String input, tempCode;
    boolean outputted = false;

    //loop through the dictionary file
    while (dictIn.hasNext())
    {
      //input
      input = dictIn.next();
      tempCode = "";

      //converts dictionary to code
      for (int i = 0; i < input.length(); i++)
      {
        //switch to determine what digit to add
        switch(input.charAt(i))
        {
          case 'A': case 'B': case 'C':
            tempCode += "2";
            break;
          case 'D': case 'E': case 'F':
            tempCode += "3";
            break;
          case 'G': case 'H': case 'I':
            tempCode += "4";
            break;
          case 'J': case 'K': case 'L':
            tempCode += "5";
            break;
          case 'M': case 'N': case 'O':
            tempCode += "6";
            break;
          case 'P': case 'R': case 'S':
            tempCode += "7";
            break;
          case 'T': case 'U': case 'V':
            tempCode += "8";
            break;
          case 'W': case 'X': case 'Y':
            tempCode += "9";
            break;
        }
      }

      //test if the dictionary code equals the given code
      if (tempCode.equals(code))
      {
        //output
        outputted = true;
        out.println(input);
      }
    }

    //case when there is nothing outputted
    if (!outputted)
      out.println("NONE");

    //exit program
    in.close();
    dictIn.close();
    out.close();
  }
}