//Xavier Silva
//AdvCS
//USACO 19-20 Round 2
//P2 Farmer John Solves 3SUM
import java.io.*;
import java.util.*;
public class ThreeSum {
    public static void main(String[] args) throws IOException
    {
        Scanner in = new Scanner(new File("threesum.in"));
        PrintWriter out = new PrintWriter(new FileWriter("threesum.out"));

        int arraySize = in.nextInt(), numQueries = in.nextInt();
        long[] array = new long[arraySize];

        for (int i = 0; i < arraySize; i++)
        {
            array[i] = in.nextLong();
        }
        int count = 0;
        for (int a = 0; a < numQueries; a++) {
            count = 0;
            int qStart = in.nextInt() - 1, qEnd = in.nextInt() - 1;

            for (int i = qStart; i <= qEnd-2; i++) {
                for (int j = i + 1; j <= qEnd-1; j++) {
                    for (int k = j + 1; k <= qEnd; k++) {
                        if (array[i]+array[j]+array[k] == 0)
                            count++;
                    }
                }
            }
            out.println(count);
        }
        out.close();
        in.close();
    }
}