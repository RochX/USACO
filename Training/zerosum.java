/*
 ID: 
 PROG: zerosum
 LANG: JAVA
 */
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   8 November 2018
//PROBLEM ID    :   USACO Zero Sum
//DESCRIPTION   :   Given the digits 1-N, insert '+'s, '-'s, or ' 's in a way so that when the expression is evaluated it equals zero.
//SOURCES/HELP  :   
import java.util.*;
import java.io.*;
class zerosum
{
  public static void main(String[] args) throws IOException
  {
    //file IO
    BufferedReader in = new BufferedReader(new FileReader("zerosum.in"));
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("zerosum.out")));

    //declare and initialize variables
    int nums = Integer.parseInt(in.readLine());
    int numCombos = (int)Math.pow(3, nums-1);
    String start = "123456789".substring(0,nums);
    ArrayList<String> combos = new ArrayList<String>();

    //loop through all possible combos
    for (int i = 0; i < numCombos; i++)
    {
      //generate a combination
      String temp = Integer.toString(i,3);

      //add leading zeroes
      while (temp.length() < nums)
        temp = "0" + temp;

      //declare and initialize the expression string
      StringBuilder expression = new StringBuilder(start);

      //loop through the string to figure out where to put symbols
      for (int j = 0; j < temp.length(); j++)
      {
        switch(temp.charAt(temp.length()-1-j))
        {
          //put a blank space in
          case '0':
            expression.insert(j*2+1,' ');
            break;
          //put plus sign in
          case '1':
            expression.insert(j*2+1,'-');
            break;
          //put minus sign in
          case '2':
            expression.insert(j*2+1,'+');
            break;
        }
      }

      //check if the combo is valid
      String toEval = expression.toString().replaceAll("[\\s]+", "");
      if (eval(toEval) == 0)
      {
        //add it to the list of valid solutions
        combos.add(expression.toString());
      }
    }

    //sort the solutions and output
    Collections.sort(combos);
    for (int i = 0; i < combos.size(); i++)
    {
      String output = combos.get(i);
      out.println(output.substring(0,output.length()-1));
    }

    //exit program
    in.close();
    out.close();
  }

  //evaluate a given expression (which is a string)
  public static int eval(String expression)
  {
    //declare and initialize variables
    int value = 0;
    StringTokenizer numbers = new StringTokenizer(expression, "+-");
    StringTokenizer operators = new StringTokenizer(expression, "0123456789");

    //add the first number
    value += Integer.parseInt(numbers.nextToken());

    //loop to apply the operators
    while (operators.hasMoreTokens())
    {
      String op = operators.nextToken();
      int num = Integer.parseInt(numbers.nextToken());
      if (op.equals("+"))
        value += num;
      if (op.equals("-"))
        value -= num;
    }

    //return the final value of the expression
    return value;
  }
}