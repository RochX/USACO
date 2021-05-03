//Xavier Silva
//DM
//USACO 19-20 Round 1
//P3 Milk Visits
import java.io.*;
import java.util.*;
public class MilkVisits {
    public static void main(String[] args) throws IOException
    {
        //declare and input
        BufferedReader in = new BufferedReader(new FileReader("milkvisits.in"));
        PrintWriter out = new PrintWriter(new FileWriter("milkvisits.out"));
        String[] inp;
        inp = in.readLine().split("[\\s]+");
        int farm = StoI(inp[0]), friend = StoI(inp[1]);
        String types = in.readLine(), output = "";
        Tree tree = new Tree();

        //add nodes to tree
        for (int i = 0; i < farm; ++i)
        {
            tree.nodes.add(new Node(types.charAt(i),i));
        }

        //assign adjacent nodes
        for (int i = 0; i < farm-1; ++i)
        {
            inp = in.readLine().split("[\\s]+");
            int a = StoI(inp[0])-1, b = StoI(inp[1])-1;
            Node n1 = tree.get(a), n2 = tree.get(b);
            n1.adjacent.add(n2);
            n2.adjacent.add(n1);
        }

        //make paths
        for (int i = 0; i < friend; ++i)
        {
            //declare vars
            inp = in.readLine().split("[\\s]+");
            int a = StoI(inp[0])-1, b = StoI(inp[1])-1;
            char type = inp[2].charAt(0);

            //get the path from start to end node
            String[] path = tree.find(a, b).substring(1).split("\\s+");

            //check if it satisfies the friend
            boolean good = false;
            Node curr;
            for (int j = 0; j < path.length; j++)
            {
                //see if the type is correct
                curr = tree.get(StoI(path[j]));
                if (curr.type == type)
                {
                    good = true;
                    break;
                }
            }

            //if one of the correct type is there output 1 otherwise 0
            if (good)
                out.print("1");
            else
                out.print("0");
        }
        out.println();

        //exit
        in.close();
        out.close();
    }

    //string to integer function
    public static int StoI(String inp)
    {
        return Integer.parseInt(inp);
    }
}

//tree class
class Tree
{
    //vars
    ArrayList<Node> nodes;
    String currPath;
    boolean stop;

    //constructor
    public Tree()
    {
        nodes = new ArrayList<>();
    }

    //get node from list
    public Node get(int n)
    {
        return nodes.get(n);
    }

    //find the path
    public String find(int s, int e)
    {
        //vars
        currPath = "NONE";
        stop = false;

        //find the path
        find(s,e," " + s + " ");

        //return path
        return currPath;
    }

    //find function
    private void find(int s, int e, String path)
    {
        //current node
        Node curr = get(s);

        //exit condition: current node (s) is the last node (e)
        if (s == e)
        {
            //path += e + " ";
            currPath = path;
            stop = true;
            return;
        }

        //DFS on the tree
        for (int i = 0; i < curr.adjacent.size(); ++i) {
            if (stop)
                return;
            int currNum = curr.adjacent.get(i).num;
            if (!path.contains(" " + currNum + " "))
            {
                //queue.add(currNum + ":" + e + ":" + path + currNum + " ");
                find(currNum,e,path + currNum + " ");
            }
        }
    }
}

//node class
class Node
{
    //vars
    char type;
    ArrayList<Node> adjacent;
    int num;

    //constructor
    public Node(char t, int n)
    {
        num = n;
        type = t;
        adjacent = new ArrayList<>();
    }
}
