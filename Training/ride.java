/*
 ID: 
 PROG: ride
 LANG: JAVA
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   6 September 2018
//PROBLEM ID    :   USACO Your Ride Is Here
//DESCRIPTION   :   Program that takes the ASCII values of characters of two strings, calculates a value for each and verifies if they are equal.
//SOURCES/HELP  :   Houtrouw
import java.io.*;
public class ride
{
  public static void main (String[] args) throws IOException
  {
    //opening files for input and output
    RandomAccessFile in = new RandomAccessFile ("ride.in", "r");
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ride.out")));

    //declares two strings--reads and assigns them from the input file
    String cometName = in.readLine();
    String groupName = in.readLine();

    //declares and initializes variables for storing calculations
    int cometNum = 1, groupNum = 1;

    //declares and initializes two constant variables
    final int ASCII_OFFSET_UPPERCASE = 64, MOD_VALUE = 47;

    //translates letters to ASCII code
    for (int k = 0; k < cometName.length(); k++)
    {
      cometNum *= cometName.charAt(k) - ASCII_OFFSET_UPPERCASE;
      cometNum %= MOD_VALUE;
    }
    for (int k = 0; k < groupName.length(); k++)
    {
      groupNum *= groupName.charAt(k) - ASCII_OFFSET_UPPERCASE;
      groupNum %= MOD_VALUE;
    }

    //checks if group and comet numbers are equal
    if (groupNum == cometNum)
      out.println("GO");
    else
      out.print("STAY\n");

    //ensures program ends properly
    out.close();
    System.exit(0);
    
  }
}
