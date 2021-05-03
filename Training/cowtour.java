/*
ID: xavierw1
PROG: cowtour
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 2-4-20
//PROBLEM ID    : USACO Cow Tours
//DESCRIPTION   : Finds the smallest diameter of two pastures
//SOURCES/HELP  :
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;
public class cowtour
{
    static final double TOL = 0.0000001, INF = 999999999;
    static int numNodes;
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        Scanner in = new Scanner(new File("cowtour.in"));
        PrintWriter out = new PrintWriter(new FileWriter("cowtour.out"));
        numNodes = in.nextInt();
        int[] x = new int[numNodes], y = new int[numNodes];
        double[][] graph = new double[numNodes][numNodes], pointDist = new double[numNodes][numNodes];
        double[][] shortestDist;
        String inp;
        double bestDiameter = Double.MAX_VALUE;

        //input coordinates
        for (int i = 0; i < numNodes; i++)
        {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }

        //input graph
        for (int i = 0; i < numNodes; i++)
        {
            inp = in.next();
            for (int j = 0; j < numNodes; j++)
            {
                pointDist[i][j] = distance(x[i],y[i],x[j],y[j]);
                if (inp.charAt(j) == '1')
                {
                    graph[i][j] = pointDist[i][j];
                    graph[j][i] = graph[i][j];
                }
                else
                {
                    graph[i][j] = INF;
                    graph[j][i] = INF;
                }
            }
        }

        //find the shortest distance between all pairs of nodes
        shortestDist = floydWarshall(graph);


        //field[i] = the field that node i is in
        int[] field = new int[numNodes];
        Arrays.fill(field,-1);
        int marker = 0;

        //marks the fields
        for (int i = 0; i < numNodes; i++)
        {
            if (field[i] == -1)
            {
                field(field, i, new boolean[numNodes], marker, graph);
                marker++;
            }
        }

        //calculate diameters for each node using distances and field markings
        double[] nodesDiams = new double[numNodes];
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (field[i] == field[j])
                {
                    nodesDiams[i] = Math.max(nodesDiams[i], shortestDist[i][j]);
                }
            }
        }

        //find the diameter of each field
        double[] fieldDiams = new double[numNodes];
        Arrays.fill(fieldDiams, -1);
        for (int i = 0; i < numNodes; i++)
        {
            fieldDiams[field[i]] = Math.max(fieldDiams[field[i]], nodesDiams[i]);
        }

        //find the best diameter
        double currCombine;
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                //for two different fields there are 3 possibilities
                if (field[i] != field[j])
                {
                    //node diameter of node i + distance i to j + node diameter of node j
                    currCombine = nodesDiams[i] + nodesDiams[j] + pointDist[i][j];
                    //or the diameter of one of the fields
                    currCombine = max(currCombine, fieldDiams[field[i]], fieldDiams[field[j]]);

                    //check for new best
                    bestDiameter = Math.min(bestDiameter, currCombine);
                }
            }
        }

        //output and exit
        DecimalFormat df = new DecimalFormat("0.000000");
        out.println(df.format(bestDiameter));
        in.close();
        out.close();
    }

    static void field(int[] field, int curr, boolean[] visited, int marker, double[][] graph)
    {
        field[curr] = marker;
        visited[curr] = true;

        for (int i = 0; i < numNodes; i++)
        {
            //have we visited this node yet and is there a connection
            if (!visited[i] && Math.abs(graph[curr][i]- INF) >= TOL)
            {
                field(field, i, visited, marker, graph);
            }
        }
    }

    //returns 2d array with distances from each node to each other node
    public static double[][] floydWarshall (double[][] adjMatrix)
    {
        int nodes = adjMatrix[0].length;
        double[][] dist = new double[nodes][nodes];


        //single length paths
        for (int i = 0; i < nodes; i++)
        {
            for (int j = 0; j < nodes; j++)
            {
                if (i == j)
                    dist[i][j] = 0;
                else
                    dist[i][j] = adjMatrix[i][j];
            }
        }
        //print(dist);

        //algorithm
        //intermittent nodes
        for (int k = 0; k < nodes; k++)
        {
            //end node 1
            for (int i = 0; i < nodes; i++)
            {
                //end node 2
                for (int j = 0; j < nodes; j++)
                {
                    //print(dist);
                    //check if the intermittent distance is better than the current distance
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        return dist;
    }

    static double distance(double x1, double y1, double x2, double y2)
    {
        return Math.sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    }

    static double max(double a, double b, double c)
    {
        return Math.max(a, Math.max(b, c));
    }

    public static void print(double[][] arr)
    {
        for (double[] a : arr)
        {
            //System.out.println(Arrays.toString(a).replaceAll("\\[|\\]", ""));
            System.out.println(Arrays.toString(a));
        }
        System.out.println();
    }
}
