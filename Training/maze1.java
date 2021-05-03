/*
ID: xavierw1
PROG: maze1
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 1-20-20
//PROBLEM ID    : USACO Overfencing
//DESCRIPTION   : Given a maze configuration, find the minimum number of steps needed to exit the maze
//SOURCES/HELP  :
import java.io.*;
import java.util.*;
public class maze1
{
    static Fence[][] maze;
    public static void main(String[] args) throws IOException
    {
        //declare vars and objects
        Scanner in = new Scanner(new File("maze1.in"));
        PrintWriter out = new PrintWriter(new FileWriter("maze1.out"));
        int w,h, minSteps;
        String[] input;

        //input and initialization
        w = 2*in.nextInt()+1;
        h = 2*in.nextInt()+1;
        in.nextLine();
        input = new String[h];
        maze = new Fence[h/2][w/2];
        //input the maze
        for (int i = 0; i < h; i++)
        {
            input[i] = in.nextLine();
            while (input[i].length() < w)
                input[i] += " ";
        }

        //figure out the wall configuration for the maze
        for (int r = 1; r < h; r += 2)
        {
            for (int c = 1; c < w; c += 2)
            {
                maze[r/2][c/2] = new Fence(input[r-1].charAt(c) == '-',input[r+1].charAt(c) == '-',input[r].charAt(c+1) == '|',input[r].charAt(c-1) == '|');
                maze[r/2][c/2].row = r/2;
                maze[r/2][c/2].col = c/2;
            }
        }

        //reset vars
        h /= 2;
        w /= 2;
        minSteps = h*w;

        //declare vars
        int[][] steps = new int[h][w];
        boolean[][] used;
        int r,c;
        for (int[] step : steps)
        {
            Arrays.fill(step,h*w);
        }

        //loop through all points in the maze
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {

                //initialize
                int[][] arr = new int[h][w];
                arr[i][j] = 1;
                Fence curr = maze[i][j];


                //check for exit
                if (i == 0 && !curr.north || i == h-1 && !curr.south || j == 0 && !curr.west || j == w-1 && !curr.east)
                {
                    //delcare vars and objects
                    used = new boolean[h][w];
                    Queue<Fence> queue = new LinkedList<>();
                    queue.add(maze[i][j]);

                    //breath first fill to find path to chosen exit
                    while (!queue.isEmpty())
                    {
                        //set up vars
                        curr = queue.remove();
                        boolean preCon;
                        r = curr.row;
                        c = curr.col;
                        used[r][c] = true;

                        //north
                        preCon = r-1 >= 0;
                        if (preCon && !used[r-1][c] && !curr.north)
                        {
                            arr[r-1][c] = arr[r][c]+1;
                            if (!queue.contains(maze[r-1][c]))
                                queue.add(maze[r-1][c]);
                        }
                        //south
                        preCon = r+1 < maze.length;
                        if (preCon && !used[r+1][c] && !curr.south)
                        {
                            arr[r+1][c] = arr[r][c]+1;
                            if (!queue.contains(maze[r+1][c]))
                                queue.add(maze[r+1][c]);
                        }
                        //east
                        preCon = c+1 < maze[0].length;
                        if (preCon && !used[r][c+1] && !curr.east)
                        {
                            arr[r][c+1] = arr[r][c]+1;
                            if (!queue.contains(maze[r][c+1]))
                                queue.add(maze[r][c+1]);
                        }
                        //west
                        preCon = c-1 >= 0;
                        if (preCon && !used[r][c-1] && !curr.west)
                        {
                            arr[r][c-1] = arr[r][c]+1;
                            if (!queue.contains(maze[r][c-1]))
                                queue.add(maze[r][c-1]);
                        }
                    }

                    //combine the current result with the final result
                    mesh(steps,arr);
                }
            }
        }

        //find and print output
        minSteps = maxOf(steps);
        out.println(minSteps);

        //exit program
        in.close();
        out.close();
    }

    //makes all the elements of steps the smallest of steps and arr
    public static void mesh(int[][] steps, int[][] arr)
    {
        for (int i = 0; i < steps.length; i++)
        {
            for (int j = 0; j < steps[0].length; j++)
            {
                steps[i][j] = Math.min(steps[i][j],arr[i][j]);
            }
        }
    }

    //finds the largest value in a 2d array
    public static int maxOf(int[][] arr)
    {
        int max = 0;
        for (int[] a : arr)
        {
            for (int b : a)
            {
                max = Math.max(max,b);
            }
        }
        return max;
    }
}

//wall class to store the wall config in
class Fence
{
    int row,col;
    boolean north,south,east,west;

    //4 bit binary string: NSEW
    public Fence(String config)
    {
        north = config.charAt(0) == '1';
        south = config.charAt(1) == '1';
        east = config.charAt(2) == '1';
        west = config.charAt(3) == '1';
    }
    public Fence(boolean n, boolean s, boolean e, boolean w)
    {
        north = n;
        south = s;
        east = e;
        west = w;
    }

    public String toString()
    {
        String output = "";

        output += row + ":" + col;
        /*output += north ? '1' : '0';
        output += south ? '1' : '0';
        output += east ? '1' : '0';
        output += west ? '1' : '0';*/
        return output;
    }
}
