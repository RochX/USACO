//Xavier Silva
//AdvCS
//USACO Round 3 19-20
//P1 Timeline
import java.io.*;
import java.util.*;
public class timeline
{
    public static void main(String[] args) throws IOException
    {
        Scanner in = new Scanner(new File("timeline.in"));
        PrintWriter out = new PrintWriter(new FileWriter("timeline.out"));
        int numSessions, maxDays, numTriplets;
        numSessions = in.nextInt();
        maxDays = in.nextInt();
        numTriplets = in.nextInt();

        timePair[] minDay = new timePair[numSessions];
        for (int i = 0; i < minDay.length; i++) {
            minDay[i] = new timePair(in.nextInt(),i);
        }

        int[][] dist = new int[numSessions][numSessions];
        for (int i = 0; i < numTriplets; i++)
        {
            int start = in.nextInt()-1;
            int end = in.nextInt()-1;
            int distInp = in.nextInt();
            dist[start][end] = distInp;
        }

        //starting session
        for (int i = 0; i < dist.length; i++)
        {
            //ending session
            for (int j = 0; j < dist[0].length; j++)
            {
                if (dist[i][j] != 0 && minDay[j].minDay < minDay[i].minDay + dist[i][j])
                {
                    minDay[j].minDay = minDay[i].minDay + dist[i][j];
                }
            }
        }

        for (int i = 0; i < minDay.length; i++)
        {
            if (minDay[i].minDay < maxDays)
                out.println(minDay[i].minDay);
            else
                out.println(maxDays);
        }
        in.close();
        out.close();
    }
}

class timePair
{
    int minDay;
    int session;
    public timePair(int d, int s)
    {
        minDay = d;
        session = s;
    }
}
