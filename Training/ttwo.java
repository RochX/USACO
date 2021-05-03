/*
ID: xavierw1
PROG: ttwo
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 1-31-20
//PROBLEM ID    : USACO The Tamworth Two
//DESCRIPTION   : Find how long it takes for cows and Farmer John to meet
//SOURCES/HELP  :
import java.io.*;
import java.util.*;
public class ttwo
{
    static char[][] map;
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        final int SIZE = 10;
        BufferedReader in = new BufferedReader(new FileReader("ttwo.in"));
        PrintWriter out = new PrintWriter(new FileWriter("ttwo.out"));
        map = new char[SIZE][SIZE];
        String inp;
        //row, col
        int[] cow = {0,0}, john = {0,0};
        //0 = N, 1 = E, 2 = S, 3 = W
        int cDir = 0, jDir = 0;

        //input and initialization
        for (int a = 0; a < 10; a++)
        {
            inp = in.readLine();
            for (int b = 0; b < 10; b++)
            {
                if (inp.charAt(b) != '.')
                    map[a][b] = inp.charAt(b);

                //get locations of cows and john
                if (map[a][b] == 'C')
                {
                    cow[0] = a;
                    cow[1] = b;
                }
                if (map[a][b] == 'F')
                {
                    john[0] = a;
                    john[1] = b;
                }
            }
        }

        boolean outputted = false;
        //loop enough times to work
        for (int a = 0; a < 4*SIZE*SIZE; a++)
        {
            //check if they meet
            if (john[0] == cow[0] && john[1] == cow[1])
            {
                out.println(a);
                outputted = true;
                break;
            }

            //update john's position
            jDir = updatePos(john, jDir);

            //update cow's position
            cDir = updatePos(cow,cDir);
        }

        //if they never meet output 0
        if(!outputted)
            out.println(0);

        //exit program
        out.close();
        in.close();
    }

    //returns the new direction
    static int updatePos(int[] pos, int dir)
    {
        //see if the thing can move in the direction
        boolean valid = valid(pos[0],pos[1],dir);

        //if valid then update direction
        //0 = N, 1 = E, 2 = S, 3 = W
        if (valid)
        {
            switch (dir)
            {
                case 0:
                    pos[0]--;
                    break;
                case 1:
                    pos[1]++;
                    break;
                case 2:
                    pos[0]++;
                    break;
                case 3:
                    pos[1]--;
                    break;
            }
        }
        //update direction
        else
        {
            dir = (dir+1) % 4;
        }
        return dir;
    }

    //check if an object can move in a certain direction
    static boolean valid(int row, int col, int dir)
    {
        //0 = N, 1 = E, 2 = S, 3 = W
        switch (dir)
        {
            case 0:
                if (row == 0 || map[row-1][col] == '*')
                    return false;
                break;
            case 1:
                if (col == 9 || map[row][col+1] == '*')
                    return false;
                break;
            case 2:
                if (row == 9 || map[row+1][col] == '*')
                    return false;
                break;
            case 3:
                if (col == 0 || map[row][col-1] == '*')
                    return false;
                break;
        }

        return true;
    }
}
