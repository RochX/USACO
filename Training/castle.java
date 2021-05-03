/*
 ID: xavierw1
 PROG: castle
 LANG: JAVA
*/
//NAME          :   Xavier Silva
//GROUP         :   DM
//LAST MODIFIED :   11 Nov 2019
//PROBLEM ID    :   USACO The Castle
//DESCRIPTION   :   Given a list of integers that determine where walls are in a M x N castle, find the number of rooms, the size of the largest room, the largest size when one wall is removed, and the wall that can be removed in order to make largest room.
//SOURCES/HELP  :
import java.io.*;
import java.util.*;
public class castle 
{
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        Scanner in = new Scanner(new File("castle.in"));
        PrintWriter out = new PrintWriter(new FileWriter("castle.out"));
        //m by n castle
        int m, n, curr, largeRoom, largestRemoved;
        String loc = "";
        int[] sizes;
        int[][] rooms;
        Wall[][] walls;

        //input and initialize
        m = in.nextInt();
        n = in.nextInt();
        walls = new Wall[n][m];
        rooms = new int[n][m];

        //set walls
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                walls[i][j] = new Wall(in.nextInt());
            }
        }

        //fill
        curr = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (rooms[i][j] == 0)
                {
                    fill(curr,i,j,rooms,walls);
                    curr++;
                }
            }
        }

        //find sizes
        sizes = new int[curr];
        for (int i = 0; i < n; i++)
        {
            System.out.println(Arrays.toString(rooms[i]));

            for (int j = 0; j < m; j++)
            {
                sizes[rooms[i][j]]++;
            }
        }

        //find largest
        largeRoom = 0;
        for (int i = 0; i < sizes.length; i++)
        {
            largeRoom = Math.max(largeRoom, sizes[i]);
        }

        //try removing walls
        largestRemoved = 0;
        for (int j = 0; j < rooms[0].length; j++)
        {
            for (int i = rooms.length-1; i >= 0; i--)
            {
                int roomCurr = rooms[i][j];

                //north
                if (i-1 >= 0)
                {
                    int roomN = rooms[i-1][j];
                    if (roomCurr != roomN)
                    {
                        if (largestRemoved < sizes[roomN] + sizes[roomCurr])
                        {
                            largestRemoved = sizes[roomN] + sizes[roomCurr];
                            loc = (i+1) + " " + (j+1) + " N";
                        }
                    }
                }

                //east
                if (j+1 < rooms[0].length)
                {
                    int roomE = rooms[i][j+1];
                    if (roomCurr != roomE)
                    {
                        if (largestRemoved < sizes[roomE] + sizes[roomCurr])
                        {
                            largestRemoved = sizes[roomE] + sizes[roomCurr];
                            loc = (i+1) + " " + (j+1) + " E";
                        }
                    }
                }
            }
        }

        //output
        out.println(sizes.length-1);
        out.println(largeRoom);
        out.println(largestRemoved);
        out.println(loc);

        //exit
        in.close();
        out.close();
    }

    static void fill(int curr, int i, int j, int[][] rooms, Wall[][] walls)
    {
        rooms[i][j] = curr;
        boolean vS = i+1 < rooms.length, vE = j+1 < rooms[0].length, vN = i-1 >= 0, vW = j-1 >= 0;

        //south
        if (vS && rooms[i+1][j] == 0 && !walls[i][j].s)
        {
            fill(curr,i+1,j,rooms,walls);
        }

        //east
        if (vE && rooms[i][j+1] == 0 && !walls[i][j].e)
        {
            fill(curr,i,j+1,rooms,walls);
        }

        //north
        if (vN && rooms[i-1][j] == 0 && !walls[i][j].n)
        {
            fill(curr,i-1,j,rooms,walls);
        }

        //west
        if (vW && rooms[i][j-1] == 0 && !walls[i][j].w)
        {
            fill(curr,i,j-1,rooms,walls);
        }
    }
}

class Wall
{
    boolean s,e,n,w;
    public Wall(int in)
    {
        String wall = Integer.toBinaryString(in);
        while (wall.length() < 4)
        {
            wall = "0" + wall;
        }

        s = wall.charAt(0) == '1';
        e = wall.charAt(1) == '1';
        n = wall.charAt(2) == '1';
        w = wall.charAt(3) == '1';
    }
}