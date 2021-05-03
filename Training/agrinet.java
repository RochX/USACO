/*
ID: xavierw1
PROG: agrinet
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 2-9-20
//PROBLEM ID    : USACO Agri-Net
//DESCRIPTION   : Find the minimum amount of cable needed to connect a set of farms
//SOURCES/HELP  :
import java.util.*;
import java.io.*;
public class agrinet
{
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        Scanner in = new Scanner(new File(("agrinet.in")));
        PrintWriter out = new PrintWriter(new FileWriter("agrinet.out"));
        int numFarms = in.nextInt();
        int[][] graph = new int[numFarms][numFarms];

        //input graph
        for (int i = 0; i < numFarms; i++)
        {
            for (int j = 0; j < numFarms; j++)
            {
                graph[i][j] = in.nextInt();
            }
        }

        //answer to problem is total weight of the minimum spanning tree of the graph
        int treeCost = prims(graph);

        //output and exit program
        out.println(treeCost);
        in.close();
        out.close();
    }

    //prims algorithm to form the minimum spanning tree
    public static int prims(int[][] graph)
    {
        //vars and objects
        final int INF = 999999999, NO_EDGE = 0;
        int numV = graph[0].length, treeSize, treeCost, minNode;
        boolean[] inTree = new boolean[numV];
        int[] parent = new int[numV];
        int[] distFromTree = new int[numV];

        //initialize the arrays
        Arrays.fill(inTree, false);
        Arrays.fill(parent, -1);
        Arrays.fill(distFromTree, INF);

        //add vertex 0 to tree
        treeSize = 1;
        treeCost = 0;
        inTree[0] = true;
        distFromTree[0] = 0;
        parent[0] = -1;

        //update distances of the other vertices to vertex 0
        for (int i = 0; i < numV; i++)
        {
            if (graph[0][i] != NO_EDGE)
            {
                distFromTree[i] = graph[0][i];
                parent[i] = 0;
            }
        }

        //loop until every vertex has been added to the tree
        while (treeSize < numV)
        {
            //find the node that is closest to the current tree
            minNode = minNode(distFromTree, inTree);

            //add that vertex to the tree
            treeSize++;
            treeCost += distFromTree[minNode];
            inTree[minNode] = true;

            //update distances of the other vertices to the tree
            for (int i = 0; i < numV; i++)
            {
                if (graph[minNode][i] > NO_EDGE && distFromTree[i] > graph[minNode][i])
                {
                    distFromTree[i] = graph[minNode][i];
                    parent[i] = minNode;
                }
            }
        }

        //return the weight of the tree
        return treeCost;
    }

    //find the vertex closest to the current tree
    static int minNode(int[] distance, boolean[] inTree)
    {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int i = 0; i < distance.length; i++)
        {
            if (!inTree[i] && distance[i] < min)
            {
                min = distance[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
}
