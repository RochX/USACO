/*
ID: xavierw1
PROG: prefix
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 2-4-20
//PROBLEM ID    : USACO Longest Prefix
//DESCRIPTION   : Find the length of the longest prefix in a given string with a list of primitives
//SOURCES/HELP  :
import java.io.*;
import java.util.*;
public class prefix
{
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        BufferedReader in = new BufferedReader(new FileReader("prefix.in"));
        PrintWriter out = new PrintWriter(new FileWriter("prefix.out"));
        ArrayList<String> primitives = new ArrayList<>();
        String[] input;
        StringBuilder sequence = new StringBuilder();
        String inp;

        //input primitives
        while (true)
        {
            input = in.readLine().split("\\s");
            if (input[0].equals("."))
                break;

            primitives.addAll(Arrays.asList(input));
        }

        //input sequence
        inp = in.readLine();
        while(inp != null)
        {
            sequence.append(inp);
            inp = in.readLine();
        }

        //initial condition
        boolean[] valid = new boolean[sequence.length()+2];
        valid[0] = true;
        int longest = 0;

        //DP algorithm: valid prefix = shorter valid prefix + primitive
        for (int i = 0; i < sequence.length(); i++)
        {
            //see if a prefix of given length is valid
            if (valid[i])
            {
                //check all primitives
                for (String prim : primitives)
                {
                    //see if shorter prefix + primitive creates a valid prefix
                    int len = prim.length();
                    if (i+len <= sequence.length() && prim.equals(sequence.substring(i,i+len)))
                    {
                        valid[i+len] = true;
                        longest = Math.max(longest,i+len);
                    }
                }
            }
        }

        //output and exit
        out.println(longest);
        in.close();
        out.close();
    }
}
