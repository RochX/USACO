/*
 ID: 
 PROG: beads
 LANG: JAVA
 */
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   28 October 2018
//PROBLEM ID    :   USACO Broken Necklace
//DESCRIPTION   :   Finds the best spot to cut a necklace to obtain the most beads
//SOURCES/HELP  :   
import java.util.*;
import java.io.*;
class beads
{
  public static void main(String[] args) throws IOException
  {
    //file input/output
    BufferedReader in = new BufferedReader(new FileReader("beads.in"));
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("beads.out")));

    //declare, initialize, and input variables
    char left, right;
    int maxBeads = 0, tempBeads;
    int size = Integer.parseInt(in.readLine());
    String necklace = in.readLine();
    //add extra copy onto the necklace
    necklace += necklace;

    for (int i = 0; i < necklace.length()/2; i++)
    {
      //check all positions
      left = necklace.charAt(i);
      right = necklace.charAt(i+1);

      //initialize
      tempBeads = 0;

      //check left
      for (int j = i; j >= 0; j--)
      {
        //find the color if it was first set to white
        if (necklace.charAt(j) != 'w' && left == 'w')
          left = necklace.charAt(j);

        //check if the current bead is the color or white
        if (necklace.charAt(j) == left || necklace.charAt(j) == 'w')
          tempBeads++;
        else
          break;
      }

      //check right
      for (int j = i+1; j < necklace.length(); j++)
      {
        //find the color if it was first set to white
        if (necklace.charAt(j) != 'w' && right == 'w')
          right = necklace.charAt(j);

        //check if the current bead is the color or white
        if (necklace.charAt(j) == right || necklace.charAt(j) == 'w')
          tempBeads++;
        else
          break;
      }

      //set new largest beads collected
      maxBeads = Math.max(maxBeads, tempBeads);
    }

    //output the beads collected without over counting
    out.println(Math.min(maxBeads, size));
	
	//exit program
    in.close();
    out.close();
  }
}