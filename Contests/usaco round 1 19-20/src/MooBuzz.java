//Xavier Silva
//DM
//USACO 19-20 Round 1
//P1 MooBuzz
import java.io.*;
import java.util.*;
public class MooBuzz
{
    public static void main(String[] args) throws IOException
    {
        //declare and input
        Scanner in = new Scanner(new File("moobuzz.in"));
        PrintWriter out = new PrintWriter(new FileWriter("moobuzz.out"));
        int n = in.nextInt()-1;
        int[] num = {1,2,4,7,8,11,13,14};

        //the number and "moo" pattern is cyclical every 15, so just use division and mod to find the right number
        out.println((n/8)*15 + num[n%8]);

        //exit
        out.close();
        in.close();
    }
}
