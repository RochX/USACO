/*
ID: xavierw1
PROG: nocows
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 5-6-20
//PROBLEM ID    : USACO Cow Pedigrees
//DESCRIPTION   : Given two numbers N and K find how many trees can be made N nodes and depth K
//SOURCES/HELP  :
import java.io.*;
import java.util.*;
public class nocows
{
    public static void main(String[] args) throws IOException
    {
        //variables and objects
        final int MOD = 9901;
        Scanner in = new Scanner(new File("nocows.in"));
        PrintWriter out = new PrintWriter(new FileWriter("nocows.out"));
        //trees[depth][number of nodes] = number of trees with this property
        int[][] trees = new int[101][202];
        //smaller[depth][number of nodes] = total number of trees with depth-1 or less
        int[][] smaller = new int[101][202];
        int numNodes, depth;

        //input and setup
        numNodes = in.nextInt();
        depth = in.nextInt();
        trees[1][1] = 1;

        //loop through depths
        for (int i = 2; i <= depth; i++)
        {
            //loop through number of nodes
            for (int j = 1; j <= numNodes; j += 2)
            {
                //loop through number of nodes in L subtree
                for (int l = 1; l <= j-1-l; l += 2)
                {
                    int c = 1;
                    //check if L and R subtrees can be swapped
                    if (l != j-1-l)
                    {
                        //if so count the tree twice
                        c = 2;
                    }

                    //3 cases
                    //left subtree smaller than i-1
                    trees[i][j] += c * (smaller[i-2][l]*trees[i-1][j-1-l]);
                    //right smaller than i-1
                    trees[i][j] += c * (trees[i-1][l]*smaller[i-2][j-1-l]);
                    //both smaller than i-1
                    trees[i][j] += c * (trees[i-1][l]*trees[i-1][j-1-l]);

                    //mod the number
                    trees[i][j] %= MOD;
                }
            }

            //ensures that the smaller array has valid values for the next loop of i
            for (int j = 0; j <= numNodes; j++)
            {
                smaller[i-1][j]+=trees[i-1][j]+smaller[i-2][j];
                smaller[i-1][j]%=MOD;
            }
        }

        //output and exit
        out.println(trees[depth][numNodes]);
        out.close();
        in.close();
    }
}
