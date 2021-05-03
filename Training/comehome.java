/*
ID: xavierw1
PROG: comehome
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 2-3-20
//PROBLEM ID    : USACO Bessie Come Home
//DESCRIPTION   : Finds the first cow to come to the barn
//SOURCES/HELP  :
import java.io.*;
import java.util.*;
public class comehome
{
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        BufferedReader in = new BufferedReader(new FileReader("comehome.in"));
        PrintWriter out = new PrintWriter(new FileWriter("comehome.out"));
        int numPaths = Integer.parseInt(in.readLine()), v1, v2, weight;
        String[] inp;
        String cowPresent = "[A-Y]", lowerCase = "[a-z]";
        int[] dist;

        //graph --> adjMatrix --> 52 x 52, a = 0, b = 1, ... z = 25, A = 26, B = 27, ... , Z = 51
        int[][] graph = new int[52][52];

        //true if a cow is starting at that barn
        boolean[] cow = new boolean[52];

        //input
        for (int a = 0; a < numPaths; a++)
        {
            //0 = v1, 1 = v2, 2 = weight
            inp = in.readLine().split("\\s+");

            //input
            if (inp[0].matches(lowerCase))
                v1 = inp[0].charAt(0) - 'a';
            else
                v1 = inp[0].charAt(0) - 'A' + 26;

            if (inp[1].matches(lowerCase))
                v2 = inp[1].charAt(0) - 'a';
            else
                v2 = inp[1].charAt(0) - 'A' + 26;
            weight = Integer.parseInt(inp[2]);

            //put the best path in graph and see if a cow is at that barn
            if (v1 != v2)
            {
                //is the cow at the barn
                if (inp[0].matches(cowPresent))
                    cow[v1] = true;
                if (inp[1].matches(cowPresent))
                    cow[v2] = true;

                //initial weight
                if (graph[v1][v2] == 0)
                {
                    graph[v1][v2] = weight;
                    graph[v2][v1] = weight;
                }
                //find best weight
                else
                {
                    graph[v1][v2] = Math.min(graph[v1][v2], weight);
                    graph[v2][v1] = Math.min(graph[v2][v1], weight);
                }
            }
        }

        //dijkstra algorithm to find best distances from the barn
        dist = dijkstra(graph,graph[0].length-1);

        //get minimum distance from the shortest distances from the barn
        int minDist = Integer.MAX_VALUE;
        char best = 'A';
        for (int i = 0; i < dist.length; i++)
        {
            if (cow[i])
            {
                if (dist[i] < minDist)
                {
                    minDist = dist[i];
                    if (i < 26)
                        best = (char) ('a' + i);
                    else
                        best = (char) ('A' + i - 26);
                }
            }
        }

        //output and exit
        out.println(best + " " + minDist);
        out.close();
        in.close();
    }

    //returns shortest distance array
    public static int[] dijkstra(int[][] graph, int src)
    {
        //vars and objects
        final int NO_EDGE_NUM = 0;
        int numVertices = graph[0].length;
        int[] dist = new int[numVertices];
        boolean[] visited = new boolean[numVertices];
        int[] parent = new int[numVertices];
        int currVertex;

        //initialize
        Arrays.fill(dist, Integer.MAX_VALUE);
        Arrays.fill(parent, -1);
        dist[src] = 0;
        parent[src] = -1;

        //loop through all vertices
        for (int a = 0; a < numVertices; a++)
        {
            //find vertex with min distance to source and not visited
            currVertex = 0;
            int minDist = Integer.MAX_VALUE;
            for (int i = 0; i < numVertices; i++)
            {
                if (dist[i] < minDist && !visited[i])
                {
                    minDist = dist[i];
                    currVertex = i;
                }
            }
            visited[currVertex] = true;

            //update neighbors of currVertex
            for (int i = 0; i < numVertices; i++)
            {
                //is the distance better than what it previously is?
                int weight = graph[currVertex][i];
                if (dist[currVertex] + weight < dist[i] && weight != NO_EDGE_NUM)
                {
                    //update
                    dist[i] = dist[currVertex] + weight;
                    parent[i] = currVertex;
                }
            }
        }

        //return dist array
        return dist;
    }

}
