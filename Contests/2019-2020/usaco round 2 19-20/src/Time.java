//Xavier Silva
//AdvCS
//USACO 19-20 Round 2
//P1 Time is Mooney
import java.io.*;
import java.util.*;
public class Time {
    static int numNodes, numEdges, price;
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("time.in"));
        PrintWriter out = new PrintWriter(new FileWriter("time.out"));
        ArrayList<Node> graph = new ArrayList<>();
        String[] currLine;

        //input
        currLine = in.readLine().split("\\s+");
        numNodes = Integer.parseInt(currLine[0]);
        numEdges = Integer.parseInt(currLine[1]);
        price = Integer.parseInt(currLine[2]);

        //create nodes with weights
        currLine = in.readLine().split("\\s+");
        for (int i = 0; i < numNodes; i++)
        {
            graph.add(new Node(i,Integer.parseInt(currLine[i])));
        }

        //create edges
        for (int i = 0; i < numEdges; i++)
        {
            currLine = in.readLine().split("\\s+");
            int prevN = Integer.parseInt(currLine[0])-1;
            int nextN = Integer.parseInt(currLine[1])-1;

            Node prev = graph.get(prevN);
            Node next = graph.get(nextN);
            prev.edges.add(new Edge(prev, next, next.weight));
        }

        //do algorithm
        Node start = graph.get(0);
        compute(start);

        out.println(start.pair.calculate(price));


        out.close();
        in.close();
    }

    public static void compute(Node curr)
    {
        Queue<Node> queue = new LinkedList<>();

        queue.add(curr);

        while (!queue.isEmpty())
        {
            curr = queue.remove();

            //go through all edges
            for (Edge e : curr.edges)
            {
                Pair nextPair = e.next.pair;
                Pair prevPair = e.prev.pair;
                Pair added = new Pair(prevPair.weight+e.weight,prevPair.time+1);

                //check whether to update edge
                if (added.calculate(price) > nextPair.calculate(price))
                {
                    e.next.pair = added;
                    queue.add(e.next);
                }
            }
        }
    }
}

class Node
{
    int label, weight;
    ArrayList<Edge> edges;
    Pair pair;

    public Node(int l, int w)
    {
        label = l;
        weight = w;
        edges = new ArrayList<>();
        pair = new Pair(0,0);
    }
}

class Edge
{
    int weight;
    Node prev, next;

    public Edge(Node p, Node n, int w)
    {
        weight = w;
        prev = p;
        next = n;
    }
}

class Pair
{
    int weight, time;
    public Pair (int w, int t)
    {
        weight = w;
        time = t;
    }
    public int calculate (int price)
    {
        return weight - price * time * time;
    }
}
