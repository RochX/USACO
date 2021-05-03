//Xavier Silva
//AdvCS
//USACO 19-20 Round 2
//P3 Springboards
import java.io.*;
import java.util.*;
public class Boards {
    static Board[] boards;
    static int best;
    public static void main(String[] args) throws IOException
    {
        Scanner in = new Scanner(new File("boards.in"));
        PrintWriter out = new PrintWriter(new FileWriter("boards.out"));

        int n = in.nextInt(), numBoards = in.nextInt();
        best = 2*n;
        boards = new Board[numBoards];

        for (int i = 0; i < numBoards; i++)
        {
            boards[i] = new Board(in.nextInt(),in.nextInt(),in.nextInt(),in.nextInt());
        }
        Arrays.sort(boards, new Comparator<Board>() {
            @Override
            public int compare(Board o1, Board o2) {
                int compX = Integer.compare(o1.sX,o2.sX);
                if (compX == 0)
                    return Integer.compare(o1.sY,o2.sY);
                else
                    return compX;
            }
        });

        //depth first search
        search(0,0,0,2*n);

        out.println(best);

        out.close();
        in.close();
    }

    public static void search(int x, int y, int index, int dist)
    {
        boolean used = false;

        for (int i = index; i < boards.length; i++)
        {
            //choose a board to use
            Board curr = boards[i];

            //check if valid then use
            if (curr.sX - x >= 0 && curr.sY - y >= 0)
            {
                search(curr.eX, curr.eY, i + 1, dist - curr.dist);
                used = true;
            }
        }

        if (!used)
            best = Math.min(best,dist);
    }
}

class Board
{
    int sX, sY, eX, eY;
    int dist;
    public Board(int a, int b, int c, int d)
    {
        sX = a;
        sY = b;
        eX = c;
        eY = d;
        dist = eX - sX + eY - sY;
    }
}
