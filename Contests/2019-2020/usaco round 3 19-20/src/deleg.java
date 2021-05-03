//Xavier Silva
//AdvCS
//USACO Round 3 19-20
//P3 Delegations
import java.io.*;
import java.util.*;
public class deleg
{
    public static void main(String[] args) throws IOException
    {
        Scanner in = new Scanner(new File("deleg.in"));
        PrintWriter out = new PrintWriter(new FileWriter("deleg.out"));

        int len = in.nextInt();
        StringBuilder output = new StringBuilder();

        for (int i = 1; i < len; i++)
        {
            if (i <= 3)
                output.append("1");
            else
                output.append("0");
        }
        out.println(output);

        in.close();
        out.close();
    }
}